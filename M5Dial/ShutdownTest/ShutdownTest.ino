// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5Dial
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified
//
// Notes:
// - M5Dial can only shutdown when powered from battery.
// - M5Dial cannot shutdown when powered from USB-C.
// - M5Dial cannot shutdown when powered from green connector. *)
//
// *) This is due to a connection between +5VIN and M5V of the M5StampS3
//    which keeps the M5StampS3 powered even though the MOSFET is off.
//    See schematic here: https://docs.m5stack.com/en/core/M5Dial 
#include "M5Dial.h"

void setup()
{
  auto cfg = M5.config();
  M5Dial.begin(cfg, false, false);

  delay(3000);

//  // Shutdown with timer
//  // Note: Power on by pressing wake button or after 30 seconds by RTC
//  M5Dial.Power.timerSleep(30);

  // Shutdown w/o timer
  // Note: Power on by pressing wake button
  M5Dial.Power.powerOff();
}

void loop()
{

}
