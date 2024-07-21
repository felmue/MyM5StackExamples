// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5Dial
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified

#include "M5Dial.h"

#define ENC_MIN    0
#define ENC_INIT   16
#define ENC_MAX    64
#define BRIGHT_MIN 0
#define BRIGHT_MAX 255

long oldPos = -999;

void setup()
{
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextSize(4);
  M5Dial.Display.setBrightness(map(ENC_INIT, ENC_MIN, ENC_MAX, BRIGHT_MIN, BRIGHT_MAX));
  M5Dial.Encoder.write(ENC_INIT);
}

void loop()
{
  M5Dial.update();

  long newPos = M5Dial.Encoder.read();

  if(newPos != oldPos)
  {
    if(newPos > ENC_MAX)
    {
      M5Dial.Encoder.write(ENC_MAX);
      return;
    }
    if(newPos < ENC_MIN)
    {
      M5Dial.Encoder.write(ENC_MIN);
      return;
    }
    oldPos = newPos;
    M5Dial.Display.setBrightness(map(newPos, ENC_MIN, ENC_MAX, BRIGHT_MIN, BRIGHT_MAX));
    M5Dial.Display.clear();
    M5Dial.Display.drawString(String(newPos), M5Dial.Display.width() / 2, M5Dial.Display.height() / 2);
  }
}
