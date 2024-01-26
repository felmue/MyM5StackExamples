// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5CoreS3
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified

// Note: set DIP switch 16 and 17 to ON position in COM.LTE(4G) module
#define RX_PIN      18
#define TX_PIN      17

#include "M5CoreS3.h"

String myCmd = "";
String myRes = "";
int myCount = 0;

void setup()
{
  auto cfg = M5.config();
  CoreS3.begin(cfg);
  CoreS3.Display.setTextSize(2);
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop()
{
  myCmd = "AT\r";
  Serial2.print(myCmd);
  delay(100);
  myRes = "";
  while(Serial2.available() > 0)
  {
    myRes += Serial2.readStringUntil('\n') + " ";
    delay(10);
  }
  CoreS3.Display.clear();  
  CoreS3.Display.setCursor(0, 0);
  CoreS3.Display.printf("#  : %d\n", myCount++);
  CoreS3.Display.printf("cmd: %s\n", myCmd.c_str());
  CoreS3.Display.printf("res: %s\n", myRes.c_str());
  delay(1000);
}
