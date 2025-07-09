#include "bacnet/basic/sys/mstimer.h"
#include "cc.h"
#include "esp_netif.h"
#include "esp_netif_types.h"
#include "esp_timer.h"

unsigned long mstimer_now(void) {
  // esp_timer_get_time() returns microseconds since boot
  return (unsigned long)(esp_timer_get_time() / 1000ULL);
}

uint8_t bip_get_subnet_prefix(void) {
  esp_netif_ip_info_t ip_info;
  esp_netif_t *eth_netif = esp_netif_get_handle_from_ifkey("ETH_DEF");
  // Or store your esp_netif_t* from creation and use that instead

  if (eth_netif == NULL) {
    // no such netif
    return 0;
  }
  if (esp_netif_get_ip_info(eth_netif, &ip_info) != ESP_OK) {
    // couldn’t read
    return 0;
  }

  uint32_t mask = ntohl(ip_info.netmask.addr);
  // Count the number of consecutive 1 bits starting at MSB
  uint8_t prefix = 0;
  while (prefix < 32 && (mask & 0x80000000)) {
    prefix++;
    mask <<= 1;
  }
  return prefix;
}
