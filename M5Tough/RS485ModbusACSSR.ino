// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// https://docs.m5stack.com/en/unit/acssr
// https://github.com/m5stack/ArduinoModbus
// https://github.com/m5stack/ArduinoRS485

#include "M5Tough.h"
#include "M5_ACSSR.h"
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>

RS485Class RS485(Serial2, GPIO_NUM_27, GPIO_NUM_19, -1, -1);  // RX, TX, ?, ReadEnable

bool gbToggle = false;

void setup()
{
  M5.begin(true, false, true, false);

  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 5);
  M5.Lcd.println("M5Tough");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.println("Modbus Test v1.0.0");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 75);
  M5.Lcd.println("Touch to toggle\nrelay state.");

  ModbusRTUClient.begin(RS485, 115200, SERIAL_8N1);
}

void loop()
{
  M5.update();

  if(M5.Touch.ispressed() == true)
  {
    if(gbToggle == false)
    {
      gbToggle = true;
      // ACSSR CTL ON
      ModbusRTUClient.coilWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_RELAY_COIL_ADDR, 0x01);
      // ACSSR LED CTL RED COLOR
      ModbusRTUClient.holdingRegisterWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_LED_HOLDING_ADDR, 0xF800);
    }
    else
    {
      gbToggle = false;
      // ACSSR CTL OFF
      ModbusRTUClient.coilWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_RELAY_COIL_ADDR, 0x00);
      // ACSSR LED CTL GREEN COLOR
      ModbusRTUClient.holdingRegisterWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_LED_HOLDING_ADDR, 0x07E0);
    }
    delay(800);
  }
}
