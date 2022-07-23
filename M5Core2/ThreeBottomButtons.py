# Copyright (c) 2022 by GWENDESIGN. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

import lvgl as lv

def btnl_event_cb(ev):
    print("Btn Left clicked")

def btnm_event_cb(ev):
    print("Btn Middle clicked")

def btnr_event_cb(ev):
    print("Btn Right clicked")

scr = lv.obj()
scr.clear_flag(lv.obj.FLAG.SCROLLABLE)

style = lv.style_t()
style.init()
style.set_width(106)
style.set_height(50)

btnl = lv.btn(scr)
btnl.add_event_cb(btnl_event_cb,lv.EVENT.CLICKED, None)
btnl.add_style(style, 0)
btnl.align(lv.ALIGN.BOTTOM_LEFT, 0, 34)
label = lv.label(btnl)
label.align(lv.ALIGN.TOP_MID, 0, -8)
label.set_text("Left")

btnm = lv.btn(scr)
btnm.add_event_cb(btnm_event_cb,lv.EVENT.CLICKED, None)
btnm.add_style(style, 0)
btnm.align(lv.ALIGN.BOTTOM_MID, 0, 34)
label = lv.label(btnm)
label.align(lv.ALIGN.TOP_MID, 0, -8)
label.set_text("Middle")

btnr = lv.btn(scr)
btnr.add_event_cb(btnr_event_cb,lv.EVENT.CLICKED, None)
btnr.add_style(style, 0)
btnr.align(lv.ALIGN.BOTTOM_RIGHT, 0, 34)
label = lv.label(btnr)
label.align(lv.ALIGN.TOP_MID, 0, -8)
label.set_text("Right")

lv.scr_load(scr)
