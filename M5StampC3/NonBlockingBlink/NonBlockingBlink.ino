// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// https://github.com/adafruit/Adafruit_NeoPixel
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     2
#define NUMPIXELS   1
#define MY_INTERVAL 1000

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t nextTime = 0;
bool myFlag = false;

void setup()
{
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();
}

void loop()
{
  if((millis() - nextTime) > MY_INTERVAL)
  {
    nextTime = millis();
    myFlag = !myFlag;
    if(myFlag == true)
    {
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    }
    else
    {
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    }
    pixels.show();
  }

  // Do other stuff here

}
