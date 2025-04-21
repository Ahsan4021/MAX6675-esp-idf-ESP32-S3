#include "driver/spi_master.h"

#include "spi_mod.h"

/* SPI Config */
spi_device_handle_t spi_init(void) {
  spi_device_handle_t spi;
  esp_err_t ret;
  spi_bus_config_t buscfg = {
    .miso_io_num = PIN_NUM_MISO,
    .mosi_io_num = PIN_NUM_MOSI,
    .sclk_io_num = PIN_NUM_CLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = (4 * 8)
  };

  //Initialize the SPI bus
  ret = spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);
  ESP_ERROR_CHECK(ret);

  spi_device_interface_config_t devCfg={
    .mode = 0,
    .clock_speed_hz = 2*1000*1000,
    .spics_io_num=10,
    .queue_size=3
  };

  ret = spi_bus_add_device(SPI3_HOST, &devCfg, &spi);
  ESP_ERROR_CHECK(ret);

  return spi;
}
