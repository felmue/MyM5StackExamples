// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5Unified
// https://github.com/m5stack/M5CoreS3
//
// Based on CameraWebServer example by Espressif
// https://github.com/espressif/arduino-esp32/tree/master/libraries/ESP32/examples/Camera/CameraWebServer
//
// Notes:
// - Maximum frame size of M5CoreS3 camera GC0308 is 640x480 (VGA)
// - M5CoreS3 camera GC0308 doesn't support JPEG
// - most setting in the webpage have no effect
// - crashes sometimes at startup

#include <M5CoreS3.h>
#include "esp_camera.h"
#include <WiFi.h>

#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  2
#define SIOD_GPIO_NUM  12
#define SIOC_GPIO_NUM  11

#define Y9_GPIO_NUM    47
#define Y8_GPIO_NUM    48
#define Y7_GPIO_NUM    16
#define Y6_GPIO_NUM    15
#define Y5_GPIO_NUM    42
#define Y4_GPIO_NUM    41
#define Y3_GPIO_NUM    40
#define Y2_GPIO_NUM    39
#define VSYNC_GPIO_NUM 46
#define HREF_GPIO_NUM  38
#define PCLK_GPIO_NUM  45

const char *ssid = "YourSSID";
const char *password = "YourPW";

void startCameraServer();
void setupLedFlash(int pin);

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  delay(2000);

  Serial.setDebugOutput(true);
  Serial.println("hello");
  M5.Lcd.println("hello");

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_QVGA;      // FRAMESIZE_VGA is slow
  config.pixel_format = PIXFORMAT_RGB565;  // GC0308 doesn't support JPEG
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.fb_count = 2;
  config.sccb_i2c_port = M5.In_I2C.getPort();
  M5.In_I2C.release();

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x.", err);
    M5.Lcd.printf("Camera init failed with error 0x%x.", err);
    return;
  }
  Serial.println("Camera init ok.");
  M5.Lcd.println("Camera init ok.");

  sensor_t *s = esp_camera_sensor_get();
  if (s == NULL) {
    Serial.println("No camera sensor found!");
    M5.Lcd.println("No camera sensor found!");
    return;
  }
  Serial.println("Camera sensor found.");
  M5.Lcd.println("Camera sensor found.");

  if (s->id.PID != GC0308_PID) {
    Serial.printf("Wrong camera PID: 0x%x. Should be: 0x%x.\n", s->id.PID, GC0308_PID);
    M5.Lcd.printf("Wrong camera PID: 0x%x. Should be: 0x%x.\n", s->id.PID, GC0308_PID);
  }
  Serial.printf("Camera PID: 0x%x GC0308_PID: 0x%x.\n", s->id.PID, GC0308_PID); // GC0308_PID
  M5.Lcd.printf("Camera PID: 0x%x GC0308_PID: 0x%x.\n", s->id.PID, GC0308_PID); // GC0308_PID

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    M5.Lcd.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  M5.Lcd.println("");
  M5.Lcd.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  M5.Lcd.print("Camera Ready! Use 'http://");
  M5.Lcd.print(WiFi.localIP());
  M5.Lcd.println("' to connect");
}

void loop() {
  // Do nothing. Everything is done in another task by the web server
  delay(10000);
}
