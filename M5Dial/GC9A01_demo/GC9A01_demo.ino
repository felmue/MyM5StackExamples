// Copyright (c) 2023 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Adapted for M5Dial from
// https://github.com/carlfriess/GC9A01_demo

#include <Arduino.h>
#include <SPI.h>
#include "GC9A01.h"

#define MY_MOSI GPIO_NUM_5
#define MY_SCLK GPIO_NUM_6
#define MY_CS   GPIO_NUM_7
#define MY_DC   GPIO_NUM_4
#define MY_RST  GPIO_NUM_8
#define MY_BL   GPIO_NUM_9

void GC9A01_set_reset(uint8_t val)
{
  digitalWrite(MY_RST, val);
}

void GC9A01_set_data_command(uint8_t val)
{
  digitalWrite(MY_DC, val);
}

void GC9A01_set_chip_select(uint8_t val)
{
  digitalWrite(MY_CS, val);
}

void GC9A01_spi_tx(uint8_t *data, size_t len)
{
  while (len--)
  {
    SPI.transfer(*data);
    data++;
  }
}

void GC9A01_delay(uint16_t ms)
{
  delay(ms);
}

void setup()
{
  pinMode(MY_RST, OUTPUT);
  pinMode(MY_DC, OUTPUT);
  pinMode(MY_CS, OUTPUT);
  pinMode(MY_BL, OUTPUT);
  digitalWrite(MY_BL, HIGH);
  SPI.begin(MY_SCLK, -1, MY_MOSI, -1);
  GC9A01_init();
  struct GC9A01_frame frame = {{0, 0},{239, 239}};
  GC9A01_set_frame(frame);
}

void loop()
{
  uint8_t color[3];

  // Triangle
  color[0] = 0xFF;
  color[1] = 0xFF;
  for(int x = 0; x < 240; x++)
  {
    for(int y = 0; y < 240; y++)
    {
      if(x < y) color[2] = 0xFF;
      else color[2] = 0x00;

      if(x == 0 && y == 0) GC9A01_write(color, sizeof(color));
      else GC9A01_write_continue(color, sizeof(color));
    }
  }
  delay(1000);

  // Rainbow
  float frequency = 0.026;
  for(int x = 0; x < 240; x++)
  {
    color[0] = sin(frequency*x + 0) * 127 + 128;
    color[1] = sin(frequency*x + 2) * 127 + 128;
    color[2] = sin(frequency*x + 4) * 127 + 128;
    for(int y = 0; y < 240; y++)
    {
      if(x == 0 && y == 0) GC9A01_write(color, sizeof(color));
      else GC9A01_write_continue(color, sizeof(color));
    }
  }
  delay(1000);

  // Checkerboard
  for(int x = 0; x < 240; x++)
  {
    for(int y = 0; y < 240; y++)
    {
      if((x / 10) % 2 ==  (y / 10) % 2)
      {
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
      }
      else
      {
        color[0] = 0x00;
        color[1] = 0x00;
        color[2] = 0x00;
      }
      if(x == 0 && y == 0) GC9A01_write(color, sizeof(color));
      else GC9A01_write_continue(color, sizeof(color));
    }
  }
  delay(1000);

  // Swiss flag
  color[0] = 0xFF;
  for(int x = 0; x < 240; x++)
  {
    for(int y = 0; y < 240; y++)
    {
      if((x >= 1*48 && x < 4*48 && y >= 2*48 && y < 3*48) ||
         (x >= 2*48 && x < 3*48 && y >= 1*48 && y < 4*48))
      {
        color[1] = 0xFF;
        color[2] = 0xFF;
      }
      else
      {
        color[1] = 0x00;
        color[2] = 0x00;
      }
      if(x == 0 && y == 0) GC9A01_write(color, sizeof(color));
      else GC9A01_write_continue(color, sizeof(color));
    }
  }
  delay(1000);
}
