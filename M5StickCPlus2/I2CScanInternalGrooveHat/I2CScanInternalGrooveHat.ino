// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Arduino.h>
#include <Wire.h>

typedef struct {
  TwoWire *wire;
  int sda;
  int scl;
} i2cBus_t;

i2cBus_t i2cBus_Internal    = {&Wire, GPIO_NUM_21, GPIO_NUM_22};
i2cBus_t i2cBus_Groove_Port = {&Wire, GPIO_NUM_32, GPIO_NUM_33}; 
i2cBus_t i2cBus_Hat_Port    = {&Wire, GPIO_NUM_0, GPIO_NUM_26};

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Start I2C scan");
}

void scanI2C(TwoWire *wire, int sda, int scl)
{
  int address;
  int error;

  wire->begin(sda, scl);
  for(address = 1; address < 127; address++)
  {
    wire->beginTransmission(address);
    error = wire->endTransmission();
    if(error == 0) Serial.printf("0x%02x ", address);
    else Serial.print(".");
    delay(10);
  }
  Serial.println();
  wire->end();
}

void loop()
{
  Serial.println("I2C Scan - internal");
  scanI2C(i2cBus_Internal.wire, i2cBus_Internal.sda, i2cBus_Internal.scl);
  Serial.println("I2C Scan - Groove Port");
  scanI2C(i2cBus_Groove_Port.wire, i2cBus_Groove_Port.sda, i2cBus_Groove_Port.scl);
  Serial.println("I2C Scan - Hat Port");
  scanI2C(i2cBus_Hat_Port.wire, i2cBus_Hat_Port.sda, i2cBus_Hat_Port.scl);
  delay(2000);
}
