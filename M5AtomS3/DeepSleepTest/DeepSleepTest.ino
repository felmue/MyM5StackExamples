// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// M5AtomS3 powered via Groove port: 5 V
// Measured current in deep sleep: 257 uA
// Measured with: EEVblog uCurrent Gold

#include "M5AtomS3.h"

void setup()
{
  M5.begin();
  M5.Lcd.println("Deep Sleep Test");
  delay(3000);
  esp_sleep_enable_timer_wakeup(1000L * 1000L * 10L);
  esp_deep_sleep_start();
}

void loop()
{

}
