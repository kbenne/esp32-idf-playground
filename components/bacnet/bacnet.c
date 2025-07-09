#include "bacnet.h"
// #include "bacnet/basic/object/device.h"
#include "bacnet/bacstr.h"
#include "bacnet/basic/object/device.h"
#include "bacnet/basic/server/bacnet_basic.h"
#include "bacnet/basic/server/bacnet_port_ipv4.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif_types.h"

static const char *TAG = "bacnet";
static int DEVICE_INSTANCE = 4194303;

static void bacnet_task(void *pvParameters) {
  // uint32_t ms = 0, sec = 0;

  // for (;;) {
  //   // Drive timeouts, retransmits, TSM
  //   bacnet_basic_task();

  //  // Poll network & deliver incoming PDUs
  //  ms += 10;
  //  if (ms >= 1000) {
  //    ms -= 1000;
  //    sec++;
  //  }
  //  // bacnet_port_ipv4_task(sec);

  //  vTaskDelay(pdMS_TO_TICKS(10));
  //}
}

static void got_ip_event(void *_, esp_event_base_t base, int32_t id,
                         void *data) {
  ESP_LOGI(TAG, "IP acquired, binding BACnet/IP port");
  // if (!bacnet_port_ipv4_init()) {
  //   ESP_LOGE(TAG, "BACnet/IP port init failed");
  //   return;
  // }
  xTaskCreate(bacnet_task, "bacnet", 8 * 1024, NULL, 5, NULL);
}

esp_err_t bacnet_init() {
  bacnet_basic_init();

  Device_Set_Object_Instance_Number(DEVICE_INSTANCE);

  BACNET_CHARACTER_STRING OBJECT_NAME;
  characterstring_init_ansi(&OBJECT_NAME, "ESP32_Device");
  Device_Set_Object_Name(&OBJECT_NAME);

  return ESP_OK;
}

esp_err_t bacnet_start() {
  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP,
                                             &got_ip_event, NULL));
  return ESP_OK;
}
