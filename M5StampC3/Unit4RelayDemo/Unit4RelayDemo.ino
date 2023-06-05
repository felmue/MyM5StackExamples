// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Arduino.h>
#include "Unit_4RELAY.h"

UNIT_4RELAY relay;

void setup()
{
  Serial.begin(115200);
  relay.begin(&Wire, 1, 0); // port A
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
