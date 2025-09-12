# Copyright (c) 2025 by GWENDESIGN. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

import os, sys, io
import M5
from M5 import *
import time

label0 = None
label1 = None

MyButtonList = []

def cb_BtnA():
  global label0, label1
  label1.setText(str('Button A'))
  time.sleep_ms(1000)
  label1.setText(str('               '))

def cb_BtnB():
  global label0, label1
  label1.setText(str('Button B'))
  time.sleep_ms(1000)
  label1.setText(str('               '))

def cb_BtnC():
  global label0, label1
  label1.setText(str('Button C'))
  time.sleep_ms(1000)
  label1.setText(str('               '))

def setup():
  global label0, label1

  M5.begin()
  Widgets.fillScreen(0xffffff)
  label0 = Widgets.Label("Button Test", 30, 0, 1.0, 0x000000, 0x000000, Widgets.FONTS.DejaVu72)
  label1 = Widgets.Label("", 80, 100, 1.0, 0x000000, 0x000000, Widgets.FONTS.DejaVu72)

  class MyButton:
    def __init__(self, x, y, w, h, c, fc, ltxt, cb):
      self.x = x
      self.y = y
      self.w = w
      self.h = h
      self.cb = cb
      self.tx = -1
      self.ty = -1
      self.rect = Widgets.Rectangle(x, y, w, h, c, fc)
      self.ltxt = Widgets.Label(ltxt, x + int(w/3), y + int(h/3), 1.0, 0x000000, 0x000000, Widgets.FONTS.DejaVu40)
      MyButtonList.append(self)

    def update(self):
      if M5.Touch.getCount() > 0:
        tx = M5.Touch.getX()
        ty = M5.Touch.getY()
        if tx != self.tx or ty != self.ty:
          self.tx = tx; self.ty = ty
          if tx >= self.x and tx <= (self.x + self.w) and ty >= self.y and ty <= (self.y + self.h):
            if callable(self.cb):
              self.cb()

  global MyButtonUpdate
  def MyButtonUpdate():
    for Btn in MyButtonList:
      Btn.update()

  BtnA = MyButton(10, 860, 150, 90, 0x000000, 0xffffff, "A", cb_BtnA)
  BtnB = MyButton(195, 860, 150, 90, 0x000000, 0xffffff, "B", cb_BtnB)
  BtnC = MyButton(380, 860, 150, 90, 0x000000, 0xffffff, "C", cb_BtnC)

def loop():
  global label0, label1
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
