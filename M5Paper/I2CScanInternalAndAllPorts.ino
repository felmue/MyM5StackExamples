// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5EPD.h>

typedef struct {
  TwoWire *wire;
  int sda;
  int scl;
} i2cBus_t;

i2cBus_t i2cBus_Internal = {&Wire, GPIO_NUM_21, GPIO_NUM_22};
i2cBus_t i2cBus_Port_A   = {&Wire1, M5EPD_PORTA_Y_PIN, M5EPD_PORTA_W_PIN}; // 25, 32
i2cBus_t i2cBus_Port_B   = {&Wire1, M5EPD_PORTB_Y_PIN, M5EPD_PORTB_W_PIN}; // 26, 33
i2cBus_t i2cBus_Port_C   = {&Wire1, M5EPD_PORTC_Y_PIN, M5EPD_PORTC_W_PIN}; // 18, 19

void setup()
{
  M5.begin();
}

void scanI2C(TwoWire *wire, int sda, int scl)
{
  int address;
  int error;

  if(wire == &Wire1) wire->begin(sda, scl);

  for(address = 1; address < 127; address++)
  {
    wire->beginTransmission(address);
    error = wire->endTransmission();
    if(error == 0) Serial.printf("0x%02x ", address);
    else Serial.print(".");
    delay(10);
  }
  Serial.println();

  if(wire == &Wire1) wire->end();
}

void loop()
{
  Serial.println("I2C Scan - internal");
  scanI2C(i2cBus_Internal.wire, i2cBus_Internal.sda, i2cBus_Internal.scl);
  Serial.println("I2C Scan - Port A");
  scanI2C(i2cBus_Port_A.wire, i2cBus_Port_A.sda, i2cBus_Port_A.scl);
  Serial.println("I2C Scan - Port B");
  scanI2C(i2cBus_Port_B.wire, i2cBus_Port_B.sda, i2cBus_Port_B.scl);
  Serial.println("I2C Scan - Port C");
  scanI2C(i2cBus_Port_C.wire, i2cBus_Port_C.sda, i2cBus_Port_C.scl);
  delay(2000);
}
