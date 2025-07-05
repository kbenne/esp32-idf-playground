#include "bacnet.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

static const char *TAG = "BACnet_Demo";

void app_main(void) {
  ESP_LOGI(TAG, "Starting BACnet demo application");

  // Main application loop
  while (1) {
    ESP_LOGI(TAG, "BACnet demo running...");
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Sleep for 5 seconds
  }
}
