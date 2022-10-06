// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5Core2.h>

void setup()
{
  M5.begin();
}

void loop()
{
  gpio_wakeup_enable((gpio_num_t) CST_INT, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  Serial.println("before light sleep");
  Serial.flush();
  esp_light_sleep_start();
  Serial.println("after light sleep");
  delay(3000);
}
