/*
 * W5500 Ethernet Initialization Component
 *
 * Simplified from ESP-IDF ethernet_init example component
 * to focus only on W5500 SPI Ethernet controller
 */

#include "ethernet_init.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_mac.h"

static const char *TAG = "w5500_eth_init";

/**
 * @brief Initialize SPI bus for W5500 Ethernet controller
 *
 * @return
 *          - ESP_OK on success
 *          - ESP_FAIL or other error code on failure
 */
static esp_err_t spi_bus_init(void) {
  esp_err_t ret = ESP_OK;

  /* Install GPIO ISR handler for W5500 interrupt */
  ret = gpio_install_isr_service(0);
  if (ret != ESP_OK) {
    if (ret == ESP_ERR_INVALID_STATE) {
      ESP_LOGW(TAG, "GPIO ISR handler has been already installed");
      ret = ESP_OK; /* ISR handler already installed, no problem */
    } else {
      ESP_LOGE(TAG, "GPIO ISR handler install failed");
      return ret;
    }
  }

  /* Initialize SPI bus */
  spi_bus_config_t buscfg = {
      .miso_io_num = W5500_SPI_MISO_GPIO,
      .mosi_io_num = W5500_SPI_MOSI_GPIO,
      .sclk_io_num = W5500_SPI_SCLK_GPIO,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
  };

  ESP_LOGI(TAG, "Initializing SPI bus (MISO:%d, MOSI:%d, SCLK:%d, CS:%d)",
           W5500_SPI_MISO_GPIO, W5500_SPI_MOSI_GPIO, W5500_SPI_SCLK_GPIO,
           W5500_SPI_CS_GPIO);

  ESP_RETURN_ON_ERROR(
      spi_bus_initialize(W5500_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO), TAG,
      "Failed to initialize SPI bus");

  return ESP_OK;
}

esp_err_t w5500_eth_init(esp_eth_handle_t *eth_handle_out) {
  esp_err_t ret = ESP_OK;
  esp_eth_handle_t eth_handle = NULL;

  /* Create MAC and PHY instances */
  esp_eth_mac_t *mac = NULL;
  esp_eth_phy_t *phy = NULL;

  /* Check parameters */
  ESP_RETURN_ON_FALSE(eth_handle_out != NULL, ESP_ERR_INVALID_ARG, TAG,
                      "eth_handle_out cannot be NULL");

  /* Initialize SPI bus */
  ESP_GOTO_ON_ERROR(spi_bus_init(), err, TAG, "SPI bus initialization failed");

  /* Configure SPI device for W5500 */
  spi_device_interface_config_t devcfg = {
      .command_bits = 0,
      .address_bits = 0,
      .dummy_bits = 0,
      .mode = 0,
      .clock_speed_hz = W5500_SPI_CLOCK_MHZ * 1000 * 1000,
      .spics_io_num = W5500_SPI_CS_GPIO,
      .queue_size = 20,
  };

  /* Initialize MAC and PHY configs */
  eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
  eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();

  /* Set PHY reset GPIO if configured */
  phy_config.reset_gpio_num = W5500_RESET_GPIO;

  /* Configure W5500 specific settings */
  eth_w5500_config_t w5500_config =
      ETH_W5500_DEFAULT_CONFIG(W5500_SPI_HOST, &devcfg);
  w5500_config.int_gpio_num = W5500_INT_GPIO;

  mac = esp_eth_mac_new_w5500(&w5500_config, &mac_config);
  phy = esp_eth_phy_new_w5500(&phy_config);

  ESP_GOTO_ON_FALSE(mac != NULL && phy != NULL, ESP_FAIL, err, TAG,
                    "Failed to create MAC or PHY instance");

  /* Install Ethernet driver */
  esp_eth_config_t config = ETH_DEFAULT_CONFIG(mac, phy);
  ESP_GOTO_ON_ERROR(esp_eth_driver_install(&config, &eth_handle), err, TAG,
                    "Ethernet driver installation failed");

  /* Set MAC address (use ESP32's base MAC address with locally administered bit
   * set) */
  uint8_t mac_addr[6];
  ESP_GOTO_ON_ERROR(esp_read_mac(mac_addr, ESP_MAC_ETH), err, TAG,
                    "Failed to get MAC address");

  /* Set locally administered bit */
  mac_addr[0] |= 0x02;
  ESP_GOTO_ON_ERROR(esp_eth_ioctl(eth_handle, ETH_CMD_S_MAC_ADDR, mac_addr),
                    err, TAG, "Failed to set MAC address");

  /* Return the Ethernet handle */
  *eth_handle_out = eth_handle;
  ESP_LOGI(TAG, "W5500 Ethernet driver initialized successfully");
  ESP_LOGI(TAG, "MAC address: %02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0],
           mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

  return ESP_OK;

err:
  /* Clean up in case of error */
  if (eth_handle != NULL) {
    esp_eth_driver_uninstall(eth_handle);
  }
  if (mac != NULL) {
    mac->del(mac);
  }
  if (phy != NULL) {
    phy->del(phy);
  }
  spi_bus_free(W5500_SPI_HOST);
  return ret;
}
