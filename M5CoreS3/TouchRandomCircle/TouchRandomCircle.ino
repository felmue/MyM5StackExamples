// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5CoreS3

#include <M5CoreS3.h>

int16_t x_last = -1;
int16_t y_last = -1;

void setup()
{
  M5.begin();
}

void loop()
{
  M5.update();

  auto p = M5.Touch.getDetail();

  if((p.x != x_last) && (p.y != y_last))
  {
    x_last = p.x;
    y_last = p.y;
    M5.Lcd.drawCircle(p.x, p.y, 10, M5.Lcd.color565(random(), random(), random()));
  }
}
