# A Safety Vest with integrated environmental sensors

![1](https://github.com/maroprjs/SafetyVest/blob/main/extras/img/SafetyVest1.png)

## Simple UDP/IP messaging based on Wio-LTE modem

![1](https://github.com/maroprjs/SafetyVest/blob/main/extras/img/Network1.png)

## Minimum Shopping List

| Image                                                                                                                                                                           | Product Name                                                                                   |
|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |:---------------------------------------------------------------------------------------------- |
| <img title="" src="https://github.com/maroprjs/SafetyVest/blob/main/extras/img/WioLte1.png" alt="" width="100">                                                                 | [Wio LTE](http://wiki.seeedstudio.com/Wio_LTE_Cat.1/)                                          |
| <img title="" src="https://github.com/maroprjs/SafetyVest/blob/main/extras/imghttps://github.com/maroprjs/SafetyVest/raw/master/extras/img/Airquality1.png" alt="" width="100"> | [Airquality Sensor](http://wiki.seeedstudio.com/Grove-Air_Quality_Sensor_v1.3/)                |
| <img title="" src="https://github.com/maroprjs/SafetyVest/blob/main/extras/img/BME2802.png" alt="" width="100">                                                                 | [Humidity Sensor](https://www.adafruit.com/product/2652)                                       |
| <img title="" src="https://github.com/maroprjs/SafetyVest/blob/main/extras/img/DRV88331.png" alt="" width="100">                                                                | Motor Driver, e.g. DRV8833                                                                     |
| <img src="https://github.com/maroprjs/SafetyVest/raw/master/extras/img/Gyro1.png" width="100">                                                                                  | [Accelerometer/Gyroscope](http://wiki.seeedstudio.com/Grove-6-Axis_AccelerometerAndGyroscope/) |
| <img src="https://github.com/maroprjs/SafetyVest/raw/master/extras/img/LED1.png" width="100">                                                                                   | 5V LED stripe                                                                                  |
| <img title="" src="https://github.com/maroprjs/SafetyVest/blob/main/extras/img/Noise1.png" alt="" width="100">                                                                  | [Electret Microphone Amplifier - MAX9814](https://www.adafruit.com/product/1713)               |
| <img title="" src="https://github.com/maroprjs/SafetyVest/blob/main/extras/img/Panic1.png" alt="" width="100">                                                                  | Panic Alarm                                                                                    |
| <img title="" src="https://github.com/maroprjs/SafetyVest/blob/main/extras/img/StepUp5V1.png" alt="" width="100">                                                               | [Step Up Converter](https://www.pololu.com/product/2121)                                       |
| resistors                                                                                                                                                                       | resistors (10k & 470)                                                                          |
| SIM card                                                                                                                                                                        |                                                                                                |

## Schematics

![1](https://github.com/maroprjs/SafetyVest/blob/main/extras/img/Schematic1.png)

## How to build with Arduino IDE

- Set up Wio LTE Environment according [Seeed Wiki](http://wiki.seeedstudio.com/Wio_LTE_Cat.1/)
- Download and install dependencies:
  - [Accelerometer And Gyroscope LSM6DS3 library](https://github.com/maroprjs/Accelerometer_And_Gyroscope_LSM6DS3) (make sure "maro_changes" branch is avtive)
  - [libgeohash](https://github.com/maroprjs/libgeohash) (make sure "maro_changes" branch is active)
  - [WioLTEforArduino](https://github.com/maroprjs/WioLTEforArduino) (make sure "maro_additions" branch is active)
  - [Grove_BME280 library](https://github.com/Seeed-Studio/Grove_BME280)
- Download and install this [SafetyVest](https://github.com/maroprjs/SafetyVest) source code as library
- Modify APN and Server IP/Port settings in Modem.h file according your SIM card subscription
- In WioLTEforArduino -> src -> WioLTEConfig.h file  harmonize with your WioLTE hardware version
- Analog port definitions to be found in NoiseSensor.h and AirQualitySensor.h
- Digital Ports defined in SafetyVest.ino

However, the software was made with [Eclipse Sloeber](https://eclipse.baeyens.it/). 

## Server

- TODO

## Some References and Appreciation

[Sloeber](https://eclipse.baeyens.it/)

[WioLTEforArduino](https://github.com/SeeedJP/WioLTEforArduino)

[libgeohash](https://github.com/simplegeo/libgeohash)

[Grove_BME280](https://github.com/Seeed-Studio/Grove_BME280)

[Accelerometer_And_Gyroscope_LSM6DS3](https://github.com/Seeed-Studio/Accelerometer_And_Gyroscope_LSM6DS3)

[clipart.email](https://www.clipart.email/make-a-clipart/?image=1286359)

[Adafruit](https://www.adafruit.com/)

[Pololu](https://www.pololu.com/)

[Seeedstudio](https://www.seeedstudio.com/)

[^1]: application/x-www-form-urlencoded
