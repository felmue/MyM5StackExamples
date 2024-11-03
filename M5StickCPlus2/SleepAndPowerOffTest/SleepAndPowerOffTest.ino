// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5StickCPlus2
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified

#include <M5StickCPlus2.h>

#define TEST_DEEP_SLEEP
#define TEST_POWER_OFFx

void setup()
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  M5.begin(cfg);

  M5.Display.setRotation(1);
  M5.Display.setTextSize(2);

#ifdef TEST_DEEP_SLEEP
  // Note: works when powered from battery or USB
  M5.Display.println("Deep sleep in 3 s\n\nPress button A\nto wake up.");
  delay(3000);
  // Set button A to wakeup ESP32 from deep sleep
  esp_sleep_enable_ext0_wakeup((gpio_num_t) GPIO_NUM_37, LOW);
  // Keep power mosfet on while in deep sleep
  gpio_hold_en((gpio_num_t) GPIO_NUM_4);
  gpio_deep_sleep_hold_en();
  esp_deep_sleep_start();
#endif // TEST_DEEP_SLEEP

#ifdef TEST_POWER_OFF
  // Note: only works when powered from battery
  M5.Display.println("Powering off in 3 s\n\nPress power button\nto (re-)start.");
  delay(3000);
  M5.Power.powerOff();
#endif // TEST_POWER_OFF
}

void loop()
{

}

