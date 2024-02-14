// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/FastLED/FastLED
// https://github.com/adafruit/Adafruit_BMP280_Library
// https://github.com/adafruit/Adafruit_BusIO
// https://github.com/adafruit/Adafruit_Sensor
// https://github.com/Sensirion/arduino-core
// https://github.com/Sensirion/arduino-i2c-sht4x

#include <M5Atom.h>
#include <Adafruit_BMP280.h>
#include <SensirionI2CSht4x.h>

Adafruit_BMP280 bmp; // uses Wire by default
SensirionI2CSht4x sht4x;

float temp, pres, humi;
uint16_t error;
char errorMessage[256];

void setup()
{
  M5.begin(true, false, false);
  Wire.begin(26, 32); // Groove port (red)

  while(!bmp.begin(0x76))
  {
    Serial.println(F("BMP280 init fail"));
  }
  Serial.println(F("BMP280 init success"));
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  uint32_t serialNumber;

  sht4x.begin(Wire, 0x44);
  error = sht4x.serialNumber(serialNumber);
  if(error)
  {
    Serial.print("Error trying to execute serialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else
  {
    Serial.print("Serial Number: ");
    Serial.println(serialNumber);
  }
}

void loop()
{
  pres = bmp.readPressure() / 100;
  Serial.printf("Pres: %2.0f hPa\n", pres);

  error = sht4x.measureHighPrecision(temp, humi);
  if(error)
  {
    Serial.print("Error trying to execute measureHighPrecision(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    temp = 0.0;
    humi = 0.0;
  }
  Serial.printf("Temp: %2.0f\n", temp);
  Serial.printf("Humi: %2.0f %%\n", humi);

  delay(1000);
}
