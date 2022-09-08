from m5stack import *
from m5ui import *
from uiflow import *
import time

setScreenColor(15)

while True:
  power.ext_power_on() # turn Groove port power on
  wait(1)
  power.ext_power_off() # turn Groove port power off

  from machine import Pin, lightsleep

  Pin(2, Pin.OUT, value=1, pull=Pin.PULL_HOLD) # M5EPD_MAIN_PWR_PIN
  lightsleep(1000*60)

  wait_ms(2)
  
