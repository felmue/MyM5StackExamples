// Copyright (c) 2024 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based on: https://github.com/m5stack/M5AtomS3/blob/main/examples/AtomicBase/AtomicGPS/GPS/GPS.ino
// Adapted to: M5Atom + Atomic GPS Base
//
// https://github.com/mikalhart/TinyGPSPlus

#include <Arduino.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps;

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
        while (Serial2.available()) gps.encode(Serial2.read());
    } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec) {
    if (!valid) {
        while (len-- > 1) Serial.print('*');
        Serial.print(' ');
    } else {
        Serial.print(val, prec);
        int vi   = abs((int)val);
        int flen = prec + (val < 0.0 ? 2 : 1);  // . and -
        flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
        for (int i = flen; i < len; ++i) Serial.print(' ');
    }
    smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len) {
    char sz[32] = "*****************";
    if (valid) sprintf(sz, "%ld", val);
    sz[len] = 0;
    for (int i = strlen(sz); i < len; ++i) sz[i] = ' ';
    if (len > 0) sz[len - 1] = ' ';
    Serial.print(sz);
    smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t) {
    if (!d.isValid()) {
        Serial.print(F("********** "));
    } else {
        char sz[32];
        sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
        Serial.print(sz);
    }

    if (!t.isValid()) {
        Serial.print(F("******** "));
    } else {
        char sz[32];
        sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
        Serial.print(sz);
    }

    printInt(d.age(), d.isValid(), 5);
    smartDelay(0);
}

static void printStr(const char *str, int len) {
    int slen = strlen(str);
    for (int i = 0; i < len; ++i) Serial.print(i < slen ? str[i] : ' ');
    smartDelay(0);
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, GPIO_NUM_22, -1);
}

void loop() {
    printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
    printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
    printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
    printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
    printInt(gps.location.age(), gps.location.isValid(), 5);
    printDateTime(gps.date, gps.time);
    printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
    printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
    printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
    printStr(
        gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ",
        6);

    printInt(gps.charsProcessed(), true, 6);
    printInt(gps.sentencesWithFix(), true, 10);
    printInt(gps.failedChecksum(), true, 9);
    Serial.println();

    smartDelay(1000);

    if (millis() > 5000 && gps.charsProcessed() < 10)
        Serial.println(F("No GPS data received: check wiring"));
}
