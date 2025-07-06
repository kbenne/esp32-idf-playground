idf_component_register(SRCS "ethernet_init.c"
                       PRIV_REQUIRES driver esp_eth
                       INCLUDE_DIRS ".")

target_compile_definitions(${COMPONENT_LIB} PRIVATE CONFIG_ETH_USE_SPI_ETHERNET=1 CONFIG_ETH_SPI_ETHERNET_W5500=1)

