// Setup for the ESP32 S3 with GC9A01 display
#define USER_SETUP_ID 70

#define GC9A01_DRIVER

// Display size
#define TFT_WIDTH  240
#define TFT_HEIGHT 240

// Typical board default pins - change to match your board
#define TFT_SCLK 36 //     12 or 36 (FSPI CLK)
#define TFT_MOSI 35 //     11 or 35 (FSPI D)
#define TFT_CS 10   //     10 or 34 (FSPI CS0)

// Use pins in range 0-31
#define TFT_DC 4
#define TFT_RST 5
// #define TFT_BL -1

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