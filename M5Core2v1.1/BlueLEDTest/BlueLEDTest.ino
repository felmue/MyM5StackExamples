// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified
//
// Note: by default the blue LED indicates the battery charging state.
//       In order to control it, the mode needs to be set to manual.

#include <M5Unified.h>

#define AXP2101_ADDR 0x34
#define CHG_LED_CFG  0x69
#define CHG_LED_MAN  0b00000101 // Manual mode
#define CHG_LED_ON   0b00110000
#define CHG_LED_OFF  0b00000000

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
}

void loop()
{
  M5.In_I2C.writeRegister8(AXP2101_ADDR, CHG_LED_CFG, CHG_LED_MAN | CHG_LED_ON, 200000);
  delay(50);
  M5.In_I2C.writeRegister8(AXP2101_ADDR, CHG_LED_CFG, CHG_LED_MAN | CHG_LED_OFF, 200000);
  delay(2000);
}
