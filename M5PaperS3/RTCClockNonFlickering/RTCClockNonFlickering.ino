// Copyright (c) 2025 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Note: requires the following PRs so M5PaperS3 can power up without the eInk display flickering
// - https://github.com/m5stack/M5GFX/pull/113
// - https://github.com/m5stack/M5Unified/pull/144
// Note: requires the folowing PR so M5PaperS3 can fully shutdown
// - https://github.com/m5stack/M5Unified/pull/141

// This RTC clock example keeps the system mostly in shutdown mode and
//  only wakes up every 58 seconds for a brief period of time during
//  which the time and date are updated on the eInk display.
//
// When started initially or via power button a full eInk display refresh
//  is executed to clear the display.
// The current time and date are fetched via NTP and shown on the eInk display.
// After waiting for the full minute the system is put into shutdown
//  mode for about 58 seconds.
// When the RTC timer expires (just befor the next minute change) the
//  system is powered on.
// The eInk display is updated with the current time and date.
// Then the system goes back into shutdown mode for about 58 seconds and
//  the cycle begins anew.
// Every hour a full eInk display refresh is executed to keep the ink
//  display crisp.

#include <epdiy.h>
#include <M5Unified.h>
#include <WiFi.h>
#include "time.h"

const char* ssid             = "YOUR_SSID";
const char* password         = "YOUR_PASSWORD";
const char* ntpServer        = "pool.ntp.org";
const long gmtOffset_sec     = 3600;
const int daylightOffset_sec = 3600;

// every hour at minute 45 do a full ink display refresh
#define FULL_REFRESH_MINUTE (45)

bool bRTCRestart = false;

void printLocalTimeAndSetRTC()
{
  struct tm timeinfo;

  if(getLocalTime(&timeinfo) == false)
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  m5::rtc_time_t time;
  time.hours = timeinfo.tm_hour;
  time.minutes = timeinfo.tm_min;
  time.seconds = timeinfo.tm_sec;
  M5.Rtc.setTime(&time);

  m5::rtc_date_t date;
  date.date = timeinfo.tm_mday;
  date.month = timeinfo.tm_mon + 1;
  date.year = timeinfo.tm_year + 1900;
  M5.Rtc.setDate(&date);
}

void getNTPTime()
{
  // Try to connect for 10 seconds
  uint32_t connect_timeout = millis() + 10000;

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while((WiFi.status() != WL_CONNECTED) && (millis() < connect_timeout))
  {
    delay(500);
    Serial.print(".");
  }
  if(WiFi.status() != WL_CONNECTED)
  {
    // WiFi connection failed - set fantasy time and date
    m5::rtc_time_t time;
    time.hours = 6;
    time.minutes = 43;
    time.seconds = 50;
    M5.Rtc.setTime(&time);

    m5::rtc_date_t date;
    date.date = 4;
    date.month = 12;
    date.year = 2032;
    M5.Rtc.setDate(&date);
    return;
  }

  Serial.println("Connected");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTimeAndSetRTC();

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void drawTimeAndDate(m5::rtc_time_t time, m5::rtc_date_t date)
{
  char buf[11];

  M5.Display.startWrite();
  snprintf(buf, 6, "%02d:%02d", time.hours, time.minutes);
  M5.Display.drawString(buf, 180, 20, &AsciiFont24x48);
  snprintf(buf, 11, "%02d.%02d.%02d", date.date, date.month, date.year - 2000);
  M5.Display.drawString(buf, 6, 280, &AsciiFont24x48);
  M5.Display.endWrite();
}

void setup(void)
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  cfg.internal_imu = false;
  cfg.internal_rtc = false;
  cfg.clear_display = false;
  M5.begin(cfg);

  uint8_t data = M5.Rtc.readRegister8(0x01);
  if(M5.In_I2C.isEnabled())
  {
    Serial.printf("*** RTC begin\n");
    M5.Rtc.begin();
  }
  Serial.printf("*** data: %X\n", data);
  if((data & 0b00000101) == 0b00000101)
  {
    bRTCRestart = true;
  }
  M5.Rtc.disableIRQ();
  M5.Rtc.clearIRQ();
  uint8_t data2 = M5.Rtc.readRegister8(0x01);
  Serial.printf("*** data2: %X\n", data2);

  M5.Power.setLed(127);

  M5.Display.setTextSize(5.0);
  if (M5.Display.isEPD())
  {
    M5.Display.setEpdMode(epd_mode_t::epd_fastest);
  }
  M5.Display.setRotation(M5.Display.getRotation() ^ 1);

  m5::rtc_time_t time;
  m5::rtc_date_t date;

  if(bRTCRestart == true)
  {
    Serial.println("Power on by: RTC timer");

    M5.Rtc.getTime(&time);
    M5.Rtc.getDate(&date);

    // Full refresh once per hour
    if(time.minutes == FULL_REFRESH_MINUTE - 1)
    {
      // Full ink display init
      M5.Display.getPanel()->clearDisplay();
    }
  }
  else
  {
    Serial.println("Power on by: power button");

    // Full ink display init
    M5.Display.getPanel()->clearDisplay();

    // Fetch current time from Internet
    getNTPTime();
    M5.Rtc.getTime(&time);
    M5.Rtc.getDate(&date);
  }

  // After every shutdown the eInk buffer is initialized anew.
  // But the eInk buffer doesn't match the current image on the
  //  ink display therefore the same time and date, as have been
  //  drawn before the shutdown, are redrawn.
  // This is required, else drawing new time and date only adds
  //  pixels to the already drawn pixels instead of clearing the
  //  previous time and date and then draw the new time and date.

  drawTimeAndDate(time, date);

  while((time.seconds != 0))
  {
    M5.Rtc.getTime(&time);
    delay(200);
  }
  M5.Rtc.getDate(&date);

  drawTimeAndDate(time, date);

  Serial.printf("Shutdown...\n");
  Serial.flush();

  // Full refresh once per hour
  if(time.minutes == FULL_REFRESH_MINUTE - 1)
  {
    // Allow extra time for full ink refresh
    // Shutdown for 55 seconds only
    M5.Power.timerSleep(55);
    return;
  }
  // Shutdown for 58 seconds
  M5.Power.timerSleep(58);
}

void loop(void)
{
}
