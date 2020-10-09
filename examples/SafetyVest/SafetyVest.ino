/**
 *  SafetyVest.ino
 *
 *  A safety vest equipped with various environmental sensors for the sake of a workers security,
 *  based on Wio Tracker (Wio LTE Cat.1) from Seeed (https://www.seeedstudio.com/about_seeed).
 *  - http://wiki.seeedstudio.com/Wio_LTE_Cat.1/
 *
 *  This is the code running on Wio_LTE_Cat.1.
 *
 *  This file handles instantiation and control of objects (sensors, LEDs, etc) integrated
 *  in safety vest as well as the modem itself.
 *
 *  The provided measurement- and alert- data are periodically sent to a public server in json
 *  format using UDP/IP protocol.
 *
 *  !!!!!!!!!
 *  !!! -The configuration for APN and server settings to be found in Modem.h file.
 *  !!! -Note also that WioLTEConfig.h definitions(under WioLTEforArduino library) must be adapted to
 *  !!!  appropriate hardware version.
 *  !!! -Digital ports 19 and 20 are in use, as well as A4 and A5
 *  !!!!!!!!
 *
 *
 */

/////////// Includes /////////////////
#include "Debug.h"
#include "TypeDefs.h"
#include <stdio.h>

#include <WioLTEforArduino.h> //lib https://github.com/maroprjs/WioLTEforArduino/tree/maro_additions
                              //forked from https://github.com/SeeedJP/WioLTEforArduino
#include <SD.h> //part of Seeed_STM32F4 core, alternative https://github.com/Seeed-Studio/SD
#include "Modem.h"
#include "Modem.h"
#include "LEDStripe.h"
#include "PanikButton.h"
#include "NoiseSensor.h"
#include "AirQualitySensor.h"
#include "Seeed_BME280.h" // lib https://github.com/Seeed-Studio/Grove_BME280
#include "HumiditySensor.h"
#include "SparkFunLSM6DS3.h" //lib https://github.com/Seeed-Studio/Accelerometer_And_Gyroscope_LSM6DS3
#include "ImpactSensor.h"


////////// Object Instantiation //////////////////
/*************************************************************
 * Safety Vest
 *
 * ->all in this file
 */
const interval_t PUBLISH_INTERVAL = 1500; //(1500)

/*************************************************************
 * Modem
 */
const int chipSelect = 43;
char data[MAX_DATA_SIZE] ;
char geohash[13] = "nofix"; //use precision 12
WioLTE wioLte;
Modem modem(&wioLte, &SD, geohash);

/*************************************************************
 * LED stripe
 */
LEDStripe leds(WioLTE::D19);

/***************************************************************
 * Panik Button
 */
PanikButton panikBtn(WioLTE::D20);

/**************************************************************
 * Temperature, HUmidity, Pressure Sensor
 */
temperature_t temp;
humidity_t humi;
pressure_t pressure;
BME280 bme280;
HumiditySensor humiditySensor(&bme280, &temp, &humi, &pressure);

/*************************************************************
 * Noise sensor
 */
noiseLevel_t noise;
NoiseSensor noiseSensor(&noise);

/**************************************************************
 * Air Quality Sensor
 */
//AirqualitySensor airqualitySensor(AIRQUALITY_SENSOR_PIN);
airquality_t airquality;
AirQualitySensor airQualitySensor(&airquality);

/***************************************************************
 * Impact Sensor
 */
bool dropDetected = false;
//bool dropDetectedOnce = false;
LSM6DS3 lsm6ds3( I2C_MODE, 0x6A );  //I2C device address 0x6A
ImpactSensor impactSensor(&lsm6ds3);


//////// Global primitive variables /////////////////
interval_t publish_interval = PUBLISH_INTERVAL;
elapsedMillis_t currentMillis = 0;
elapsedMillis_t previousMillis = 0;




//////  The Arduino way ///////////////////
void setup()
{

    /*TODO
	delay(200);

	DPRINTLN("### Initialize SD card.");
    wioLte.PowerSupplySD(true);
    pinMode(SS, OUTPUT);
	if (!SD.begin(chipSelect)) {
		DPRINTLN("### ERROR! failed to initialize SD card ###");
	    return;
	};*/

	delay(200);
	DPRINTLN("### Start Modem Setup.");
	modem.setup();
	leds.setup();
	panikBtn.setup();


	DPRINTLN("### Initialize humidity sensor.");
	humiditySensor.setup();
	DPRINTLN("### Initialize noise sensor.");
    noiseSensor.setup();
    DPRINTLN("### Initialize air sensor.");
    airQualitySensor.setup();
    DPRINTLN("### Initialize impact sensor.");
	impactSensor.setup();
	DPRINTLN("### Setup completed.");
}

//// The loop function is called in an endless loop
void loop()
{

	elapsedMillis_t measuredelay = millis();
	modem.loop();
	leds.loop();
	panikBtn.loop();
	humiditySensor.loop();
    noiseSensor.loop();
    airQualitySensor.loop();
    impactSensor.loop();


    currentMillis = millis();
    if (currentMillis - previousMillis >= publish_interval) {
		//rgbLed.pureColor(previousMillis % 3);
		//rgbLed.WS2812Send();

        //publish
	    noiseSensor.stop();//there is probably a killing delay in WiolTE API(inside modem)
	    airQualitySensor.stop();//there is probably a killing delay in WiolTE API(inside modem)
	    dropDetected = impactSensor.dropDetected(); //show a bit longer in GUI
	    if (impactSensor.dropDetectedOnce()){
	    	leds.alarmOn(6);
	    	panikBtn.push();
	    };
	    if (airquality == AIR_QUALITY::HIGH_POLLUTION) {
	    	leds.alarmOn(1);
	    };
	    if (airquality == AIR_QUALITY::FORCE_SIGNAL){
	    	leds.alarmOn(1);//TODO: disable this for some amount of time, due slow slope of sensor it will occur too often
	    	panikBtn.push();
	    };
	    sprintf(data,"{\"temperature\":%.2f,\"humidity\":%.2f,\"pressure\":%.2f,\"noise\":%d,\"air\":%d,\"drop\":%d,\"geo\":\"%s\"}", temp, humi, pressure, noise, airquality, dropDetected, geohash);
	    PRINTLN(data);
        modem.sendUdpMessage(data); //TODO: this function blocks if there is no network...disable it when PS activation or ping failed
        noiseSensor.start();
        airQualitySensor.start();
        previousMillis = millis();

	   }
    //PRINTLN(millis() - measuredelay);
};
