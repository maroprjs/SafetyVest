/*
 * HumiditySensor.cpp
 *
 *  Created on: 4 Feb 2020
 *      Author: maro
 */

#include "HumiditySensor.h"
#include "Debug.h"

HumiditySensor::HumiditySensor(BME280* bme280, temperature_t* temp, humidity_t* humi, pressure_t* pressure, interval_t interval) {
	_temp = temp;
	_humi = humi;
	_pressure = pressure;
	_sensor = bme280;
	_measurementInterval = interval;
	_elapsedTime = 0;


}

void HumiditySensor::setup(){
    if(!_sensor->init()){
      DPRINTLN("### ERROR BME280 Device error! ####");
    }else {
    	DPRINTLN("### BME280 Device found! ####");
    };
	_elapsedTime = millis();


}


void HumiditySensor::loop() {
	//_elapsedTime = millis();
	if ( millis() >= (_elapsedTime + _measurementInterval)) {
		//_elapsedTime = _elapsedTime - _measurementInterval;
		_elapsedTime = millis();
		*_temp = _sensor->getTemperature();
		*_humi = _sensor->getHumidity();
		*_pressure = _sensor->getPressure() / 100; //convert to hPa
	}
}

HumiditySensor::~HumiditySensor() {
	// TODO Auto-generated destructor stub
}

