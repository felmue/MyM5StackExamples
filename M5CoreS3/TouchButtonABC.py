# Copyright (c) 2023 by GWENDESIGN. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

import os, sys, io
import M5
from M5 import *
import time

label0 = None

def cb_BtnA():
  global label0
  label0.setText(str('Button A'))
  time.sleep_ms(250)
  label0.setText(str('               '))

def cb_BtnB():
  global label0
  label0.setText(str('Button B'))
  time.sleep_ms(250)
  label0.setText(str('               '))

def cb_BtnC():
  global label0
  label0.setText(str('Button C'))
  time.sleep_ms(250)
  label0.setText(str('               '))

def setup():
  global label0

  M5.begin()
  Widgets.fillScreen(0x222222)
  label0 = Widgets.Label("label0", 74, 85, 1.0, 0xffffff, 0x222222, Widgets.FONTS.DejaVu40)

  class MyButton:
    def __init__(self, x, y, w, h, c, fc, cb):
      self.x = x
      self.y = y
      self.w = w
      self.h = h
      self.cb = cb
      self.tx = -1
      self.ty = -1
      self.rect = Widgets.Rectangle(x, y, w, h, c, fc)

    def update(self):
      if M5.Touch.getCount() > 0:
        tx = M5.Touch.getX() - 20 # offset???
        ty = M5.Touch.getY()
        if tx != self.tx or ty != self.ty:
          self.tx = tx; self.ty = ty
          if tx >= self.x and tx <= (self.x + self.w) and ty >= self.y and ty <= (self.y + self.h):
            if callable(self.cb):
              self.cb()

  MyButtonList = []

  global MyButtonUpdate
  def MyButtonUpdate():
    for Btn in MyButtonList:
      Btn.update()

  BtnA = MyButton(0, 230, 106, 30, 0xff0000, 0x880000, cb_BtnA)
  MyButtonList.append(BtnA)

  BtnB = MyButton(107, 230, 106, 30, 0x00ff00, 0x008800, cb_BtnB)
  MyButtonList.append(BtnB)

  BtnC = MyButton(214, 230, 106, 30, 0x0000ff, 0x000088, cb_BtnC)
  MyButtonList.append(BtnC)

def loop():
  global label0
  M5.update()
  MyButtonUpdate()

if __name__ == '__main__':
  try:
    setup()
    while True:
      loop()
  except (Exception, KeyboardInterrupt) as e:
    try:
      from utility import print_error_msg
      print_error_msg(e)
    except ImportError:
      print("please update to latest firmware")
