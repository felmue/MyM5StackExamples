// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5EPD.h>
#include "time.h"

M5EPD_Canvas CountPageSprite(&M5.EPD);

char myBuf[11];
uint8_t myCount = 0;

// EEPROM 8bit address: | 1 | 0 | 1 | 0 | A2 | A1 | A0 | R/W |
// Note: A2, A1, A0 all low
#define EEPROM_ADDR (0b10100000 >> 1) // 7bit address

void writeEEPROM(int addr, unsigned int location, byte data)
{
  Wire.beginTransmission(addr);
  Wire.write((int)(location & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

byte readEEPROM(int addr, unsigned int location)
{
  byte rdata = 0xFF;

  Wire.beginTransmission(addr);
  Wire.write((int)(location & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(addr, 1);
  if(Wire.available())
  {
    rdata = Wire.read();
  }
  return rdata;
}

void setup()
{
    // Enable everything except SD and RTC
    M5.begin(true, false, true, true, true);
    // Read wake up reason before RTC begin which clears interrupts
    uint8_t data = M5.RTC.readReg(0x01);
    // Start RTC and clear interrupt
    M5.RTC.begin();

    M5.EPD.SetRotation(0);
    M5.TP.SetRotation(0);

    // Check timer flag
    if((data & 0b00000100) == 0b00000100)
    {
        Serial.println("Power on by: RTC timer");
        M5.EPD.Clear(false);
    }
    else
    {
        Serial.println("Power on by: power button");
        M5.EPD.Clear(true);
        myCount = 0;
        writeEEPROM(EEPROM_ADDR, 0, myCount);
    }

    // After every shutdown the sprite is created anew.
    // But the sprite doesn't know about the current image on the
    //  ink display therefore the same count, as has been
    //  drawn before the shutdown, is redrawn.
    // This is required, else drawing new count only adds
    //  pixels to the already drawn pixels instead of clearing the
    //  previous count and then draw the new count.
    CountPageSprite.createCanvas(960, 540);
    CountPageSprite.fillCanvas(1);

    CountPageSprite.setTextSize(3);
    CountPageSprite.setFreeFont(&FreeSansBold12pt7b);
    CountPageSprite.setTextDatum(TL_DATUM);

    // First draw old count
    myCount = readEEPROM(EEPROM_ADDR, 0);
    snprintf(myBuf, 10,  "%04d ", myCount);
    CountPageSprite.drawString(myBuf, 20, 20);
    CountPageSprite.pushCanvas(0, 0, UPDATE_MODE_DU4);

ON_USB_POWER_LOOP:

    // Then draw new count
    myCount++;
    writeEEPROM(EEPROM_ADDR, 0, myCount);
    snprintf(myBuf, 10, "%04d ", myCount);
    CountPageSprite.drawString(myBuf, 20, 20);
    CountPageSprite.pushCanvas(0, 0, UPDATE_MODE_DU4);
    delay(250); // required, else no update

    Serial.printf("Shutdown...\n");
    Serial.flush();

    M5.shutdown(10);

    // This part is only executed if running from USB power
    delay(1000);
    // Undo what shutdown did
    M5.RTC.clearIRQ();
    M5.enableMainPower();
    // Kill some time
    Serial.println("Should not be reachded when battery powered 1");
    delay(10000);
    Serial.println("Should not be reachded when battery powered 2");

    goto ON_USB_POWER_LOOP;
}

void loop()
{

}
