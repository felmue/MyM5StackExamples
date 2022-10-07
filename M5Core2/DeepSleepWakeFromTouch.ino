// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5Core2.h>

void setup()
{
  M5.begin();

  esp_sleep_enable_ext0_wakeup((gpio_num_t)CST_INT, LOW);
  Serial.println("before deep sleep");
  Serial.flush();
  esp_deep_sleep_start();
  Serial.println("never reached");
  // Never reached - after deep sleep ESP32 restarts
}

void loop()
{
}
