# Copyright (c) 2022 by GWENDESIGN. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

from m5stack import *
from m5ui import *
from uiflow import *
import time

setScreenColor(lcd.WHITE)
my_time = None
label0 = M5TextBox(41, 64, "Text", lcd.FONT_DejaVu56, lcd.BLACK, rotate=0)
from numbers import Number

setScreenColor(lcd.WHITE)
coreInkShow()
my_time = 10
while my_time > 0:
  my_time = (my_time if isinstance(my_time, Number) else 0) + -1
  label0.setText(str(my_time))
  coreInkParitalShow(0, 64, 200, 56)
  wait(1)
speaker.sing(889, 1)
wait(2)
power.off()
