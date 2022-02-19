#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

#define DATA_PIN 11
#define CLK_PIN 13
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

Adafruit_BME280 bme;

void setup() {
  myDisplay.begin();
  myDisplay.setIntensity(5);
  myDisplay.displayClear();
  bme.begin(0x76);
}

void loop() {
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
      float temp = bme.readTemperature();
      float press = bme.readPressure() / 100.0F;
      float hum = bme.readHumidity();
      char text[200];
      int ret = snprintf(text, sizeof text, "%.1f C   %.1f hPa   %.1f %%", temp, press, hum);
      myDisplay.displayText(text , PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}