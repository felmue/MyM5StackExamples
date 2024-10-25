// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5Dial
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified
// https://github.com/arduino-libraries/ArduinoModbus
// https://github.com/arduino-libraries/ArduinoRS485

#include "M5Dial.h"
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>

#define ACSSR_DEFAULT_SLAVE_ID     0x04
#define ACSSR_RELAY_COIL_ADDR      0x0000
#define ACSSR_LED_HOLDING_ADDR     0x0000
#define ACSSR_VERSION_HOLDING_ADDR 0x0001
#define ACSSR_ID_HOLDING_ADDR      0x0002

RS485Class RS485(Serial2, GPIO_NUM_1, GPIO_NUM_2, -1, -1);  // RX, TX, ?, ReadEnable

bool bToggle = false;

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);

  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(60, 40);
  M5.Lcd.println("M5Dial");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 70);
  M5.Lcd.println("Modbus Test v1.0.0");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20, 100);
  M5.Lcd.println("Click to toggle\n    relay state.");

  ModbusRTUClient.begin(RS485, 115200, SERIAL_8N1);
}

void loop()
{
  M5.update();

  if(M5.BtnA.wasPressed() == true)
  {
    if(bToggle == false)
    {
      bToggle = true;

      Serial.println("on");
      // ACSSR CTL ON
      ModbusRTUClient.coilWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_RELAY_COIL_ADDR, 0x01);
      // ACSSR LED CTL RED COLOR
      ModbusRTUClient.holdingRegisterWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_LED_HOLDING_ADDR, 0xF800);
    }
    else
    {
      bToggle = false;

      Serial.println("off");
      // ACSSR CTL OFF
      ModbusRTUClient.coilWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_RELAY_COIL_ADDR, 0x00);
      // ACSSR LED CTL GREEN COLOR
      ModbusRTUClient.holdingRegisterWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_LED_HOLDING_ADDR, 0x07E0);
    }
  }
}

