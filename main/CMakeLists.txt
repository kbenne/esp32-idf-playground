idf_component_register(SRCS 
                    "esp-idf-demo.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_netif esp_eth driver esp_timer spi_flash esp_hw_support ethernet_init)
