#include "esp_event.h"
#include "esp_log.h"

static const char *TAG = "BACnet_Demo";

bool bip_init(char *ifname);

void app_main(void) {
  ESP_LOGI(TAG, "Starting BACnet demo application");

  bip_init(NULL);

  /* Main application loop */
  while (1) {
    vTaskDelay(5000 / portTICK_PERIOD_MS); /* Sleep for 5 seconds */
  }
}
