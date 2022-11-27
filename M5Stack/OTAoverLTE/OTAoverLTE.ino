// Copyright (c) 2022 by GWENDESIGN. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Based on TinyGSM - FileDownload example
// https://github.com/vshymanskyy/TinyGSM/blob/master/examples/FileDownload/FileDownload.ino

#define TINY_GSM_MODEM_SIM7080

#define DO_NOT_USE_SSL

#define PIN_MODEM_RX    GPIO_NUM_35
#define PIN_MODEM_TX    GPIO_NUM_0
#define PIN_MODEM_PWR   GPIO_NUM_12
#define GSM_PIN         "1234"

const char apn[]      = "your_apn";
const char gprsUser[] = "";
const char gprsPass[] = "";

const char server[]   = "your_ota_server";
#ifdef DO_NOT_USE_SSL
const int  port       = 80;
const char resource[] = "/firmware.bin";
#else
const int  port       = 443;
const char resource[] = "/firmware.bin";
#endif

#define SerialMon Serial
#define SerialAT Serial1

// Increase RX buffer to capture the entire response
// Chips without internal buffering (A6/A7, ESP8266, M590)
// need enough space in the buffer for the entire response
// else data will be lost (and the http library will fail).
#if !defined(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 1024
#endif

#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>
#include <Update.h>

TinyGsm modem(SerialAT);
#ifdef DO_NOT_USE_SSL
TinyGsmClient client(modem);
#else
TinyGsmClientSecure client(modem);
#endif
bool bReboot = false;

void setup()
{
  SerialMon.begin(115200);
  delay(10);

  pinMode(PIN_MODEM_PWR, OUTPUT);
  digitalWrite(PIN_MODEM_PWR, LOW);
  delay(500);
  digitalWrite(PIN_MODEM_PWR, HIGH);
  delay(500);
  digitalWrite(PIN_MODEM_PWR, LOW);

  SerialMon.println("Wait...");

  SerialAT.begin(115200, SERIAL_8N1, PIN_MODEM_RX, PIN_MODEM_TX);
  delay(6000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();
//  modem.init();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  if(GSM_PIN && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }
}

void printPercent(uint32_t readLength, uint32_t contentLength)
{
  if(contentLength != (uint32_t)-1)
  {
    SerialMon.print("\r ");
    SerialMon.print((100.0 * readLength) / contentLength);
    SerialMon.print('%');
  }
  else
  {
    SerialMon.println(readLength);
  }
}

void loop()
{
  SerialMon.print(F("Waiting for network..."));
  if(!modem.waitForNetwork())
  {
    SerialMon.println(F(" fail"));
    delay(10000);
    return;
  }
  SerialMon.println(F(" success"));

  if(modem.isNetworkConnected()) { SerialMon.println(F("Network connected")); }

  // GPRS connection parameters are usually set after network registration
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  if(!modem.gprsConnect(apn, gprsUser, gprsPass))
  {
    SerialMon.println(F(" fail"));
    delay(10000);
    return;
  }
  SerialMon.println(F(" success"));

  if(modem.isGprsConnected()) { SerialMon.println(F("GPRS connected")); }

  SerialMon.print(F("Connecting to "));
  SerialMon.print(server);
  if(!client.connect(server, port)) {
    SerialMon.println(F(" fail"));
    delay(10000);
    return;
  }
  SerialMon.println(F(" success"));

  client.print(String("GET ") + resource + " HTTP/1.0\r\n");
  client.print(String("Host: ") + server + "\r\n");
  client.print("Connection: close\r\n\r\n");

  uint32_t timeElapsed = millis();

  SerialMon.println(F("Waiting for response header"));

  // While we are still looking for the end of the header (i.e. empty line
  // FOLLOWED by a newline), continue to read data into the buffer, parsing each
  // line (data FOLLOWED by a newline). If it takes too long to get data from
  // the client, we need to exit.

  const uint32_t clientReadTimeout   = 5000;
  uint32_t       clientReadStartTime = millis();
  String         headerBuffer;
  bool           finishedHeader = false;
  uint32_t       contentLength  = 0;

  while(!finishedHeader)
  {
    int nlPos;

    if(client.available())
    {
      clientReadStartTime = millis();
      while(client.available())
      {
        char c = client.read();
        headerBuffer += c;

        // Uncomment the lines below to see the data coming into the buffer
        // if (c < 16)
        //   SerialMon.print('0');
        // SerialMon.print(c, HEX);
        // SerialMon.print(' ');
        // if (isprint(c))
        //   SerialMon.print(reinterpret_cast<char> c);
        // else
        //   SerialMon.print('*');
        // SerialMon.print(' ');

        // Let's exit and process if we find a new line
        if(headerBuffer.indexOf(F("\r\n")) >= 0) break;
      }
    }
    else
    {
      if(millis() - clientReadStartTime > clientReadTimeout)
      {
        SerialMon.println(F(">>> Client Timeout !"));
        break;
      }
    }

    nlPos = headerBuffer.indexOf(F("\r\n"));

    if(nlPos > 0)
    {
      headerBuffer.toLowerCase();
      if(headerBuffer.startsWith(F("content-length:")))
      {
        contentLength = headerBuffer.substring(headerBuffer.indexOf(':') + 1).toInt();
      }
      headerBuffer.remove(0, nlPos + 2);
    }
    else if(nlPos == 0)
    {
      finishedHeader = true;
    }
  }

  Serial.printf("Content-length: %d\n", contentLength);
  if(Update.begin(contentLength))
  {
    Serial.println(F("Update begin ok"));
  }
  else
  {
    Serial.println(F("Update begin not ok"));

    while (true) { delay(1000); }
  }

  // The two cases which are not managed properly are as follows:
  // 1. The client doesn't provide data quickly enough to keep up with this
  // loop.
  // 2. If the client data is segmented in the middle of the 'Content-Length: '
  // header,
  //    then that header may be missed/damaged.
  //

  uint32_t readLength = 0;

  if(finishedHeader)
  {
    SerialMon.println(F("Reading response data"));
    clientReadStartTime = millis();

    printPercent(readLength, contentLength);
    while(readLength < contentLength && client.connected() &&
           millis() - clientReadStartTime < clientReadTimeout)
    {
      while(client.available())
      {
        uint8_t c = client.read();
        Update.write(&c, 1);
        readLength++;
        if(readLength % (contentLength / 13) == 0)
        {
          printPercent(readLength, contentLength);
        }
        clientReadStartTime = millis();
      }
    }
    printPercent(readLength, contentLength);
  }

  timeElapsed = millis() - timeElapsed;
  SerialMon.println();

  if(Update.end())
  {
    Serial.println(F("OTA done!"));
    if(Update.isFinished())
    {
      Serial.println(F("Update successfully completed. Rebooting."));
      bReboot = true;
    }
    else
    {
      Serial.println(F("Update not finished? Something went wrong!"));
    }
  }
  else
  {
    Serial.println("Error Occurred. Error #: " + String(Update.getError()));
  }

  client.stop();
  SerialMon.println(F("Server disconnected"));

  modem.gprsDisconnect();
  SerialMon.println(F("GPRS disconnected"));

  float duration = float(timeElapsed) / 1000;

  SerialMon.println();
  SerialMon.print("Content-Length: ");
  SerialMon.println(contentLength);
  SerialMon.print("Actually read:  ");
  SerialMon.println(readLength);
  SerialMon.print("Duration:       ");
  SerialMon.print(duration);
  SerialMon.println("s");

  if(bReboot == true) ESP.restart();

  // Do nothing forevermore
  while (true) { delay(1000); }
}
