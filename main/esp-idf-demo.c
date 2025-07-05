#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "ethernet_config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>
// #include "bacnet_port_esp32.h"

static const char *TAG = "BACnet_Demo";
static esp_timer_handle_t bacnet_timer;

/* BACnet device configuration */
#define BACNET_DEVICE_INSTANCE                                                 \
  4194303 /* Device instance number (adjust as needed) */
#define BACNET_DEVICE_NAME "ESP32-BACnet"

///* Timer callback for BACnet processing */
// static void bacnet_timer_callback(void *arg) {
//   bacnet_esp32_task(10); /* 10ms intervals */
// }
//
///* Initialize BACnet timer */
// static void init_bacnet_timer(void) {
//   const esp_timer_create_args_t timer_args = {
//       .callback = &bacnet_timer_callback, .name = "bacnet_timer"};
//
//   ESP_ERROR_CHECK(esp_timer_create(&timer_args, &bacnet_timer));
//   /* Timer fires every 10ms */
//   ESP_ERROR_CHECK(esp_timer_start_periodic(bacnet_timer, 10 * 1000));
//   ESP_LOGI(TAG, "BACnet timer initialized");
// }

void app_main(void) {
  ESP_LOGI(TAG, "Starting BACnet demo application");

  /* Initialize Ethernet with LAN8720 */
  ESP_ERROR_CHECK(ethernet_init());
  ESP_LOGI(TAG, "Waiting for Ethernet connection...");

  /* Wait for Ethernet to connect */
  int retry_count = 0;
  while (!ethernet_is_connected() && retry_count < 15) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    retry_count++;
    ESP_LOGI(TAG, "Waiting for Ethernet connection... %d/15", retry_count);
  }

  if (!ethernet_is_connected()) {
    ESP_LOGE(TAG, "Ethernet connection failed");
    return;
  }

  /* Get IP address */
  char ip_str[16];
  ethernet_get_ip_str(ip_str);
  ESP_LOGI(TAG, "Ethernet connected with IP: %s", ip_str);

  ///* Initialize BACnet */
  // if (!bacnet_esp32_init(BACNET_DEVICE_INSTANCE, BACNET_DEVICE_NAME)) {
  //     ESP_LOGE(TAG, "Failed to initialize BACnet");
  //     return;
  // }
  //
  ///* Start BACnet timer */
  // init_bacnet_timer();

  /* Main application loop */
  while (1) {
    ESP_LOGI(TAG, "BACnet demo running... IP: %s", ip_str);
    vTaskDelay(5000 / portTICK_PERIOD_MS); /* Sleep for 5 seconds */
  }
}
