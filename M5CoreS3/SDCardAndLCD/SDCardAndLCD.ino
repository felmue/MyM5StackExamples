// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Note: requires PR https://github.com/m5stack/M5CoreS3/pull/35 to set SD card voltage to 3.3 V.

// Note: The LCD uses the MISO GPIO as DC, so for the
//  LCD     : MISO/DC GPIO needs to be an output
//  SD card : MISO/DC GPIO needs to be an input
// In order to be able to switch back and forth the same SPI
//  instance needs to be used for the LCD and the SD card.
// Luckily the LCD library provides a function to get the
//  SPI instance. E.g. M5.Lcd.getSPIinstance();

#include <M5CoreS3.h>
#include <SD.h>

#define SD_CS 4

// Helpers to switch MISO/DC GPIO to output or input
#define SPI_MODE_LCD { pinMode(TFT_DC, OUTPUT); digitalWrite(TFT_DC, HIGH); }
#define SPI_MODE_SDCARD { pinMode(TFT_DC, INPUT); }

void setup()
{
  M5.begin();

  delay(1000);

  SPI_MODE_SDCARD;
  // Use LCD SPI instance for SD card
  if(!SD.begin(SD_CS, M5.Lcd.getSPIinstance()))
  {
    USBSerial.println("SD card error!");
    while(1);
  }
  USBSerial.println("SD ok!");

  SPI_MODE_LCD;
  USBSerial.println("*** 1");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(100, 120);
  M5.Lcd.print("Hello World");

  SPI_MODE_SDCARD;
  if(SD.exists("/hello.txt"))
  {
    USBSerial.println("hello.txt exists.");
  }
  else
  {
    USBSerial.println("hello.txt doesn't exist.");
  }

  SPI_MODE_LCD;
  USBSerial.println("*** 2");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(100, 140);
  M5.Lcd.print("Hello World 2");

  SPI_MODE_SDCARD;
  if(SD.exists("/hello.txt"))
  {
    USBSerial.println("hello.txt exists.");
  }
  else
  {
    USBSerial.println("hello.txt doesn't exist.");
  }
}

void loop()
{
}
