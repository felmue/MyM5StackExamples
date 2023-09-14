// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5CoreS3
// https://github.com/m5stack/M5GFX

#include <M5CoreS3.h>
#include <M5GFX.h>

M5GFX display;

void setup()
{
  M5.begin();
  display.begin();
}

void loop()
{
  int x, y;

  if(display.getTouch(&x, &y))
  {
    display.drawCircle(x, y, 10, display.color565(random(), random(), random()));
  }
}
