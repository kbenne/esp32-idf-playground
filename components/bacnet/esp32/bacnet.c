/**
 * @file bacnet.c
 * @brief BACnet/IP implementation for ESP32
 * @author Claude
 * @date 2025
 */

#include <string.h>
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_timer.h"
#include "bacnet/datalink/bip.h"
#include "bacnet/datalink/bvlc.h"
#include "bacnet/basic/binding/address.h"
#include "bacnet/basic/sys/mstimer.h"
#include "bacnet/datalink/datalink.h"
#include "bacnet/bacstr.h"

/* Default BACnet/IP port */
#define BIP_PORT 0xBAC0

static const char *TAG = "bacnet_ip_esp32";

/* BACnet/IP implementation for ESP32 */
bool bip_init(char *ifname)
{
    bool status = false;
    esp_netif_ip_info_t ip_info;
    
    ESP_LOGI(TAG, "Initializing BACnet/IP datalink layer");
    
    /* Get the default netif */
    esp_netif_t *netif = esp_netif_get_default_netif();
    if (!netif) {
        ESP_LOGE(TAG, "Failed to get default network interface");
        return false;
    }
    
    /* Get IP information */
    if (esp_netif_get_ip_info(netif, &ip_info) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get IP info");
        return false;
    }
    
    /* Set BIP address with retrieved IP */
    BACNET_IP_ADDRESS addr;
    
    addr.address[0] = (ip_info.ip.addr >> 0) & 0xFF;
    addr.address[1] = (ip_info.ip.addr >> 8) & 0xFF;
    addr.address[2] = (ip_info.ip.addr >> 16) & 0xFF;
    addr.address[3] = (ip_info.ip.addr >> 24) & 0xFF;
    addr.port = BIP_PORT;
    
    bip_set_addr(&addr);
    
    /* Set the BIP port (default 47808 = 0xBAC0) */
    bip_set_port(BIP_PORT);
    
    /* Set the broadcast address */
    BACNET_IP_ADDRESS broadcast_addr;
    broadcast_addr.address[0] = (ip_info.ip.addr | ~ip_info.netmask.addr) & 0xFF;
    broadcast_addr.address[1] = ((ip_info.ip.addr | ~ip_info.netmask.addr) >> 8) & 0xFF;
    broadcast_addr.address[2] = ((ip_info.ip.addr | ~ip_info.netmask.addr) >> 16) & 0xFF;
    broadcast_addr.address[3] = ((ip_info.ip.addr | ~ip_info.netmask.addr) >> 24) & 0xFF;
    broadcast_addr.port = BIP_PORT;
    
    bip_set_broadcast_addr(&broadcast_addr);
    
    ESP_LOGI(TAG, "BACnet/IP initialized with address %d.%d.%d.%d", 
             addr.address[0], addr.address[1], addr.address[2], addr.address[3]);
    ESP_LOGI(TAG, "BACnet/IP broadcast address %d.%d.%d.%d", 
             broadcast_addr.address[0], broadcast_addr.address[1], 
             broadcast_addr.address[2], broadcast_addr.address[3]);
    
    status = true;
    return status;
}

/* ESP32 implementation for millisecond timer functions */
void mstimer_init(void)
{
    ESP_LOGI(TAG, "Initialized millisecond timer");
}

uint32_t mstimer_now(void)
{
    /* Use ESP32's internal millisecond counter */
    return (uint32_t)(esp_timer_get_time() / 1000);
}

/* Implementation for getting local IP address */
bool bip_get_local_address_ioctl(BACNET_ADDRESS *src, int socket_fd)
{
    /* Use the address already set in bip_init */
    uint32_t device_id = 0;
    BACNET_IP_ADDRESS addr;
    uint16_t port;
    
    if (src) {
        src->mac_len = 6;
        bip_get_addr(&addr);
        port = bip_get_port();
        
        memcpy(&src->mac[0], &addr.address[0], 4);
        memcpy(&src->mac[4], &port, 2);
        src->net = 0;
        src->len = 0;
        
        /* Create a matching binding entry */
        device_id = (addr.address[0] << 24) | 
                    (addr.address[1] << 16) | 
                    (addr.address[2] << 8) | 
                    (addr.address[3]);
        device_id &= 0x3FFFFF;
        
        if (address_get_device_id(src, &device_id)) {
            return true;
        }
    }
    
    return false;
}