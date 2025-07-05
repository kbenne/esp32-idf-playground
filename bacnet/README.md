# BACnet Stack for ESP32

This directory contains a BACnet/IP implementation for ESP32 based on the [BACnet Protocol Stack](https://github.com/bacnet-stack/bacnet-stack) project. The implementation is configured as an ESP-IDF component that can be included in ESP32 projects.

## Overview

This component provides a complete BACnet/IP implementation that can be used to create BACnet devices on ESP32 hardware. It supports:

- BACnet/IP over Ethernet communication
- IPv4 and IPv6 support
- Full device server functionality
- Client functionality for discovering and communicating with other BACnet devices
- Comprehensive set of BACnet objects
- Standard BACnet services
- BBMD (BACnet Broadcast Management Device) support for both IPv4 and IPv6
- Routing capabilities for multi-network configurations

## Directory Structure

The BACnet implementation follows this structure:

- `bacnet-stack/` - The main BACnet protocol stack source code
  - `src/bacnet/` - Core BACnet protocol implementation
    - `datalink/` - Network communication layer (BACnet/IP, MS/TP, etc.)
    - `basic/` - Implementation of basic BACnet functionality
      - `object/` - BACnet object implementations (Analog/Binary/Multi-state I/O, etc.)
      - `service/` - BACnet service handlers and initiators
      - `binding/` - Address binding and caching
      - `bbmd/` - BACnet/IP Broadcast Management for IPv4
      - `bbmd6/` - BACnet/IP Broadcast Management for IPv6
      - `client/` - Client-side functionality
      - `npdu/` - Network Protocol Data Unit handling
      - `server/` - Server implementation
      - `sys/` - System utilities (timers, buffers, etc.)
      - `tsm/` - Transaction State Machine

## Usage

### Including in Your Project

The BACnet component is included in the ESP-IDF build system through the `CMakeLists.txt` file. It depends on:

- `lwip` - For network communication
- `esp_timer` - For timing functions

### Initialization

To initialize the BACnet stack in your application:

```c
#include "bacnet/bacdef.h"
#include "bacnet/config.h"
#include "bacnet/bactext.h"
#include "bacnet/datalink/bip.h"
#include "bacnet/basic/binding/address.h"
#include "bacnet/basic/object/device.h"
#include "bacnet/basic/object/netport.h"
#include "bacnet/basic/sys/mstimer.h"
#include "bacnet/basic/server/bacnet_basic.h"
#include "bacnet/basic/server/bacnet_port.h"
#include "bacnet/basic/server/bacnet_port_ipv4.h"
#include "bacnet/dcc.h"

#define BACNET_DEVICE_INSTANCE 4194303  // Choose a unique device instance
#define BACNET_DEVICE_NAME "ESP32-BACnet"

void app_main(void) {
    // Initialize Ethernet first
    ethernet_init();
    
    // Wait for Ethernet connection
    while (!ethernet_is_connected()) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    // Initialize BACnet device
    Device_Set_Object_Instance_Number(BACNET_DEVICE_INSTANCE);
    Device_Object_Name_ANSI_Init(BACNET_DEVICE_NAME);
    
    // Set device properties
    Device_Set_Model_Name("ESP32", sizeof("ESP32") - 1);
    Device_Set_Vendor_Identifier(999); // Replace with your vendor ID
    Device_Set_Application_Software_Version("1.0", sizeof("1.0") - 1);
    Device_Set_Description("ESP32 BACnet Device", sizeof("ESP32 BACnet Device") - 1);
    
    // Initialize BACnet/IP
    bip_init(NULL);
    
    // Initialize BACnet ports
    bacnet_port_ipv4_init();
    
    // Initialize BACnet services
    bacnet_basic_init();
    
    // Setup BACnet timer for periodic processing
    esp_timer_handle_t bacnet_timer;
    const esp_timer_create_args_t timer_args = {
        .callback = &bacnet_timer_callback,
        .name = "bacnet_timer"
    };
    
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &bacnet_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(bacnet_timer, 10 * 1000));  // 10ms intervals
    
    // Your main application loop
    while (1) {
        // Other application tasks
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

// BACnet timer callback for periodic processing
void bacnet_timer_callback(void *arg) {
    // Process BACnet tasks
    bacnet_basic_task();
    
    // Process network tasks
    static uint16_t seconds_elapsed = 0;
    static uint16_t ms_counter = 0;
    
    ms_counter += 10; // 10ms intervals
    if (ms_counter >= 1000) {
        seconds_elapsed++;
        ms_counter -= 1000;
        bacnet_port_ipv4_task(seconds_elapsed);
    }
}
```

### Creating BACnet Objects

This implementation includes all standard BACnet object types. To create a BACnet object (e.g., Analog Input):

```c
#include "bacnet/basic/object/ai.h"

void setup_bacnet_objects(void) {
    // Create an Analog Input object with instance 0
    Analog_Input_Create(0);
    
    // Set its properties
    Analog_Input_Name_Set(0, "Temperature Sensor");
    Analog_Input_Description_Set(0, "Room temperature sensor");
    Analog_Input_Units_Set(0, UNITS_DEGREES_CELSIUS);
    
    // Set its present value
    float value = 23.5;
    Analog_Input_Present_Value_Set(0, value);
}
```

## Configuration

The BACnet implementation can be configured through several methods:

1. **Device Properties** - Set during initialization and runtime
   ```c
   Device_Set_Object_Instance_Number(4194303);
   Device_Set_Model_Name("ESP32", sizeof("ESP32") - 1);
   Device_Set_Vendor_Identifier(999);  // Your assigned vendor ID
   ```

2. **Network Properties** - IP configuration is handled by the ESP32 Ethernet setup

3. **Object Configuration** - Add, configure, and update objects as needed in your application

## ESP32 Integration

This implementation integrates with the ESP32 platform through:

- Socket operations through lwIP
- Time functions through FreeRTOS and ESP-IDF's timer APIs
- Integration with the ESP32 Ethernet driver

The integration uses the standard BACnet/IP datalink layer with ESP32-specific networking APIs.

## Compiler Flags

The following compiler flags have been applied to the BACnet component to ensure compatibility with ESP32:

```cmake
target_compile_options(${COMPONENT_LIB} PRIVATE 
    -Wno-format            # Disable format warnings
    -Wno-error=format      # Don't treat format warnings as errors
)
```

These flags are necessary because the ESP32 compiler treats `uint32_t` as `long unsigned int`, which causes format string warnings when using `%u` with `uint32_t` values.

## Limitations

- This implementation focuses on BACnet/IP over Ethernet. MS/TP (RS-485) is not currently included in the port.
- The UCI configuration system (for OpenWrt-based systems) is disabled as it's not applicable to ESP32.
- Some advanced security features may require additional implementation.

## References

- [BACnet Protocol Stack Project](https://github.com/bacnet-stack/bacnet-stack)
- [BACnet Standard (ASHRAE 135)](http://www.bacnet.org/)
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)