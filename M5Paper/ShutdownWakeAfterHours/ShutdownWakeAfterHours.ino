// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5EPD.h>

M5EPD_Canvas canvas(&M5.EPD);
rtc_date_t myDate;
rtc_time_t myTime;

void setup()
{
  // Enable everything except SD and RTC
  M5.begin(true, false, true, true, true);
  // Read wake up reason before RTC begin which clears interrupts
  uint8_t data = M5.RTC.readReg(0x01);
  // Start RTC and clear interrupt
  M5.RTC.begin();
  // Setup paper display
  M5.EPD.SetRotation(0);
  M5.EPD.Clear(true);
  canvas.createCanvas(960, 540);
  canvas.setTextSize(3);
  // Check alarm flag
  if((data & 0b00001000) == 0b00001000)
  {
    canvas.drawString("Power on by RTC", 0, 0);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
  }
  else
  {
    canvas.drawString("Power on by power button", 0, 0);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
    // Small delay to allow paper display to update
    delay(250);
    // Set RTC date and time (arbitrarily)
    myDate.year = 1900;
    myDate.mon = 1;
    myDate.day = 1;
    myTime.hour = 0;
    myTime.min = 0;
    myTime.sec = 0;
    M5.RTC.setDate(&myDate);
    M5.RTC.setTime(&myTime);
    // Set alarm time 7 hours from now
    myTime.hour += 7;
    M5.shutdown(myDate, myTime);
  }
}

void loop()
{
  delay(100);
}
