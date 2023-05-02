#include <Arduino.h>
#include <AirGradient.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#define TFT_GREY 0x5AEB // New colour
#define CO2_TX_PIN 6
#define CO2_RX_PIN 7

static AirGradient ag = AirGradient();
static TFT_eSPI tft = TFT_eSPI();

static void LCDPrint(int co2, float temp);

void setup() {
  Serial.begin(115200);

  // LCD int
  tft.init();
  tft.setRotation(1);

  // Sensors init
  ag.TMP_RH_Init(0x44);
  ag.CO2_Init(CO2_RX_PIN, CO2_TX_PIN);
}

void loop() {
  int CO2 = ag.getCO2_Raw();
  TMP_RH result = ag.periodicFetchData();

  Serial.print("Relative Humidity in %: ");
  Serial.println(result.rh);

  Serial.print(" Temperature in Celcius: ");
  Serial.println(result.t);

  Serial.print(" Temperature in Fahrenheit: ");
  Serial.println((result.t * 9 / 5) + 32);

  LCDPrint(CO2, result.t);
  // delay(1000);
}

static void LCDPrint(int co2, float temp) {
  tft.fillScreen(TFT_GREY);

  tft.setCursor(40, 40, 2);
  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(4);
  tft.setTextSize(1);

  tft.print("Temperature = "); tft.println(temp);
  tft.setCursor(40, 62);
  tft.print("Co2 = "); tft.println(co2);
}