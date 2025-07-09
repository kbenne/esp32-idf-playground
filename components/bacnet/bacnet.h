#pragma once
#include "esp_err.h"

// static int DEVICE_INSTANCE; // = 4194303;

esp_err_t bacnet_init();

esp_err_t bacnet_start();
