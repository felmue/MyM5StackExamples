# MyM5StackExamples
Some examples for M5Stack devices.

### M5Atom
- **[AtomicGPSTest.ino](./M5Atom/AtomicGPSTest/AtomicGPSTest.ino)** : get GPS data from Atomic GPS kit
- **[DTUNBIOTPassthroughTest.ino](./M5Atom/DTUNBIOTPassthroughTest/DTUNBIOTPassthroughTest.ino)** : send and receive AT commands via serial console from ATOM DTU NB IOT
- **[EnvIVTest.ino](./M5Atom/EnvIVTest/EnvIVTest.ino)** : read temperature, humidity and pressure from EnvIV unit
- **[atom_dtu_nb_iot.py](./M5Atom/atom_dtu_nb_iot.py)** : send AT command and wait for response

### M5AtomS3
- **[DeepSleepTest.ino](./M5AtomS3/DeepSleepTest/DeepSleepTest.ino)** : Deep sleep test to measure current
- **[ReadDualButtonViaPbHub.ino](./M5AtomS3/ReadDualButtonViaPbHub/ReadDualButtonViaPbHub.ino)** : Read Dual Button states via PbHub unit

### M5Core2
- **[BatteryMonitor.ino](./M5Core2/BatteryMonitor/BatteryMonitor.ino)** : show battery charging current, level, voltage and whether the battery is being charged or not 
- **[DeepSleepWakeFromTouch.ino](./M5Core2/DeepSleepWakeFromTouch/DeepSleepWakeFromTouch.ino)** : put ESP32 into deep sleep then wake when screen is touched
- **[LightSleepWakeFromTouch.ino](./M5Core2/LightSleepWakeFromTouch/LightSleepWakeFromTouch.ino)** : put ESP32 into light sleep then wake when screen is touched
- **[TouchButtonTest.ino](./M5Core2/TouchButtonTest/TouchButtonTest.ino)** : Touch button using M5Unified and M5GFX
- **[IoTBasePSM.py](./M5Core2/IoTBasePSM.py)** : button A powers modem on; button B sends AT command; button C puts modem into power save mode
- **[SimpleTone.py](./M5Core2/SimpleTone.py)** : play a tone

### M5Core2v1.1
- **[BlueLEDTest.ino](./M5Core2v1.1/BlueLEDTest/BlueLEDTest.ino)** : blink blue LED

### M5CoreInk
- **[CountDownThenPowerOff.py](./M5CoreInk/CountDownThenPowerOff.py)** : count down from 10 then power off
- **[RTC_Clock.ino](./M5CoreInk/RTC_Clock/RTC_Clock.ino)** : low power clock with non-flickering ink display update

### M5CoreS3
- **[COMLTETest.ino](./M5CoreS3/COMLTETest/COMLTETest.ino)** : COM.LTE module - send AT command and read response
- **[CamWebServer](./M5CoreS3/CamWebServer)** : adapted CameraWebServer version for M5CoreS3
- **[I2CScanInternalGroove.ino](./M5CoreS3/I2CScanInternalGroove/I2CScanInternalGroove.ino)** : I2C scan internal and Port A (red)
- **[SDCard.ino](./M5CoreS3/SDCard/SDCard.ino)** : init SD card (Note: breaks LCD)
- **[SDCardAndLCD.ino](./M5CoreS3/SDCardAndLCD/SDCardAndLCD.ino)** : SD card and LCD both work
- **[TouchRandomCircle.ino](./M5CoreS3/TouchRandomCircle/TouchRandomCircle.ino)** : Touch to draw random colored circle
- **[TouchButtonABC.py](./M5CoreS3/TouchButtonABC.py)** : Button A, B and C at the bottom

### M5Dial
- **[GC9A01_demo.ino](./M5Dial/GC9A01_demo/GC9A01_demo.ino)** : TFT demo
- **[I2CScanIntExt.ino](./M5Dial/I2CScanIntExt/I2CScanIntExt.ino)** : Scan I2C - internal and external (red port A)
- **[RS485ModbusACSSR.ino](./M5Dial/RS485ModbusACSSR/RS485ModbusACSSR.ino)** : use RS485 unit on port B with Modbus protocol. Click button to toggle ACSSR relay on / off
- **[ShutdownTest.ino](./M5Dial/ShutdownTest/ShutdownTest.ino)** : Shutdown test - power on via knob button or RTC timer
- **[SleepTest.ino](./M5Dial/SleepTest/SleepTest.ino)** : Light/Deep sleep test - wakeup via touch screen or knob button

### M5LANBase
- **[LinkTest.ino](./M5LANBase/LinkTest/LinkTest.ino)** : LAN Base link test for M5Core, M5Core2, M5Tough and M5CoreS3

### M5Paper
- **[GestureSensor.ino](./M5Paper/GestureSensor/GestureSensor.ino)** : read gesture sensor and display result
- **[I2CScanInternalAndAllPorts.ino](./M5Paper/I2CScanInternalAndAllPorts/I2CScanInternalAndAllPorts.ino)** : i2c scan (internal and port A, B und C).
- **[NonFlickeringUpdateAfterShutdown.ino](./M5Paper/NonFlickeringUpdateAfterShutdown/NonFlickeringUpdateAfterShutdown.ino)** : display non flickering count after waking up from shutdown
- **[ShutdownWakeAfterHours.ino](./M5Paper/ShutdownWakeAfterHours/ShutdownWakeAfterHours.ino)** : Shutdown (after being turned on by power button) and wake up after 7 hours by RTC
- **[SleepTest.ino](./M5Paper/SleepTest/SleepTest.ino)** : ESP32 light / deep sleep test with timer and touch screen wakeup
- **[Lightsleep.py](./M5Paper/Lightsleep.py)** : put ESP32 into light sleep for 60 seconds

### M5PaperS3
- **[RTCClockNonFlickering.ino](./M5PaperS3/RTCClockNonFlickering/RTCClockNonFlickering.ino)** : low power clock with non flickering eInk display
- **[LightSleepTouchWakeup.ino](./M5PaperS3/LightSleepTouchWakeup/LightSleepTouchWakeup.ino)** : light sleep with touch wakeup example

### M5Stack
- **[Cam2CoreExtended.ino](./M5Stack/Cam2CoreExtended/Cam2CoreExtended.ino)** : receive data from TimerCam and display on LCD; use button A, B and C to change frame size
- **[OTAoverLTE.ino](./M5Stack/OTAoverLTE/OTAoverLTE.ino)** : firmware update over the air using an LTE modem

### M5StampC3
- **[NonBlockingBlink.ino](./M5StampC3/NonBlockingBlink/NonBlockingBlink.ino)** : blink LED w/o using delays
- **[Unit4RelayDemo.ino](./M5StampC3/Unit4RelayDemo/Unit4RelayDemo.ino)** : turn relay on / off over i2C every second

### M5Station
- **[LEDTest.ino](./M5Station/LEDTest/LEDTest.ino)** : change LED color every half second
- **[RS485ModbusACSSR.ino](./M5Station/RS485ModbusACSSR/RS485ModbusACSSR.ino)** : use RS485 port with Modbus protocol; button A turns relay on; button B reads the firmware of the relay; button C turns the relay off

### M5StickCPlus2
- **[I2CScanInternalGrooveHat.ino](./M5StickCPlus2/I2CScanInternalGrooveHat/I2CScanInternalGrooveHat.ino)** : I2C scan (internal, Groove, Hat)
- **[SleepAndPowerOffTest.ino](./M5StickCPlus2/SleepAndPowerOffTest/SleepAndPowerOffTest.ino)** : Shows how to put ESP32 into deep sleep and wakeup from button A. It also shows how to power off device and restart from power button.

### M5Tough
- **[LightSleepWakeFromTouch.ino](./M5Tough/LightSleepWakeFromTouch/LightSleepWakeFromTouch.ino)** : put ESP32 into light sleep then wake when screen is touched
- **[RS485ModbusACSSR.ino](./M5Tough/RS485ModbusACSSR/RS485ModbusACSSR.ino)** : use RS485 port with Modbus protocol and toggle ACSSR relay on / off every 800 ms
- **[ThreeBottomButtons.py](./M5Tough/ThreeBottomButtons.py)** : three bottom button for M5Tough
