#include "bacnet.h"
#include "bacnet/bacstr.h"
#include "bacnet/basic/object/device.h"
#include "bacnet/basic/server/bacnet_basic.h"
#include "bacnet/basic/server/bacnet_port_ipv4.h"
#include "esp_check.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif_types.h"

static const char *TAG = "bacnet";
static int DEVICE_INSTANCE = 4194303;
static const char *OBJECT_NAME = "ESP32_Device";

static void bacnet_task(void *pvParameters) {
  uint32_t ms = 0, sec = 0;

  for (;;) {
    // Drive timeouts, retransmits, TSM
    bacnet_basic_task();

    // Poll network & deliver incoming PDUs
    ms += 10;
    if (ms >= 1000) {
      ms -= 1000;
      sec++;
      // Only call the port task once per second to renew foreign device
      // registration if needed
      bacnet_port_ipv4_task(1);
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

static void got_ip_event(void *_, esp_event_base_t base, int32_t id,
                         void *data) {
  ESP_LOGI(TAG, "IP acquired, binding BACnet/IP port");
  if (!bacnet_port_ipv4_init()) {
    ESP_LOGE(TAG, "BACnet/IP port init failed");
    return;
  }

  BaseType_t result =
      xTaskCreate(bacnet_task, "bacnet", 16 * 1024, NULL, 5, NULL);
  if (result != pdPASS) {
    ESP_LOGE(TAG, "Failed to create BACnet task, error: %d", result);
  }
}

esp_err_t bacnet_init() {
  // Initialize the BACnet stack
  bacnet_basic_init();

  // Set BACnet device properties
  Device_Set_Object_Instance_Number(DEVICE_INSTANCE);

  BACNET_CHARACTER_STRING name;
  characterstring_init_ansi(&name, OBJECT_NAME);
  Device_Set_Object_Name(&name);

  // Currently no failure points in this function, but we could add error
  // checking if the BACnet stack functions ever provide error returns
  return ESP_OK;
}

esp_err_t bacnet_start() {
  ESP_RETURN_ON_ERROR(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP,
                                                 &got_ip_event, NULL),
                      TAG, "Failed to register Ethernet IP event handler");
  return ESP_OK;
}
