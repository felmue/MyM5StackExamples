# Copyright (c) 2022 by GWENDESIGN. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

from m5stack import *
from m5stack_ui import *
from uiflow import *
from easyIO import *
from m5mqtt import M5mqtt
import time

screen = M5Screen()
screen.clean_screen()
screen.set_screen_bg_color(0xFFFFFF)

cmd = None
response = None
timeout = None
waitFor = None
logentry = None
btnAPressed = None
btnBPressed = None
btnCPressed = None
list1 = None
list2 = None
list3 = None
list4 = None
list5 = None
list6 = None
list7 = None

action = M5Label('action', x=10, y=20, color=0x000, font=FONT_MONT_14, parent=None)
l_list1 = M5Label('l_list1', x=9, y=50, color=0x000, font=FONT_MONT_14, parent=None)
l_list2 = M5Label('l_list2', x=10, y=70, color=0x000, font=FONT_MONT_14, parent=None)
l_list3 = M5Label('l_list3', x=10, y=90, color=0x000, font=FONT_MONT_14, parent=None)
l_list4 = M5Label('l_list4', x=10, y=110, color=0x000, font=FONT_MONT_14, parent=None)
l_list5 = M5Label('l_list5', x=10, y=130, color=0x000, font=FONT_MONT_14, parent=None)
l_list6 = M5Label('l_list6', x=10, y=150, color=0x000, font=FONT_MONT_14, parent=None)
l_list7 = M5Label('l_list7', x=10, y=170, color=0x000, font=FONT_MONT_14, parent=None)
l_timeout = M5Label('l_timeout', x=10, y=210, color=0x000, font=FONT_MONT_14, parent=None)

from numbers import Number

# Describe this function...
def powerOn():
  global cmd, timeout, waitFor, logentry, btnAPressed, btnBPressed, btnCPressed, list1, list2, response, list3, list4, list5, list6, list7, uart1
  digitalWrite(27, 0)
  wait_ms(100)
  digitalWrite(27, 1)
  wait_ms(100)
  digitalWrite(27, 0)
  wait_ms(100)
  while (uart1.any()) == 0:
    sendAT('AT')
  readResponse(1000, 'OK')
  sendAT('AT+CPSMS=0')
  readResponse(1000, 'OK')
  readResponse(10000, '+CPSMSTATUS: "EXIT PSM"')

# Describe this function...
def sendAT(cmd):
  global timeout, waitFor, logentry, btnAPressed, btnBPressed, btnCPressed, list1, list2, response, list3, list4, list5, list6, list7, uart1
  printLog((str('> ') + str(cmd)))
  uart1.write(str(cmd)+"\r\n")
  wait_ms(250)

# Describe this function...
def readResponse(timeout, waitFor):
  global cmd, logentry, btnAPressed, btnBPressed, btnCPressed, list1, list2, response, list3, list4, list5, list6, list7, uart1
  while timeout:
    if uart1.any():
      response = (uart1.readline()).decode()
      response = response.strip()
      if response != '':
        printLog((str('< ') + str(response)))
        if response == waitFor:
          break
    wait_ms(100)
    timeout = (timeout if isinstance(timeout, Number) else 0) + -100
    l_timeout.set_text(str(timeout))
  if timeout == 0:
    l_timeout.set_text('timeout')
  else:
    l_timeout.set_text('found')

# Describe this function...
def gotoPSM():
  global cmd, timeout, waitFor, logentry, btnAPressed, btnBPressed, btnCPressed, list1, list2, response, list3, list4, list5, list6, list7, uart1
  sendAT('AT+CPSMSTATUS=1')
  readResponse(1000, 'OK')
  sendAT('AT+CPSMS=1,,,"01011111","00000001"')
  readResponse(1000, 'OK')
  readResponse(30000, '+CPSMSTATUS: "ENTER PSM"')

# Describe this function...
def printLog(logentry):
  global cmd, timeout, waitFor, btnAPressed, btnBPressed, btnCPressed, list1, list2, response, list3, list4, list5, list6, list7, uart1
  list1 = list2
  list2 = list3
  list3 = list4
  list4 = list5
  list5 = list6
  list6 = list7
  list7 = logentry
  l_list1.set_text(str(list1))
  l_list2.set_text(str(list2))
  l_list3.set_text(str(list3))
  l_list4.set_text(str(list4))
  l_list5.set_text(str(list5))
  l_list6.set_text(str(list6))
  l_list7.set_text(str(list7))

# Describe this function...
def startMQTT():
  global cmd, timeout, waitFor, logentry, btnAPressed, btnBPressed, btnCPressed, list1, list2, response, list3, list4, list5, list6, list7, uart1
  m5mqtt = M5mqtt('m5stackTest1', 'mqtt.gwen.ch', 8883, 'mytestuser', 'mytestpw', 300, ssl = True)
  m5mqtt.subscribe(str('update'), fun_update_)
  m5mqtt.start()

# Describe this function...
def postMQTT():
  global cmd, timeout, waitFor, logentry, btnAPressed, btnBPressed, btnCPressed, list1, list2, response, list3, list4, list5, list6, list7, uart1
  m5mqtt.publish(str('update'), str('mytest1'), 0)


def fun_update_(topic_data):
  global btnAPressed, btnBPressed, btnCPressed, list1, timeout, list2, cmd, response, list3, list4, list5, list6, list7, logentry, waitFor, uart1
  action.set_text('Hello M5')
  pass

def buttonA_wasPressed():
  global btnAPressed, btnBPressed, btnCPressed, list1, timeout, list2, cmd, response, list3, list4, list5, list6, list7, logentry, waitFor, uart1
  btnAPressed = True
  pass
btnA.wasPressed(buttonA_wasPressed)

def buttonB_wasPressed():
  global btnAPressed, btnBPressed, btnCPressed, list1, timeout, list2, cmd, response, list3, list4, list5, list6, list7, logentry, waitFor, uart1
  btnBPressed = True
  pass
btnB.wasPressed(buttonB_wasPressed)

def buttonC_wasPressed():
  global btnAPressed, btnBPressed, btnCPressed, list1, timeout, list2, cmd, response, list3, list4, list5, list6, list7, logentry, waitFor, uart1
  btnCPressed = True
  pass
btnC.wasPressed(buttonC_wasPressed)

uart1 = machine.UART(1, tx=0, rx=35)
uart1.init(115200, bits=8, parity=None, stop=1)
while uart1.any():
  action.set_text(str(uart1.readline()))
while True:
  if btnAPressed:
    btnAPressed = False
    action.set_text('PowerOn start')
    powerOn()
    action.set_text('PowerOn end')
  if btnBPressed:
    btnBPressed = False
    action.set_text('SendAT start')
    sendAT('AT')
    readResponse(1000, 'OK')
    action.set_text('SendAT end')
  if btnCPressed:
    btnCPressed = False
    action.set_text('GotoPSM start')
    gotoPSM()
    action.set_text('GotoPSM end')
  wait_ms(2)
