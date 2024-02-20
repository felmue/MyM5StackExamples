// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based upon: I2C scanner for M5Tough
// Adapted to: M5Dial
//
// https://github.com/m5stack/M5Dial
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified

#include "M5Dial.h"

void scanI2C(m5::I2C_Class* scanWire)
{
  bool result[0x80];

  M5Dial.Lcd.clearDisplay(TFT_BLACK);
  M5Dial.Lcd.setFont(&fonts::Font4);
  M5Dial.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5Dial.Lcd.setCursor(0, M5Dial.Lcd.height() / 2 - 6);

  if(scanWire == &M5.In_I2C) M5Dial.Lcd.print("Int.");
  else M5Dial.Lcd.print("Ext.");

  M5Dial.Lcd.setCursor(200, M5Dial.Lcd.height() / 2 - 6);
  M5Dial.Lcd.print("I2C");

  M5Dial.Lcd.setFont(&fonts::AsciiFont8x16);
  scanWire->scanID(result);
  for(int i = 0x08; i < 0x78; ++i)
  {
    bool hit = result[i];
    std::size_t y = i >> 3;
    std::size_t x = i & 7;
    M5Dial.Lcd.setCursor(50 + x * 18, 7 + y * 14);
    M5Dial.Lcd.setTextColor(hit ? TFT_BLACK : TFT_LIGHTGRAY , hit ? TFT_GREEN : TFT_WHITE);
    M5Dial.Lcd.printf("%02x", i);
  }
}

void setup()
{
  auto cfg = M5.config();
  M5Dial.begin(cfg, false, false);
}

void loop()
{
  scanI2C(&M5.In_I2C);
  delay(3000);
  scanI2C(&M5.Ex_I2C);
  delay(3000);
}
