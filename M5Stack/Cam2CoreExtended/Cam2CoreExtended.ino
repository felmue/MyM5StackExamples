// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Based on CAM2CORE example by M5Stack
// https://github.com/m5stack/M5-ProductExampleCodes/tree/master/Unit/UNIT_CAM/CAM2CORE

#include <M5Stack.h>
#include "uart_frame.h"

// Serial connection between M5Stack and Camera
// - receive picture frames from camera
// - send commands to camera
#define UART_RX_PIN 36 
#define UART_TX_PIN 26

typedef enum {
  kImage = 0x00,
// cam config
  kFrameSize,
  kQuality,
  kContrast,
  kBrightness,
  kSaturation,
  kGainceiling,
  kColorbar,
  kAwb,
  kAgc,
  kAec,
  kHmirror,
  kVflip,
  kAwbGain,
  kAgcGain,
  kAecValue,
  kAec2,
  kDcw,
  kBpc,
  kWpc,
  kRawGma,
  kLenc,
  kSpecialEffect,
  kWbMode,
  kAeLevel,
  kCamCmdEnd,
// usr cmd
  kSetDeviceMode,
  kGetDeviceMode,
  kSaveDeviceConfig,
  kGetCamConfig,
  kSaveCamConfig,
  kSetWiFi,
  kGetWifiSSID,
  kGetWifiIP,
  kGetWifiState,
  kTimingTime,
  kFactoryTest,
  kErrorOccur,
  KRestart,
} CmdList_t;

typedef enum {
  FRAMESIZE_96X96,    // 96x96
  FRAMESIZE_QQVGA,    // 160x120
  FRAMESIZE_QCIF,     // 176x144
  FRAMESIZE_HQVGA,    // 240x176
  FRAMESIZE_240X240,  // 240x240
  FRAMESIZE_QVGA,     // 320x240
  FRAMESIZE_CIF,      // 400x296
  FRAMESIZE_HVGA,     // 480x320
  FRAMESIZE_VGA,      // 640x480
  FRAMESIZE_SVGA,     // 800x600
  FRAMESIZE_XGA,      // 1024x768
  FRAMESIZE_HD,       // 1280x720
  FRAMESIZE_SXGA,     // 1280x1024
  FRAMESIZE_UXGA,     // 1600x1200
  // 3MP Sensors
  FRAMESIZE_FHD,      // 1920x1080
  FRAMESIZE_P_HD,     //  720x1280
  FRAMESIZE_P_3MP,    //  864x1536
  FRAMESIZE_QXGA,     // 2048x1536
  // 5MP Sensors
  FRAMESIZE_QHD,      // 2560x1440
  FRAMESIZE_WQXGA,    // 2560x1600
  FRAMESIZE_P_FHD,    // 1080x1920
  FRAMESIZE_QSXGA,    // 2560x1920
  FRAMESIZE_INVALID
} framesize_t;

typedef struct _JpegFrame_t {
  uint8_t *buf;
  uint32_t size;
} JpegFrame_t;

static QueueHandle_t jpeg_fream_queue = NULL;

void frame_recv_callback(int cmd, const uint8_t*buf, int len)
{
  JpegFrame_t frame;

  frame.buf = (uint8_t *) malloc(sizeof(uint8_t) * len);
  memcpy(frame.buf, buf, len);
  frame.size = len;
  
  if(xQueueSend(jpeg_fream_queue, &frame, 0) != pdTRUE)
  {
    free(frame.buf);
  }
}

void setup()
{
  M5.begin(true, false, true, false);
  uart_frame_init(UART_RX_PIN, UART_TX_PIN, 1500000);
  jpeg_fream_queue = xQueueCreate(2, sizeof(JpegFrame_t));
}

void loop()
{
  JpegFrame_t frame;

  if(xQueueReceive(jpeg_fream_queue, &frame, portMAX_DELAY) == pdTRUE)
  {
    M5.Lcd.drawJpg(frame.buf, frame.size, 0, 0);
    free(frame.buf);
  }

  M5.update();
  if(M5.BtnA.wasPressed() == true)
  {
//    uint8_t b[2] = {1};
//    uart_frame_send(CmdList_t::kHmirror, b, 2, true);
//    uint8_t b[2] = {5};
//    uart_frame_send(CmdList_t::kQuality, b, 2, true);
    uint8_t b[2] = {FRAMESIZE_QQVGA};
    uart_frame_send(kFrameSize, b, 2, true);
  }
  if(M5.BtnB.wasPressed() == true)
  {
//    uint8_t b[2] = {0};
//    uart_frame_send(CmdList_t::kHmirror, b, 2, true);
//    uint8_t b[2] = {30};
//    uart_frame_send(CmdList_t::kQuality, b, 2, true);
    uint8_t b[2] = {FRAMESIZE_HQVGA};
    uart_frame_send(kFrameSize, b, 2, true);
  }
  if(M5.BtnC.wasPressed() == true)
  {
//    uint8_t b[2] = {60};
//    uart_frame_send(CmdList_t::kQuality, b, 2, true);
    uint8_t b[2] = {FRAMESIZE_QVGA};
    uart_frame_send(kFrameSize, b, 2, true);
  }
}
