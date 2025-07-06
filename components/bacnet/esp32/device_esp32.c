/**
 * @file device_esp32.c
 * @brief BACnet Device object with simplified object table for ESP32
 * @author Claude
 * @date 2025
 */

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "bacnet/config.h"
#include "bacnet/bacdef.h"
#include "bacnet/bacdcode.h"
#include "bacnet/bacstr.h"
#include "bacnet/basic/binding/address.h"
#include "bacnet/basic/object/device.h"
#include "bacnet/basic/object/ai.h"
#include "bacnet/basic/object/ao.h"
#include "bacnet/basic/object/av.h"
#include "bacnet/basic/object/bi.h"
#include "bacnet/basic/object/bo.h"
#include "bacnet/basic/object/bv.h"

static const char *TAG = "device_esp32";

/* Forward declarations for stub objects */
/* Add stub for Device_Value_List_Supported to fix the h_cov.c dependency */
bool Device_Value_List_Supported(BACNET_OBJECT_TYPE object_type)
{
    return false;
}

/* Reduced object table with just the basic objects */
static object_functions_t My_Object_Table[] = {
    {OBJECT_DEVICE, NULL, Device_Count, Device_Index_To_Instance,
        Device_Valid_Object_Instance_Number, Device_Object_Name,
        Device_Read_Property_Local, Device_Write_Property_Local,
        Device_Property_Lists, NULL /* ReadRangeInfo */ , NULL /* Iterator */ ,
        NULL /* Value_Lists */ , NULL /* COV */ , NULL /* COV Clear */ ,
        NULL /* Intrinsic Reporting */ , NULL /* Aggregate List */},
    {MAX_BACNET_OBJECT_TYPE}
};

/* Override Device_Objects_Find_Functions to use our reduced object table */
bool Device_Objects_Find_Functions(
    BACNET_OBJECT_TYPE object_type,
    object_functions_t *object_functions)
{
    bool status = false;
    unsigned index = 0;

    while (My_Object_Table[index].Object_Type != MAX_BACNET_OBJECT_TYPE) {
        if (object_type == My_Object_Table[index].Object_Type) {
            memcpy(object_functions, &My_Object_Table[index],
                sizeof(object_functions_t));
            status = true;
            break;
        }
        index++;
    }

    return status;
}

/* Stub for broadcast_address functionality */
bool bip_get_broadcast_address(BACNET_IP_ADDRESS *dest)
{
    if (dest) {
        dest->address[0] = 192;
        dest->address[1] = 168;
        dest->address[2] = 1;
        dest->address[3] = 255;
        dest->port = 0xBAC0;
        return true;
    }
    return false;
}