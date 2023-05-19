// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5Tough.h>

void setup()
{
  M5.begin(true, false, true, false);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Light Sleep Test");
  delay(3000);
}

void loop()
{
  gpio_wakeup_enable((gpio_num_t) CST_INT, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  M5.Axp.SetLDOEnable(3, false);
  Serial.println("before light sleep");
  Serial.flush();
  esp_light_sleep_start();
  Serial.println("after light sleep");
  M5.Axp.SetLDOEnable(3, true);
  delay(3000);
}
