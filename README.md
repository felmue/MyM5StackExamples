# MyM5StackExamples
Some examples for M5Stack devices.

### M5Atom
- **atom_dtu_nb_iot.py** : send AT command and wait for response

### M5AtomS3
- **DeepSleepTest.ino** : Deep sleep test to measure current

### M5Core2
- **DeepSleepWakeFromTouch.ino** : put ESP32 into deep sleep then wake when screen is touched
- **LightSleepWakeFromTouch.ino** : put ESP32 into light sleep then wake when screen is touched
- **IotBasePSM.py** : button A powers modem on; button B sends AT command; button C puts modem into power save mode
- **SimpleTone.py** : play a tone

### M5CoreInk
- **CountDownThePowerOff.py** : count down from 10 then power off

### M5CoreS3
- **COMLTETest.ino** : COM.LTE module - send AT command and read response
- **CamToLCD.ino** : take picture from camera and show on LCD
- **SDCard.ino** : init SD card (Note: breaks LCD)
- **SDCardAndLCD.ino** : SD card and LCD both work
- **TouchRandomCircle.ino** : Touch to draw random colored circle
- **TouchButtonABC.py*** : Button A, B and C at the bottom

### M5Dial
- **GC9A01_demo.ino** : TFT demo

### M5LANBase
- **LinkTest.ino** : LAN Base link test for M5Core, M5Core2, M5Tough and M5CoreS3

### M5Paper
- **GestureSensor.ino** : read gesture sensor and display result
- **I2CScanInternalAndAllPorts.ino** : i2c scan (internal and port A, B und C).
- **NonFlickeringUpdateAfterShutdown.ino** : display non flickering count after waking up from shutdown
- **ShutdownWakeAfterHours.ino** : Shutdown (after being turned on by power button) and wake up after 7 hours by RTC
- **Lightsleep.py** : put ESP32 into light sleep for 60 seconds

### M5Stack
- **Cam2CoreExtended.ino** : receive data from TimerCam and display on LCD; use button A, B and C to change frame size
- **OTAoverLTE.ino** : firmware update over the air using an LTE modem

### M5StampC3
- **NonBlockingBlink.ino** : blink LED w/o using delays
- **Unit4RelayDemo.ino** : turn relay on / off over i2C every second

### M5Station
- **LEDTest.ino** : change LED color every half second
- **RS485ModbusACSSR.ino** : use RS485 port with Modbus protocol; button A turns relay on; button B reads the firmware of the relay; button C turns the relay off

### M5Tough
- **LightSleepWakeFromTouch.ino** : put ESP32 into light sleep then wake when screen is touched
- **RS485ModbusACSSR.ino** : use RS485 port with Modbus protocol and toggle ACSSR relay on / off every 800 ms
- **ThreeBottomButtons.py** : three bottom button for M5Tough
