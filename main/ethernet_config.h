#ifndef ETHERNET_CONFIG_H
#define ETHERNET_CONFIG_H

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Default pin assignments for LAN8720 Ethernet PHY
 * 
 * These can be overridden in your project's sdkconfig
 * You may need to adjust these based on your specific ESP32 board
 */
#define CONFIG_ETH_PHY_ADDR        0          // PHY address (usually 0 or 1 for LAN8720)
#define CONFIG_ETH_PHY_RST_GPIO    5          // GPIO connected to PHY reset pin (-1 if not connected)
#define CONFIG_ETH_MDC_GPIO        23         // GPIO connected to SMI MDC pin
#define CONFIG_ETH_MDIO_GPIO       18         // GPIO connected to SMI MDIO pin
#define CONFIG_ETH_CLK_MODE        EMAC_CLK_OUT // RMII clock mode

/**
 * @brief Initialize the Ethernet interface with LAN8720 PHY
 *
 * @return ESP_OK on success
 */
esp_err_t ethernet_init(void);

/**
 * @brief Get MAC address as string
 * 
 * @param mac_str Buffer to store MAC address string (minimum 18 bytes)
 */
void ethernet_get_mac_str(char *mac_str);

/**
 * @brief Get IP address as string
 * 
 * @param ip_str Buffer to store IP address string (minimum 16 bytes)
 */
void ethernet_get_ip_str(char *ip_str);

/**
 * @brief Check if Ethernet is connected
 * 
 * @return true if Ethernet is connected
 */
bool ethernet_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* ETHERNET_CONFIG_H */