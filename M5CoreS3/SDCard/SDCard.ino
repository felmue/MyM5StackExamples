// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Note: requires PR https://github.com/m5stack/M5CoreS3/pull/35 to set SD card voltage to 3.3 V.
// Note: breaks TFT as SD card needs MOSI as input whereas TFT uses MOSI as DC which is an output.

#include <M5CoreS3.h>
#include <SD.h>

#define SD_CS         4
#define SPI_MOSI      37 
#define SPI_MISO      35
#define SPI_SCK       36

void setup()
{
  M5.begin();
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  if(!SD.begin(SD_CS, SPI))
  {
    USBSerial.println("SD card error!");
    while(true); 
  }
  USBSerial.println("SD ok!");
}

void loop()
{
}
