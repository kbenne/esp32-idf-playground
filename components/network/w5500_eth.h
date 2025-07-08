/*
 * W5500 Ethernet Initialization Component
 *
 * Simplified from ESP-IDF ethernet_init example component
 * to focus only on W5500 SPI Ethernet controller
 */

#pragma once

#include "esp_eth_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief W5500 SPI Ethernet pin configuration
 *
 * Default values are set for ESP32-C6 with W5500 module
 */
#define W5500_SPI_HOST SPI2_HOST // SPI host (SPI2_HOST for ESP32-C6)
#define W5500_SPI_MISO_GPIO 2    // SPI MISO GPIO (IO_MUX pin for SPI2)
#define W5500_SPI_MOSI_GPIO 7    // SPI MOSI GPIO (IO_MUX pin for SPI2)
#define W5500_SPI_SCLK_GPIO 6    // SPI SCLK GPIO (IO_MUX pin for SPI2)
#define W5500_SPI_CS_GPIO 16     // SPI CS GPIO (IO_MUX pin for SPI2)
#define W5500_INT_GPIO 18        // W5500 Interrupt GPIO (non-strapping pin)
#define W5500_RESET_GPIO 19      // W5500 Reset GPIO (non-strapping pin)
#define W5500_SPI_CLOCK_MHZ 25   // SPI clock speed in MHz

/**
 * @brief Initialize W5500 Ethernet driver
 *
 * @return
 *          - ESP_OK on success
 *          - ESP_FAIL or other specific error code on error
 */
esp_err_t w5500_eth_init(esp_eth_handle_t *eth_handle_out);

#ifdef __cplusplus
}
#endif
