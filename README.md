# 🌡️ MAX6675 Thermocouple SPI Interface (ESP-IDF, ESP32-S3)

This project demonstrates how to interface the **MAX6675** thermocouple-to-digital converter with an **ESP32-S3** using **raw SPI** via the **Espressif ESP-IDF framework**.

It performs a low-level SPI transaction to read temperature data, process the result, and log it periodically using a FreeRTOS task. The code is clean, modular, and easily adaptable to other SPI-based sensors or ESP32 variants.

---

## 📦 Features

- 🔌 Interfaces directly with the MAX6675 using raw SPI
- 🌡️ Converts 12-bit sensor data to temperature in °C
- 🧠 Detects disconnected thermocouple via error bit
- ⏲️ Periodic polling using FreeRTOS
- 📟 Serial output of temperature readings
- 🧩 Modular structure with dedicated SPI config module

---

## 🧰 Hardware Requirements

| Component             | Qty | Notes                                   |
|-----------------------|-----|-----------------------------------------|
| ESP32-S3 Dev Board    | 1   | Using SPI3_HOST                         |
| MAX6675 Module        | 1   | Works with K-type thermocouples         |
| K-type Thermocouple   | 1   | For temperature measurement             |
| Jumper Wires          | -   | For wiring the sensor to ESP32          |
| USB Cable             | 1   | To power and program the ESP32 board    |

---

## 🔌 Pin Configuration

Defined in `pins.h`:

| Signal | GPIO | MAX6675 Pin |
|--------|------|-------------|
| MISO   | 13   | SO          |
| MOSI   | 11   | (Unused)    |
| CLK    | 12   | SCK         |
| CS     | 10   | CS          |

> **Note:** MAX6675 is a **read-only** device. MOSI is unused but required in the ESP-IDF SPI config.

---

## 📁 File Structure
project_root/ ├── main/ │ ├── main.c // Main FreeRTOS task to poll MAX6675 │ ├── spi_mod.c // SPI config and init logic │ ├── spi_mod.h // Header for spi_mod.c │ └── pins.h // GPIO pin assignments ├── CMakeLists.txt └── README.md // You're reading it!

## 🔧 How It Works

1. Initializes SPI bus with `spi_init()` from `spi_mod.c`
2. Creates a FreeRTOS task (`temp_task`) in `main.c`
3. Every second, the task:
   - Starts a 16-bit SPI read
   - Checks bit 2 for thermocouple presence
   - Shifts the 12-bit result and multiplies by 0.25
4. Logs temperature in Celsius or error message if disconnected

---

## 💡 Sample Code Snippets

**Reading and processing MAX6675 data:**

```c
spi_transaction_t tM = {
  .tx_buffer = NULL,
  .rx_buffer = &data,
  .length = 16,
  .rxlength = 16,
};

spi_device_transmit(spi, &tM);
int16_t res = (int16_t) SPI_SWAP_DATA_RX(data, 16);

if (res & (1 << 2)) {
  ESP_LOGE(TAG, "Sensor is not connected\n");
} else {
  res >>= 3;
  printf("SPI res = %d temp = %.2f °C\n", res, res * 0.25);
}
```


## 🧪 Example Serial Output
SPI res = 104 temp = 26.00 °C
SPI res = 112 temp = 28.00 °C
E (12345) main: Sensor is not connected
---

## 🎯 Motivation
It is hard to get a working example of a raw SPI device using ESP-IDF, especially with sensors like the MAX6675. This project provides a clean, working solution with direct SPI interaction — no extra libraries required.

Please feel free to fork, adapt, improve, or contribute!
---
## 🔄 Compatibility

ESP32 Variant	Status	Notes
ESP32-S3	✅ Tested	Uses SPI3_HOST
ESP32-C3	⚠️ Untested	May require different SPI host
ESP32-S2	⚠️ Untested	Update host and GPIOs
ESP32 (Original)	⚠️ Untested	Use SPI2_HOST and update pins
---

## 📦 Dependencies
ESP-IDF v4.x or later

No external libraries required

Uses standard ESP-IDF SPI and FreeRTOS components

## 📜 License
MIT License
---
Made with ❤️ to help developers integrate MAX6675 with ESP32 the low-level way.


