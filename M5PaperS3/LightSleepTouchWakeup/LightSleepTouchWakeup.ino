// Copyright (c) 2025 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Notes:
// - Touch wake-up is only possible in ESP light sleep.
// - Touch wake-up from ESP deep sleep is NOT possible as that would require the touch
//    interrupt line to be connected to a so called RTC GPIO which is not the case in M5PaperS3.
// - Touch wake-up from shutdown mode is NOT possible as the eInk display and touch IC are
//    not running in shutdown mode.

#include <epdiy.h>
#include <M5Unified.h>

void setup(void)
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  cfg.internal_imu = false;
  M5.begin(cfg);

  M5.Display.setTextSize(5);
  if (M5.Display.isEPD())
  {
    M5.Display.setEpdMode(epd_mode_t::epd_fastest);
  }
  M5.Display.setRotation(M5.Display.getRotation() ^ 1);

  delay(2000);
  Serial.printf("Starting...\n");

  // LED on (Note: inverted)
  M5.Power.setLed(0);
}

void myPrintText(String t)
{
  M5.Display.startWrite();
  M5.Display.println(t.c_str());
  M5.Display.endWrite();
  delay(100);
  Serial.println(t.c_str());
  Serial.flush();
}

void loop()
{
  // Clear out old touch interrupts
  M5.update();
  delay(150);
  M5.update();
  delay(150);
  M5.update();
  delay(150);
  // Clear display
  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.fillScreen(TFT_WHITE);

  M5.Display.setCursor(0, 0);
  myPrintText("Light sleep touch test");
  myPrintText("Going to light sleep now");
  myPrintText("Touch to wake up");
  // LED off (Note: inverted)
  M5.Power.setLed(255);
  delay(100);
  // Touch interrupt is connected to GPIO48 which in NOT an RTC GPIO,
  //  therefore touch wakeup only works with light sleep.
  gpio_wakeup_enable((gpio_num_t) GPIO_NUM_48, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  esp_light_sleep_start();
  gpio_wakeup_disable((gpio_num_t) GPIO_NUM_48);

  myPrintText("Awake after light sleep");
  // LED on (Note: inverted)
  M5.Power.setLed(0);
  delay(2000);
}
