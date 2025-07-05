#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "esp_event.h"
#include "driver/gpio.h"
#include "ethernet_config.h"

static const char *TAG = "eth_config";

/* Event group for network connection status */
static EventGroupHandle_t eth_event_group;
#define ETH_CONNECTED_BIT BIT0

/* Ethernet objects */
static esp_eth_handle_t eth_handle = NULL;
static esp_netif_t *eth_netif = NULL;
static char eth_mac_str[18] = {0};
static char eth_ip_str[16] = {0};

/* Event handler for Ethernet events */
static void eth_event_handler(void *arg, esp_event_base_t event_base,
                              int32_t event_id, void *event_data)
{
    uint8_t mac_addr[6] = {0};
    esp_eth_handle_t eth_handle = *(esp_eth_handle_t *)event_data;

    switch (event_id) {
    case ETHERNET_EVENT_CONNECTED:
        esp_eth_ioctl(eth_handle, ETH_CMD_G_MAC_ADDR, mac_addr);
        snprintf(eth_mac_str, sizeof(eth_mac_str), "%02x:%02x:%02x:%02x:%02x:%02x",
                 mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        ESP_LOGI(TAG, "Ethernet Link Up");
        ESP_LOGI(TAG, "Ethernet HW Addr %s", eth_mac_str);
        break;
    case ETHERNET_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "Ethernet Link Down");
        xEventGroupClearBits(eth_event_group, ETH_CONNECTED_BIT);
        break;
    case ETHERNET_EVENT_START:
        ESP_LOGI(TAG, "Ethernet Started");
        break;
    case ETHERNET_EVENT_STOP:
        ESP_LOGI(TAG, "Ethernet Stopped");
        xEventGroupClearBits(eth_event_group, ETH_CONNECTED_BIT);
        break;
    default:
        break;
    }
}

/* IP event handler */
static void ip_event_handler(void *arg, esp_event_base_t event_base,
                             int32_t event_id, void *event_data)
{
    ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;

    switch (event_id) {
    case IP_EVENT_ETH_GOT_IP:
        snprintf(eth_ip_str, sizeof(eth_ip_str), IPSTR, IP2STR(&event->ip_info.ip));
        ESP_LOGI(TAG, "Ethernet Got IP Address");
        ESP_LOGI(TAG, "~~~~~~~~~~~");
        ESP_LOGI(TAG, "IP: %s", eth_ip_str);
        ESP_LOGI(TAG, "MASK: " IPSTR, IP2STR(&event->ip_info.netmask));
        ESP_LOGI(TAG, "GW: " IPSTR, IP2STR(&event->ip_info.gw));
        ESP_LOGI(TAG, "~~~~~~~~~~~");
        xEventGroupSetBits(eth_event_group, ETH_CONNECTED_BIT);
        break;
    default:
        break;
    }
}

esp_err_t ethernet_init(void)
{
    esp_err_t ret = ESP_OK;

    /* Create event group for Ethernet status */
    eth_event_group = xEventGroupCreate();
    if (!eth_event_group) {
        ESP_LOGE(TAG, "Failed to create event group");
        return ESP_FAIL;
    }

    /* Initialize TCP/IP network interface (should be called only once) */
    ESP_ERROR_CHECK(esp_netif_init());
    
    /* Create default event loop that running in background */
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    /* Create new default instance of esp-netif for Ethernet */
    esp_netif_config_t netif_cfg = ESP_NETIF_DEFAULT_ETH();
    eth_netif = esp_netif_new(&netif_cfg);

    /* Register user defined event handlers */
    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, 
                                              &eth_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, 
                                              &ip_event_handler, NULL));

    /* Initialize MAC and PHY configs to default */
    eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();
    
    /* Set PHY address and GPIO number for PHY reset */
    phy_config.phy_addr = CONFIG_ETH_PHY_ADDR;
    phy_config.reset_gpio_num = CONFIG_ETH_PHY_RST_GPIO;

    /* Configure ESP32 specific Ethernet settings */
    eth_esp32_emac_config_t esp32_emac_config = ETH_ESP32_EMAC_DEFAULT_CONFIG();
    esp32_emac_config.smi_mdc_gpio_num = CONFIG_ETH_MDC_GPIO;
    esp32_emac_config.smi_mdio_gpio_num = CONFIG_ETH_MDIO_GPIO;
    esp32_emac_config.clock_config.rmii.clock_mode = CONFIG_ETH_CLK_MODE;

    /* Create new ESP32 Ethernet MAC instance */
    esp_eth_mac_t *mac = esp_eth_mac_new_esp32(&esp32_emac_config, &mac_config);
    
    /* Create new LAN87xx PHY instance (replaces LAN8720) */
    esp_eth_phy_t *phy = esp_eth_phy_new_lan87xx(&phy_config);

    /* Combine Ethernet MAC and PHY to create Ethernet driver */
    esp_eth_config_t config = ETH_DEFAULT_CONFIG(mac, phy);
    ret = esp_eth_driver_install(&config, &eth_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Ethernet driver install failed");
        return ret;
    }

    /* Attach Ethernet driver to TCP/IP stack */
    ret = esp_netif_attach(eth_netif, esp_eth_new_netif_glue(eth_handle));
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to attach Ethernet driver to TCP/IP stack");
        return ret;
    }

    /* Start Ethernet driver */
    ret = esp_eth_start(eth_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Ethernet start failed");
        return ret;
    }

    return ESP_OK;
}

void ethernet_get_mac_str(char *mac_str)
{
    if (mac_str) {
        strcpy(mac_str, eth_mac_str);
    }
}

void ethernet_get_ip_str(char *ip_str)
{
    if (ip_str) {
        strcpy(ip_str, eth_ip_str);
    }
}

bool ethernet_is_connected(void)
{
    return (xEventGroupGetBits(eth_event_group) & ETH_CONNECTED_BIT) != 0;
}