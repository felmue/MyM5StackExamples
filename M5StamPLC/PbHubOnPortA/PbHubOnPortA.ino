// Copyright (c) 2025 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5StamPLC
// https://github.com/m5stack/M5Unified
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unit-PbHub

#include <M5StamPLC.h>
#include "M5UnitPbHub.h"

M5UnitPbHub pbhub;

void setup()
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  M5.begin(cfg);
  M5StamPLC.begin();
  delay(3000);
  Serial.println("Starting...");
  if(!pbhub.begin(&Wire, UNIT_PBHUB_I2C_ADDR, 2, 1, 400000U))
  {
    Serial.println("Couldn't find PbHub");
    while(1) delay(1);
  }
  Serial.println("Found PbHub");
}

void loop()
{
  Serial.println("Port: 0, index: 0, on");
  pbhub.digitalWrite(0, 0, true);
  delay(2000);
  Serial.println("Port: 0, index: 0, off");
  pbhub.digitalWrite(0, 0, false);
  delay(2000);
}
