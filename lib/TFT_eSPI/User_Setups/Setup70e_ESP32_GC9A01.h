// Setup for the ESP32 S3 with GC9A01 display
#pragma once

#include "../../include/board_conf.h"

#define USER_SETUP_ID 70

#define GC9A01_DRIVER

// Display size
#define TFT_WIDTH  CONFIG_TFT_WIDTH
#define TFT_HEIGHT CONFIG_TFT_HEIGHT

#define TFT_SCLK CONFIG_TFT_PIN_SCLK
#define TFT_MOSI CONFIG_TFT_PIN_MOSI
#define TFT_CS CONFIG_TFT_PIN_CS

#define TFT_DC CONFIG_TFT_PIN_DC
#define TFT_RST CONFIG_TFT_PIN_RST
// #define TFT_BL CONFIG_TFT_PIN_BL

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT

// FSPI port (SPI2) used unless following defined.
// HSPI port (SPI3) NOT TESTED YET
#define USE_HSPI_PORT

// Setup for the ESP32 S3 with GC9A01 display
#define SPI_FREQUENCY 40000000