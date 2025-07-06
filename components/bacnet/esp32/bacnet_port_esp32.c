/**
 * @file bacnet_port_esp32.c
 * @brief BACnet stack port for ESP32
 * @author Claude
 * @date 2025
 */

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bacnet_port_esp32.h"

/* Include the BACnet stack headers */
#include "bacnet/basic/binding/address.h"
#include "bacnet/basic/object/device.h"
#include "bacnet/basic/service/h_whois.h"
#include "bacnet/basic/service/h_rp.h"
#include "bacnet/basic/service/h_wp.h"
#include "bacnet/basic/service/h_cov.h"
#include "bacnet/basic/service/h_dcc.h"
#include "bacnet/basic/service/h_iam.h"
#include "bacnet/basic/services.h"
#include "bacnet/datalink/bip.h"
#include "bacnet/datalink/bvlc.h"
#include "bacnet/datalink/datalink.h"
#include "bacnet/bacdef.h"
#include "bacnet/npdu.h"
#include "bacnet/apdu.h"
#include "bacnet/basic/tsm/tsm.h"
#include "bacnet/basic/sys/keylist.h"
#include "bacnet/basic/object/objects.h"
#include "bacnet/basic/sys/mstimer.h"
#include "bacnet/basic/sys/fifo.h"
#include "bacnet/bacstr.h"
#include "bacnet/dcc.h"

static const char *TAG = "bacnet_esp32";
static bool initialized = false;

bool bacnet_esp32_init(uint32_t device_instance, const char *device_name)
{
    ESP_LOGI(TAG, "Initializing BACnet stack for ESP32");
    
    /* Initialize device object */
    Device_Init(NULL);
    
    /* Set device instance ID and name */
    Device_Set_Object_Instance_Number(device_instance);
    if (device_name) {
        BACNET_CHARACTER_STRING bacnet_name;
        characterstring_init_ansi(&bacnet_name, device_name);
        Device_Set_Object_Name(&bacnet_name);
    }
    
    /* Initialize the datalink layer - this will call bip_init() from bacnet.c */
    if (!datalink_init(NULL)) {
        ESP_LOGE(TAG, "Failed to initialize datalink layer");
        return false;
    }
    
    /* Initialize the millisecond timer */
    mstimer_init();
    
    /* Initialize device address binding table */
    address_init();
    
    /* Initialize transaction state machine */
    /* Note: The BACnet stack actually doesn't have a tsm_init function exposed
       The internal data is static and initialized when used */
    
    /* Set up the confirmed service handlers */
    apdu_set_confirmed_ack_handler(SERVICE_CONFIRMED_READ_PROPERTY, handler_read_property_ack);
    apdu_set_confirmed_handler(SERVICE_CONFIRMED_READ_PROPERTY, handler_read_property);
    apdu_set_confirmed_handler(SERVICE_CONFIRMED_WRITE_PROPERTY, handler_write_property);
    apdu_set_confirmed_handler(SERVICE_CONFIRMED_SUBSCRIBE_COV, handler_cov_subscribe);
    
    /* Set up unconfirmed service handlers */
    apdu_set_unconfirmed_handler(SERVICE_UNCONFIRMED_WHO_IS, handler_who_is);
    /* There's no direct handler_i_am function in the stack, as I-AM is typically sent, not received
       The I-AM binding is handled by handler_i_am_add and handler_i_am_bind */
    
    /* Start the BACnet stack timer */
    ESP_LOGI(TAG, "BACnet stack initialized - Device ID: %u, Name: %s", 
             device_instance, device_name ? device_name : "Unknown");
    
    initialized = true;
    return true;
}

void bacnet_esp32_task(uint16_t milliseconds)
{
    if (!initialized) {
        return;
    }
    
    /* Handle BACnet communication tasks */
    uint16_t pdu_len = 0;
    BACNET_ADDRESS src = {0};
    uint8_t rx_buf[MAX_MPDU] = {0};
    
    /* Process received BACnet packets */
    pdu_len = datalink_receive(&src, &rx_buf[0], MAX_MPDU, milliseconds);
    if (pdu_len) {
        npdu_handler(&src, &rx_buf[0], pdu_len);
    }
    
    /* Handle any pending timeouts of confirmed requests */
    tsm_timer_milliseconds(milliseconds);
    
    /* Handle COV subscriptions */
    handler_cov_timer_seconds(milliseconds / 1000);
    
    /* Handle Device Communication Control timer */
    dcc_timer_seconds(milliseconds / 1000);
    
    /* Handle any other periodic tasks as needed */
}