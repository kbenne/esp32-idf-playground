#pragma once
#include "esp_eth.h"
#include "esp_netif.h"
#include "esp_err.h"

// Opaque handle for your Ethernet interface
typedef struct {
    esp_eth_handle_t eth_handle;
    esp_netif_t *eth_netif;
} network_t;

/**
 * @brief  Initialize the Ethernet driver (W5500) and TCP/IP stack
 */
esp_err_t network_init(network_t *net);

/**
 * @brief  Start the Ethernet driver state machine
 */
esp_err_t network_start(network_t *net);

/**
 * @brief  Stop and clean up the Ethernet and TCP/IP interfaces
 */
void network_deinit(network_t *net);
