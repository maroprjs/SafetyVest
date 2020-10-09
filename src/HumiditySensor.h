/*
 * HumiditySensor.h
 *
 *  Created on: 4 Feb 2020
 *      Author: maro
 */

#ifndef HUMIDITYSENSOR_H_
#define HUMIDITYSENSOR_H_

#include "TypeDefs.h"
#include "Seeed_BME280.h"

#define DEFAULT_MEASUREMENT_INTERVAL 1000

class HumiditySensor {
public:
	HumiditySensor(BME280* bme280, temperature_t* temp, humidity_t* humi, pressure_t* pressure, interval_t interval = DEFAULT_MEASUREMENT_INTERVAL);
	void setup();
	void loop();
	virtual ~HumiditySensor();

private:
	temperature_t* _temp;
	humidity_t* _humi;
	pressure_t* _pressure;
	BME280* _sensor;
	elapsedMillis_t _elapsedTime;
	interval_t _measurementInterval;
};

#endif /* HUMIDITYSENSOR_H_ */

