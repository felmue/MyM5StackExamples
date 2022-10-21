// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// https://docs.m5stack.com/en/unit/acssr
// https://github.com/m5stack/ArduinoModbus
// https://github.com/m5stack/ArduinoRS485

#include "M5Station.h"
#include "M5_ACSSR.h"
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>

RS485Class RS485(Serial2, GPIO_NUM_3, GPIO_NUM_1, -1, GPIO_NUM_2);  // RX, TX, ?, ReadEnable

void setup()
{
  M5.begin(true, false, false);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("  ON - FW ver - OFF");

  ModbusRTUClient.begin(115200, SERIAL_8N1);
}

void loop()
{
  M5.update();
  
  if(M5.BtnA.wasPressed() == true)
  {
    // ACSSR CTL ON
    ModbusRTUClient.coilWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_RELAY_COIL_ADDR, 0x01);
    // ACSSR LED CTL RED COLOR
    ModbusRTUClient.holdingRegisterWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_LED_HOLDING_ADDR, 0xF800);
  }
  else if(M5.BtnB.wasPressed() == true)
  {
    M5.Lcd.setCursor(0, 80);
    M5.Lcd.println("            ");
    delay(500);
    // GET ACSSR FW VERSION
    if(ModbusRTUClient.requestFrom(ACSSR_DEFAULT_SLAVE_ID, HOLDING_REGISTERS, ACSSR_VERSION_HOLDING_ADDR, 1))
    {
      while(ModbusRTUClient.available())
      {
        M5.Lcd.setCursor(0, 80);
        M5.Lcd.printf("        0x%02x", ModbusRTUClient.read());
      }
    }
  }
  else if(M5.BtnC.wasPressed() == true)
  {
    // ACSSR CTL OFF
    ModbusRTUClient.coilWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_RELAY_COIL_ADDR, 0x00);
    // ACSSR LED CTL GREEN COLOR
    ModbusRTUClient.holdingRegisterWrite(ACSSR_DEFAULT_SLAVE_ID, ACSSR_LED_HOLDING_ADDR, 0x07E0);
  }
}
