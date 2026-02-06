// Copyright (c) 2026 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified
// https://github.com/m5stack/M5PM1
//
// Adapted Button.ino from M5Unified to work with M5StickS3
// https://github.com/m5stack/M5Unified/blob/master/examples/Basic/Button/Button.ino

#include <M5Unified.h>

// Adapted for M5StickS3
#include <M5PM1.h>
M5PM1 pm1;

void setup(void)
{
  M5.begin();

// Adapted for M5StickS3
  delay(2000);
  // Init M5PM1
  auto pin_num_sda = M5.getPin(m5::pin_name_t::in_i2c_sda);
  auto pin_num_scl = M5.getPin(m5::pin_name_t::in_i2c_scl);
  M5_LOGI("getPin: SDA:%u SCL:%u", pin_num_sda, pin_num_scl);
  Wire.end();
  Wire.begin(pin_num_sda, pin_num_scl, 100000U);
  m5pm1_err_t err = pm1.begin(&Wire, M5PM1_DEFAULT_ADDR, pin_num_sda, pin_num_scl, M5PM1_I2C_FREQ_100K);
  if(err == M5PM1_OK)
  {
    M5_LOGI("PM1 initialization successful");
  }
  else
  {
    M5_LOGE("PM1 initialization failed, error code: %d\n", err);
  }
  // Disable BtnPWR default reset function
  pm1.setSingleResetDisable(true);


  /// For models with EPD : refresh control
  M5.Display.setEpdMode(epd_mode_t::epd_fastest); // fastest but very-low quality.

  if (M5.Display.width() < M5.Display.height())
  { /// Landscape mode.
    M5.Display.setRotation(M5.Display.getRotation() ^ 1);
  }
}

void loop(void)
{
  M5.delay(1);

  M5.update();

// Adapted for M5StickS3
  // Simulate BtnPWR state with data read from M5PM1
  {
    bool b;
    pm1.btnGetState(&b);
    M5.BtnPWR.setRawState(millis(), b);
  }

//------------------- Button test
/*
/// List of available buttons:
  M5Stack BASIC/GRAY/GO/FIRE:  BtnA,BtnB,BtnC
  M5Stack Core2:               BtnA,BtnB,BtnC,BtnPWR
  M5Stick C/CPlus:             BtnA,BtnB,     BtnPWR
  M5Stick CoreInk:             BtnA,BtnB,BtnC,BtnPWR,BtnEXT
  M5Paper:                     BtnA,BtnB,BtnC
  M5Station:                   BtnA,BtnB,BtnC,BtnPWR
  M5Tough:                                    BtnPWR
  M5Atom M5AtomU:              BtnA
  M5Stamp Pico/C3/C3U:         BtnA
*/

  static constexpr const int colors[] = { TFT_WHITE, TFT_CYAN, TFT_RED, TFT_YELLOW, TFT_BLUE, TFT_GREEN };
  static constexpr const char* const names[] = { "none", "wasHold", "wasClicked", "wasPressed", "wasReleased", "wasDeciedCount" };

  int w = M5.Display.width() / 5;
  int h = M5.Display.height();
  M5.Display.startWrite();

  /// BtnPWR: "wasClicked"/"wasHold"  can be use.
  /// BtnPWR of CoreInk: "isPressed"/"wasPressed"/"isReleased"/"wasReleased"/"wasClicked"/"wasHold"/"isHolding"  can be use.
  int state = M5.BtnPWR.wasHold() ? 1
            : M5.BtnPWR.wasClicked() ? 2
            : M5.BtnPWR.wasPressed() ? 3
            : M5.BtnPWR.wasReleased() ? 4
            : M5.BtnPWR.wasDecideClickCount() ? 5
            : 0;

  if (state)
  {
    M5_LOGI("BtnPWR:%s  count:%d", names[state], M5.BtnPWR.getClickCount());
    M5.Display.fillRect(w*0, 0, w-1, h, colors[state]);
  }

  /// BtnA,BtnB,BtnC,BtnEXT: "isPressed"/"wasPressed"/"isReleased"/"wasReleased"/"wasClicked"/"wasHold"/"isHolding"  can be use.
  state = M5.BtnA.wasHold() ? 1
        : M5.BtnA.wasClicked() ? 2
        : M5.BtnA.wasPressed() ? 3
        : M5.BtnA.wasReleased() ? 4
        : M5.BtnA.wasDecideClickCount() ? 5
        : 0;
  if (state)
  {
    M5_LOGI("BtnA:%s  count:%d", names[state], M5.BtnA.getClickCount());
    M5.Display.fillRect(w*1, 0, w-1, h, colors[state]);
  }

  state = M5.BtnB.wasHold() ? 1
        : M5.BtnB.wasClicked() ? 2
        : M5.BtnB.wasPressed() ? 3
        : M5.BtnB.wasReleased() ? 4
        : M5.BtnB.wasDecideClickCount() ? 5
        : 0;
  if (state)
  {
    M5_LOGI("BtnB:%s  count:%d", names[state], M5.BtnB.getClickCount());
    M5.Display.fillRect(w*2, 0, w-1, h, colors[state]);
  }

  state = M5.BtnC.wasHold() ? 1
        : M5.BtnC.wasClicked() ? 2
        : M5.BtnC.wasPressed() ? 3
        : M5.BtnC.wasReleased() ? 4
        : M5.BtnC.wasDecideClickCount() ? 5
        : 0;
  if (state)
  {
    M5_LOGI("BtnC:%s  count:%d", names[state], M5.BtnC.getClickCount());
    M5.Display.fillRect(w*3, 0, w-1, h, colors[state]);
  }

  state = M5.BtnEXT.wasHold() ? 1
        : M5.BtnEXT.wasClicked() ? 2
        : M5.BtnEXT.wasPressed() ? 3
        : M5.BtnEXT.wasReleased() ? 4
        : M5.BtnEXT.wasDecideClickCount() ? 5
        : 0;
  if (state)
  {
    M5_LOGI("BtnEXT:%s  count:%d", names[state], M5.BtnEXT.getClickCount());
    M5.Display.fillRect(w*4, 0, w-1, h, colors[state]);
  }
  M5.Display.endWrite();
}

