// Copyright (c) 2025 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5Unified
// https://github.com/m5stack/M5GFX

#include <M5Unified.h>
#include <M5GFX.h>

m5gfx::touch_point_t tp;
LGFX_Button btn1;
LGFX_Button btn2;

void setup()
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  M5.begin(cfg);

  btn1.initButton(&M5.Lcd, 100, 120, 100, 50, TFT_RED, TFT_YELLOW, TFT_BLACK, "Btn 1");
  btn1.drawButton();
  btn2.initButton(&M5.Lcd, 220, 120, 100, 50, TFT_RED, TFT_YELLOW, TFT_BLACK, "Btn 2");
  btn2.drawButton();
}

void loop()
{
  M5.update();

  if(M5.Touch.getCount() > 0)
  {
    tp = M5.Touch.getTouchPointRaw();
  }
  else
  {
    tp.x = -1;
    tp.y = -1;
  }

  if(btn1.contains(tp.x, tp.y))
  {
    btn1.press(true);
  }
  else
  {
    btn1.press(false);
  }
  if(btn1.justPressed())
  {
    Serial.println("Btn1 just pressed");
    btn1.drawButton(true);
  }
  if(btn1.isPressed())
  {
    Serial.println("Btn1 is pressed");
  }
  if(btn1.justReleased())
  {
    Serial.println("Btn1 just released");
    btn1.drawButton(false);
  }

  if(btn2.contains(tp.x, tp.y))
  {
    btn2.press(true);
  }
  else
  {
    btn2.press(false);
  }
  if(btn2.justPressed())
  {
    Serial.println("Btn2 just pressed");
    btn2.drawButton(true);
  }
  if(btn2.isPressed())
  {
    Serial.println("Btn2 is pressed");
  }
  if(btn2.justReleased())
  {
    Serial.println("Btn2 just released");
    btn2.drawButton(false);
  }

  delay(50);
}
