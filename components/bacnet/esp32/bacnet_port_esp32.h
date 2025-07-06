/**
 * @file bacnet_port_esp32.h
 * @brief BACnet stack port for ESP32
 * @author Claude
 * @date 2025
 */

#ifndef BACNET_PORT_ESP32_H
#define BACNET_PORT_ESP32_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the BACnet stack for ESP32
 * 
 * @param device_instance BACnet device instance number
 * @param device_name Name of the BACnet device
 * @return true if initialization was successful
 */
bool bacnet_esp32_init(uint32_t device_instance, const char *device_name);

/**
 * @brief Task function for handling BACnet communication
 * 
 * @param milliseconds Time interval for processing
 */
void bacnet_esp32_task(uint16_t milliseconds);

#ifdef __cplusplus
}
#endif

#endif /* BACNET_PORT_ESP32_H */