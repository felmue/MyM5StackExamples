// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5Dial
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified

#include "M5Dial.h"

void setup()
{
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  delay(3000);
  Serial.println("Sleep tests");
}

void loop()
{
  Serial.println("in loop - before");
  Serial.flush();
  delay(1000);

  // Deep sleep - wakeup from touch screen
//  esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, LOW);
//  esp_deep_sleep_start();

  // Light sleep - wakeup from touch screen
//  esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, LOW);
//  esp_light_sleep_start();

  // Light sleep - wakeup from dial button
  gpio_wakeup_enable(GPIO_NUM_42, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  esp_light_sleep_start();

  // Note: never reached after deep sleep
  Serial.println("");
  Serial.println("in loop - after");
  Serial.flush();
  delay(1000);
}
