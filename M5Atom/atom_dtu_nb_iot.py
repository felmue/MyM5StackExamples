# Copyright (c) 2022 by GWENDESIGN. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

from m5stack import *
from m5ui import *
from uiflow import *
from easyIO import *
from numbers import Number
import time

btnAPressed = None

def sendAT(cmd):
  print((str('> ') + str(cmd)))
  uart1.write(str(cmd)+"\r\n")
  wait_ms(250)

def readResponse(timeout, waitFor):
  rgb.setColorAll(0x000000)
  while timeout:
    if uart1.any():
      response = (uart1.readline()).decode()
      response = response.strip()
      if response != '':
        print((str('< ') + str(response)))
        if response == waitFor:
          break
    wait_ms(100)
    timeout = (timeout if isinstance(timeout, Number) else 0) + -100
    print(str(timeout))
  if timeout == 0:
    print('timeout')
    rgb.setColorAll(0xff0000)
  else:
    print('found')
    rgb.setColorAll(0x00ff00)

def buttonA_wasPressed():
  global btnAPressed
  btnAPressed = True
  pass
btnA.wasPressed(buttonA_wasPressed)


uart1 = machine.UART(1, tx=22, rx=19)
uart1.init(115200, bits=8, parity=None, stop=1)
while True:
  if btnAPressed:
    btnAPressed = False
    sendAT('AT')
    readResponse(10000, 'OK')
  wait_ms(2)
