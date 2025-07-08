#include "network.h"
#include "w5500_eth.h"
#include "esp_event.h"
#include "esp_check.h"
#include "esp_log.h"

static const char *TAG = "network";

/** Event handler for IP_EVENT_ETH_GOT_IP */
static void got_ip_event_handler(void *arg, esp_event_base_t event_base,
                                 int32_t event_id, void *event_data) {
  ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
  const esp_netif_ip_info_t *ip_info = &event->ip_info;

  ESP_LOGI(TAG, "Ethernet Got IP Address");
  ESP_LOGI(TAG, "~~~~~~~~~~~");
  ESP_LOGI(TAG, "ETHIP:" IPSTR, IP2STR(&ip_info->ip));
  ESP_LOGI(TAG, "ETHMASK:" IPSTR, IP2STR(&ip_info->netmask));
  ESP_LOGI(TAG, "ETHGW:" IPSTR, IP2STR(&ip_info->gw));
  ESP_LOGI(TAG, "~~~~~~~~~~~");
}

/** Event handler for Ethernet events */
static void eth_event_handler(void *arg, esp_event_base_t event_base,
                              int32_t event_id, void *event_data) {
  uint8_t mac_addr[6] = {0};
  /* we can get the ethernet driver handle from event data */
  esp_eth_handle_t eth_handle = *(esp_eth_handle_t *)event_data;

  switch (event_id) {
  case ETHERNET_EVENT_CONNECTED:
    esp_eth_ioctl(eth_handle, ETH_CMD_G_MAC_ADDR, mac_addr);
    ESP_LOGI(TAG, "Ethernet Link Up");
    ESP_LOGI(TAG, "~~~~~~~~~~~");
    ESP_LOGI(TAG, "Ethernet HW Addr: %02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0],
             mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    ESP_LOGI(TAG, "~~~~~~~~~~~");
    break;
  case ETHERNET_EVENT_DISCONNECTED:
    ESP_LOGI(TAG, "Ethernet Link Down");
    break;
  case ETHERNET_EVENT_START:
    ESP_LOGI(TAG, "Ethernet Started");
    break;
  case ETHERNET_EVENT_STOP:
    ESP_LOGI(TAG, "Ethernet Stopped");
    break;
  default:
    break;
  }
}

esp_err_t network_init(network_t *net) {
    if (!net) {
        ESP_LOGE(TAG, "invalid argument");
        return ESP_ERR_INVALID_ARG;
    }

    // 1) init ETH driver
    esp_err_t ret = w5500_eth_init(&net->eth_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "w5500_eth_init failed");

    // 2) init TCP/IP stack & default loop
    ret = esp_netif_init();
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_netif_init failed");

    // We will assume that a default event loop exists
    // ret = esp_event_loop_create_default();
    // ESP_RETURN_ON_ERROR(ret, TAG, "esp_event_loop_create_default failed");

    // 3) create & attach netif for ETH
    esp_netif_config_t cfg = ESP_NETIF_DEFAULT_ETH();
    net->eth_netif = esp_netif_new(&cfg);
    if (!net->eth_netif) {
        ESP_LOGE(TAG, "esp_netif_new failed");
        return ESP_FAIL;
    }
    ret = esp_netif_attach(net->eth_netif,
                           esp_eth_new_netif_glue(net->eth_handle));
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_netif_attach failed");

    ESP_RETURN_ON_ERROR(
        esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, got_ip_event_handler, net),
        TAG, "register IP_EVENT handler failed");

    ESP_RETURN_ON_ERROR(
        esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, eth_event_handler, &net->eth_handle),
        TAG, "register ETH_EVENT handler failed");

    return ESP_OK;
}

esp_err_t network_register_handlers(network_t *net,
                                    esp_event_handler_t eth_cb,
                                    esp_event_handler_t ip_cb)
{
    ESP_RETURN_ON_ERROR(
        esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, eth_cb, net),
        TAG, "register ETH_EVENT handler failed");
    ESP_RETURN_ON_ERROR(
        esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, ip_cb, net),
        TAG, "register IP_EVENT handler failed");
    return ESP_OK;
}

esp_err_t network_start(network_t *net) {
    if (!net) {
        ESP_LOGE(TAG, "invalid argument");
        return ESP_ERR_INVALID_ARG;
    }
    esp_err_t ret = esp_eth_start(net->eth_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_eth_start failed");
    return ESP_OK;
}

void network_deinit(network_t *net) {
    if (!net) {
        return;
    }
    // Stop driver
    esp_eth_stop(net->eth_handle);
    // Detach and destroy netif
    esp_netif_destroy(net->eth_netif);
    // Remove glue
    esp_eth_del_netif_glue(net->eth_handle);
    // Uninstall driver
    esp_eth_driver_uninstall(net->eth_handle);
}
