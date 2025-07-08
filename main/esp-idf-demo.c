#include "esp_check.h"
#include "esp_event.h"
#include "esp_log.h"
#include "network.h"

static const char *TAG = "BACnet_Demo";

// bool bip_init(char *ifname);

static network_t network;

void app_main(void) {
  ESP_LOGI(TAG, "Starting BACnet demo application");

  ESP_ERROR_CHECK(esp_event_loop_create_default());

  ESP_ERROR_CHECK(network_init(&network));

  ESP_ERROR_CHECK(network_start(&network));

  // bip_init(NULL);

  ///* Main application loop */
  // while (1) {
  //   ESP_LOGI(TAG, "Tick");
  //   vTaskDelay(5000 / portTICK_PERIOD_MS); /* Sleep for 5 seconds */
  // }
}
