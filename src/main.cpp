#include <Arduino.h>
#include <AirGradient.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <FastLED.h>

#include "board_conf.h"

#define TFT_GREY 0x5AEB // New colour
#define NUM_LEDS 4
#define DATA_PIN 39
#define TFT_BACKLIGHT 15

static AirGradient ag = AirGradient();
static TFT_eSPI tft = TFT_eSPI();
static CRGB leds[NUM_LEDS];

static void LCDPrint(int co2, float temp, int pm2);

void blinkLED() {
  for (size_t i = 0; i < NUM_LEDS; i++) {
    // Turn the LED on, then pause
    leds[i] = CRGB::Red;
    FastLED.show();
  }
  delay(500);

  for (size_t i = 0; i < NUM_LEDS; i++) {
    // Now turn the LED off, then pause
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  delay(500);
}

void setup() {
  Serial.begin(115200);

  // LCD blacklight init
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);
  delay(1000);
  digitalWrite(TFT_BACKLIGHT, LOW);
  delay(1000);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // LED init
  FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);

  // LCD int
  tft.init();
  tft.setRotation(2);

  // Sensors init
  ag.TMP_RH_Init(0x44, CONFIG_SHT30_PIN_SDA, CONFIG_SHT30_PIN_SCL);
  ag.CO2_Init(CONFIG_CO2_PIN_RX, CONFIG_CO2_PIN_TX);
  ag.PMS_Init(CONFIG_PMS_PIN_RX, CONFIG_PMS_PIN_TX);
}

void loop() {  
  TMP_RH result = ag.periodicFetchData();
  Serial.print("Relative Humidity in %: ");
  Serial.println(result.rh);
  Serial.print("Temperature in Celsius: ");
  Serial.println(result.t);
  Serial.print("Temperature in Fahrenheit: ");
  Serial.println((result.t * 9 / 5) + 32);

  int PM2 = ag.getPM2_Raw();
  Serial.print("PM2.5 in ug/m3: ");
  Serial.println(PM2);

  int Co2 = ag.getCO2();
  Serial.print("Co2: ");
  Serial.println(Co2);

  // Display the sensors result on the LCD
  LCDPrint(Co2, result.t, PM2);
  blinkLED();
}

static void LCDPrint(int co2, float temp, int pm2) {
  tft.fillScreen(TFT_BLACK);

  tft.setCursor(40, 40, 2);
  tft.setTextColor(TFT_YELLOW);
  tft.setTextSize(1);
  tft.setTextFont(4);
  tft.println("Air Sensor");

  tft.setCursor(40, 85);
  tft.setTextColor(TFT_RED);
  tft.setTextFont(4);
  tft.print("Temp = ");
  tft.println(temp);

  tft.setCursor(40, 120);
  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(4);
  tft.print("Co2 = ");
  tft.println(co2);

  tft.setCursor(40, 165);
  tft.setTextColor(TFT_GREEN);
  tft.setTextFont(4);
  tft.print("PM2.5 = ");
  tft.println(pm2);
}

