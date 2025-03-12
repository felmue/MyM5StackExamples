// Copyright (c) 2025 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified

#include <M5Unified.h>

#define SIM7020_BAUDRATE 115200
#define SIM7020_RX_PIN GPIO_NUM_19
#define SIM7020_TX_PIN GPIO_NUM_22

void setup()
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  M5.begin(cfg);
  Serial2.begin(115200, SERIAL_8N1, SIM7020_RX_PIN, SIM7020_TX_PIN);
  delay(2000);
  Serial.printf("Start SIM7020 passthrough test\n");
}

void loop()
{
  while(Serial.available())
  {
    char c = Serial.read();
    Serial2.write(c);
  }
  while(Serial2.available())
  {
    char c = Serial2.read();
    Serial.write(c);
  }
}
