idf_component_register(SRCS 
                    "esp-idf-demo.c"
                    INCLUDE_DIRS "."
                    REQUIRES bacnet esp_netif esp_eth driver esp_timer spi_flash esp_hw_support network)
