// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based upon: M5Stack LinkStatus example for M5Module-LAN-13.2
// Adapted to: M5Stack LAN Base
// Works with: M5Core, M5Core2, M5Tough and M5CoreS3
// Libraries:
// - https://github.com/m5stack/M5Unified
// - https://github.com/m5stack/M5GFX
// - https://github.com/m5stack/M5-Ethernet
// - https://github.com/m5stack/M5Module-LAN-13.2

#include <M5Unified.h>
#include <M5GFX.h>
#include <SPI.h>
#include <M5Module_LAN.h>
#include "utility/w5100.h"

uint8_t cs_pin;
uint8_t rst_pin;
uint8_t int_pin;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x89};

M5Module_LAN LAN;

#define LINE1_Y   0
#define LINE2_Y  60
#define LINE3_Y  90
#define LINE4_Y 120
#define LINE5_Y 180

void setup()
{
  M5.begin();
  M5.Display.begin();
  M5.Display.setTextColor(WHITE, BLACK);
  M5.Display.setTextSize(2);

  M5.Display.setCursor(0, LINE1_Y);
  m5::board_t board = M5.getBoard();
  switch(board)
  {
    case m5::board_t::board_M5Stack:
      M5.Display.println("Core: M5Stack (Grey/Fire)");
      cs_pin  = 26;
      rst_pin = 13;
      int_pin = 34;
    break;
    case m5::board_t::board_M5StackCore2:
    case m5::board_t::board_M5Tough:
      M5.Display.println("Core: M5Core2 or M5Tough");
      cs_pin  = 26;
      rst_pin = 19;
      int_pin = 34;
    break;
    case m5::board_t::board_M5StackCoreS3:
      M5.Display.println("Core: M5CoreS3");
      cs_pin  = 9;
      rst_pin = 7;
      int_pin = 14;
    break;
    default:
      M5.Display.println("Unsupported core.");

      while(true) delay(1);
    break;
  }

  SPI.begin(SCK, MISO, MOSI, -1);
  LAN.setResetPin(rst_pin);
  LAN.reset();
  LAN.init(cs_pin);
  // W/o below line the check for Ethernet hardware present always fails
  W5100.init();
  // Check for Ethernet hardware present
  if(Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    M5.Display.setCursor(0, LINE2_Y);
    M5.Display.println("Ethernet HW not found.");
    // Do nothing; no point running w/o Ethernet hardware
    while(true) delay(1);
  }
  M5.Display.setCursor(0, LINE2_Y);
  M5.Display.println("Ethernet HW found.    ");
  // Wait for Ethernet cable to be attached
  while(Ethernet.linkStatus() == LinkOFF)
  {
    M5.Display.setCursor(0, LINE3_Y);
    M5.Display.println("Cable not connected.");
    delay(1000);
  }
  M5.Display.setCursor(0, LINE3_Y);
  M5.Display.println("Cable connected.    ");
  // Initiate DHCP
  while(LAN.begin(mac) != 1)
  {
    M5.Display.setCursor(0, LINE4_Y);
    M5.Display.println("DHCP failed. Trying again.");
    delay(2000);
  }

  IPAddress IP = LAN.localIP();
  M5.Display.setCursor(0, LINE4_Y);
  M5.Display.print("Got IP: ");
  M5.Display.print(IP.toString());
  M5.Display.print("    ");
}

void loop()
{
  delay(500);
  auto link = LAN.linkStatus();
  M5.Display.setCursor(0, LINE5_Y);
  M5.Display.print("Link status: ");
  switch(link)
  {
    case Unknown:
      M5.Display.println("Wait");
    break;
    case LinkON:
    {
      M5.Display.println("ON  ");
    }
    break;
    case LinkOFF:
      M5.Display.println("OFF ");
    break;
  }
}
