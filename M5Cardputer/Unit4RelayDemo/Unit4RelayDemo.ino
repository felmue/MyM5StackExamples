// Copyright (c) 2025 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified
// https://github.com/m5stack/M5Cardputer
// https://github.com/m5stack/M5Module-4Relay

#include "M5Cardputer.h"
#include "Unit_4RELAY.h"

UNIT_4RELAY relay;

void setup()
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  M5.begin(cfg);

  Serial.print("Unit 4Relay Demo");
  M5.Display.print("Unit 4Relay Demo");

  relay.begin(&Wire, GPIO_NUM_2, GPIO_NUM_1); // Port A
  relay.Init(1); // synchronous mode
}

void loop()
{
  relay.relayWrite(0, 1); // turn on relay 1
  delay(1000);
  relay.relayWrite(0, 0); // turn off relay 1
  delay(1000);
  relay.relayAll(1); // turn on all relay
  delay(1000);
  relay.relayAll(0); // turn off all relay
  delay(1000);
}
