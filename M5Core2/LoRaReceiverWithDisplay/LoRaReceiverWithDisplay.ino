// Copyright (c) 2025 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// https://github.com/m5stack/M5Unified
// https://github.com/m5stack/M5GFX
// https://github.com/m5stack/M5-SX127x

// Note: Stock LoRaReceiver example adapted to M5Core2 with output to display

/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include <M5Unified.h>
#include <SPI.h>
#include "M5_SX127X.h"

// Module Connect Pins Config
#define CS_PIN  33 //5
#define RST_PIN 26 //13
#define IRQ_PIN 36 //34

#define LORA_MISO 38 //19
#define LORA_MOSI 23 //23
#define LORA_SCLK 18 //18

// LoRa Parameters Config
// #define LORA_FREQ     433E6
#define LORA_FREQ     868E6
#define LORA_SF       12
#define LORA_BW       125E3
#define LORA_TX_POWER 17

void setup() {
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    M5.begin(cfg);
    delay(3000);
    M5.Display.setTextSize(3);
    M5.Display.println("Starting...");

    Serial.println("LoRa Receiver");
    SPI.begin(LORA_SCLK, LORA_MISO, LORA_MOSI, -1);  // SCK, MISO, MOSI, SS
    LoRa.setSPI(&SPI);
    LoRa.setPins(CS_PIN, RST_PIN, IRQ_PIN);  // set CS, reset, IRQ pin
    while (!LoRa.begin(LORA_FREQ)) {
        Serial.println("LoRa init fail.");
        delay(1000);
    }
    Serial.println("Lora ok");
    LoRa.setTxPower(LORA_TX_POWER);
    LoRa.setSignalBandwidth(LORA_BW);
    LoRa.setSpreadingFactor(LORA_SF);
}

void loop() {
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String s = "";
        // received a packet
        Serial.print("Received packet '");
        // read packet
        while (LoRa.available()) {
            s += String((char)LoRa.read());
        }
        Serial.print(s.c_str());
        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
        M5.Display.println(s.c_str());
    }
}
