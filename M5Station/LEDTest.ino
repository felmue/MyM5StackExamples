// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// https://github.com/FastLED/FastLED

#include <M5Station.h>
#include <FastLED.h>

#define NEO_PIXEL_NUM 7
#define NEO_PIXEL_PIN 4

#define NEO_PIXEL_BUTTON 3

CRGB NeoPixel[NEO_PIXEL_NUM];

void setup()
{
  M5.begin();

  FastLED.addLeds<SK6812, NEO_PIXEL_PIN, GRB>(NeoPixel, NEO_PIXEL_NUM);
}

void loop()
{
  NeoPixel[NEO_PIXEL_BUTTON] = CRGB::Red;
  FastLED.show();
  delay(500);

  NeoPixel[NEO_PIXEL_BUTTON] = CRGB::Green;
  FastLED.show();
  delay(500);

  NeoPixel[NEO_PIXEL_BUTTON] = CRGB::Blue;
  FastLED.show();
  delay(500);

  NeoPixel[NEO_PIXEL_BUTTON] = CRGB::Black;
  FastLED.show();
  delay(500);
}
