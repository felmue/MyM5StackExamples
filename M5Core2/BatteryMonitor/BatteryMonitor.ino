// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified

#include <M5Unified.h>

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setTextSize(2);
}

void loop()
{
  int32_t bc = M5.Power.getBatteryCurrent();
  int32_t bl = M5.Power.getBatteryLevel();
  int16_t bv = M5.Power.getBatteryVoltage();
  m5::Power_Class::is_charging_t ic = M5.Power.isCharging();

  M5.Display.setCursor(0, 0);
  M5.Display.printf("Battery Monitor v 1.1\n\n");
  M5.Display.printf("Charge Current: %03d mA\n", bc);
  M5.Display.printf("Level         : %03d %%\n", bl);
  M5.Display.printf("Voltage       : %04d mV\n", bv);
  M5.Display.printf("Is Charging   : %01d\n", ic);

  delay(1000);
}
