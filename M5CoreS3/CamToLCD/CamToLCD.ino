// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Based on take_picture example by Espressif
// https://github.com/espressif/esp32-camera

#include <M5CoreS3.h>
#include "esp_camera.h"

#define CAM_PIN_PWDN    -1
#define CAM_PIN_RESET   -1
#define CAM_PIN_XCLK    -1
#define CAM_PIN_SIOD    -1
#define CAM_PIN_SIOC    -1
#define CAM_PIN_D7      47
#define CAM_PIN_D6      48
#define CAM_PIN_D5      16
#define CAM_PIN_D4      15
#define CAM_PIN_D3      42
#define CAM_PIN_D2      41
#define CAM_PIN_D1      40
#define CAM_PIN_D0      39
#define CAM_PIN_VSYNC   46
#define CAM_PIN_HREF    38
#define CAM_PIN_PCLK    45

static camera_config_t camera_config = {
  .pin_pwdn  = CAM_PIN_PWDN,
  .pin_reset = CAM_PIN_RESET,
  .pin_xclk = CAM_PIN_XCLK,
  .pin_sccb_sda = CAM_PIN_SIOD,
  .pin_sccb_scl = CAM_PIN_SIOC,
  .pin_d7 = CAM_PIN_D7,
  .pin_d6 = CAM_PIN_D6,
  .pin_d5 = CAM_PIN_D5,
  .pin_d4 = CAM_PIN_D4,
  .pin_d3 = CAM_PIN_D3,
  .pin_d2 = CAM_PIN_D2,
  .pin_d1 = CAM_PIN_D1,
  .pin_d0 = CAM_PIN_D0,
  .pin_vsync = CAM_PIN_VSYNC,
  .pin_href = CAM_PIN_HREF,
  .pin_pclk = CAM_PIN_PCLK,

  .xclk_freq_hz = 20000000,
  .ledc_timer = LEDC_TIMER_0,
  .ledc_channel = LEDC_CHANNEL_0,
  .pixel_format = PIXFORMAT_RGB565,
  .frame_size = FRAMESIZE_QVGA,
  .jpeg_quality = 0,
  .fb_count = 1,
  .fb_location = CAMERA_FB_IN_PSRAM,
  .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
  .sccb_i2c_port = 1, // M5CoreS3 internal I2C is Wire1
};

void setup()
{
  M5.begin();

  esp_err_t err = esp_camera_init(&camera_config);
  if(err != ESP_OK)
  {
    USBSerial.println("Camera Init Failed");
    while(1) delay(100);
  }
  USBSerial.println("Camera Init ok");
}

void loop()
{
  camera_fb_t *fb = esp_camera_fb_get();
  if(!fb)
  {
    USBSerial.println("Camera Capture Failed");
    delay(1000);
    return;
  }
  M5.Lcd.setAddrWindow(0, 0, fb->width, fb->height);
  M5.Lcd.pushColors(fb->buf, fb->len);
  esp_camera_fb_return(fb);
}
