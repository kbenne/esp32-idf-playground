#include "bacnet.h"
#include "esp_event.h"
#include "esp_log.h"
#include "network.h"

static const char *TAG = "BACnet_App";

// bool bip_init(char *ifname);

static network_t network;

void app_main(void) {
  ESP_LOGI(TAG, "Starting BACnet Application");

  ESP_ERROR_CHECK(esp_event_loop_create_default());

  ESP_ERROR_CHECK(network_init(&network));

  // ESP_ERROR_CHECK(bacnet_init());

  ESP_ERROR_CHECK(network_start(&network));

  // ESP_ERROR_CHECK(bacnet_start());

  // bip_init(NULL);

  ///* Main application loop */
  // while (1) {
  //   ESP_LOGI(TAG, "Tick");
  //   vTaskDelay(5000 / portTICK_PERIOD_MS); /* Sleep for 5 seconds */
  // }
}
