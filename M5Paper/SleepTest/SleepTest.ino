// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5EPD.h>

M5EPD_Canvas canvas(&M5.EPD);

void setup()
{
  M5.begin();
  M5.EPD.SetRotation(90);
  M5.EPD.Clear(true);
  canvas.createCanvas(540, 960);
  canvas.setTextSize(5);
  canvas.drawString("Touch The Screen!", 20, 400);
  canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void loop()
{
  // Clear out all previous touch screen interrupts
  while(digitalRead(GPIO_NUM_36) == LOW)
  {
    M5.TP.flush();
    delay(10);
  }

  Serial.println("before sleep");
  Serial.flush();
  delay(1000);

  // Enable timer (10 s)
  esp_sleep_enable_timer_wakeup(10 * 1000000UL);

  // Enable touch screen
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_36, LOW);

  // Test light sleep or ...
//  esp_light_sleep_start();

  // ... test deep sleep
  // Keep power mosfet on while in deep sleep
  gpio_hold_en((gpio_num_t) M5EPD_MAIN_PWR_PIN);
  gpio_deep_sleep_hold_en();
  esp_deep_sleep_start();

  // Only reached after light sleep
  Serial.println("after sleep");
  delay(1000);
}
