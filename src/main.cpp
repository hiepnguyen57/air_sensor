#include <Arduino.h>
#include <AirGradient.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "board_conf.h"

#define TFT_GREY 0x5AEB // New colour

static AirGradient ag = AirGradient();
static TFT_eSPI tft = TFT_eSPI();

static void LCDPrint(int co2, float temp);

void setup() {
  Serial.begin(115200);

  // LCD int
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_GREY);

  // Sensors init
  ag.TMP_RH_Init(0x44, CONFIG_SHT30_PIN_SDA, CONFIG_SHT30_PIN_SCL);
  ag.CO2_Init(CONFIG_CO2_PIN_RX, CONFIG_CO2_PIN_TX);
}

void loop() {  
  TMP_RH result = ag.periodicFetchData();

  Serial.print("Relative Humidity in %: ");
  Serial.println(result.rh);

  Serial.print("Temperature in Celsius: ");
  Serial.println(result.t);

  Serial.print("Temperature in Fahrenheit: ");
  Serial.println((result.t * 9 / 5) + 32);

  int Co2 = ag.getCO2_Raw();
  Serial.print("Co2 raw: ");
  Serial.println(String(Co2));
  LCDPrint(Co2, result.t);
}

static void LCDPrint(int co2, float temp) {
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

  tft.setCursor(40, 110);
  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(4);
  tft.print("Co2 = ");
  tft.println(co2);

  delay(5000);
}

