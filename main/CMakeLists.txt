idf_component_register(SRCS 
                    "esp-idf-demo.c"
                    "ethernet_config.c"
                    INCLUDE_DIRS "."
                    REQUIRES bacnet esp_netif esp_eth driver esp_timer)