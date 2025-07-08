idf_component_register(SRCS
                       "network.c"
                       "w5500_eth.c"
                       PRIV_REQUIRES driver esp_eth esp_netif esp_eth driver esp_timer spi_flash esp_hw_support 
                       INCLUDE_DIRS ".")

target_compile_definitions(${COMPONENT_LIB} PRIVATE CONFIG_ETH_USE_SPI_ETHERNET=1 CONFIG_ETH_SPI_ETHERNET_W5500=1)

