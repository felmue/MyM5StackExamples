// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// You need: M5AtomS3, ATOMIC ABC, PbHub unit v1.1, Dual Button unit
// Place M5AtomS3 onto ATOMIC ABC, connect PbHub to red port, connect Dual Button unit to channel 2

#include <M5AtomS3.h>
#include <M5UnitPbHub.h>

M5UnitPbHub pbhub;

#define PBHUB_CHANNEL     2 // 0 - 5
#define BUTTON_BLUE_INDEX 0
#define BUTTON_RED_INDEX  1

void setup()
{
  auto cfg = M5.config();
  AtomS3.begin(cfg);

  if(!pbhub.begin(&Wire, UNIT_PBHUB_I2C_ADDR, 38, 39, 400000U))
  {
    Serial.println("Pbhub not found");
    while(1) delay(1);
  }
  Serial.println("Pbhub found");
}

void loop()
{
  if(pbhub.digitalRead(PBHUB_CHANNEL, BUTTON_BLUE_INDEX) == true)
    Serial.println("Blue button released");
  else
    Serial.println("Blue button pressed");

  if(pbhub.digitalRead(PBHUB_CHANNEL, BUTTON_RED_INDEX) == true)
    Serial.println("Red button released");
  else
    Serial.println("Red button pressed");

  delay(1000);
}
