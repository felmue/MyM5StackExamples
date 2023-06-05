// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5EPD.h>
#include <DFRobot_PAJ7620U2.h>

M5EPD_Canvas canvas(&M5.EPD);
DFRobot_PAJ7620U2 paj(&Wire1);

void setup()
{
  M5.begin(true, false, true, true, false);

  Wire1.begin(25, 32, 400000U);
  while(paj.begin() != 0)
  {
    Serial.println("check PAJ7620U2");
    delay(500);
  }
  Serial.println("PAJ7620U2 success");
  paj.setGestureHighRate(true);

  M5.EPD.SetRotation(90);
  M5.EPD.Clear(true);
  M5.RTC.begin();
  canvas.createCanvas(540, 960);
  canvas.setTextSize(3);
  canvas.drawString("Hello World", 10, 10);
  canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void loop()
{
  DFRobot_PAJ7620U2::eGesture_t gesture = paj.getGesture();
  if(gesture != paj.eGestureNone)
  {
    canvas.fillCanvas(0);
    canvas.drawString(paj.gestureDescription(gesture), 10, 10);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
  }
}
