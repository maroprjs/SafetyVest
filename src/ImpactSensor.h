/*
 * ImpactSensor.h
 *
 *  Created on: 6 Feb 2020
 *      Author: maro
 *
 *      ref: https://github.com/Seeed-Studio/Accelerometer_And_Gyroscope_LSM6DS3 example free fall detect
 *           http://wiki.seeedstudio.com/Grove-6-Axis_AccelerometerAndGyroscope/
 *
 */

#ifndef IMPACTSENSOR_H_
#define IMPACTSENSOR_H_
#include "SparkFunLSM6DS3.h"

#define REMAIN_ACTIVE_COUNT 10  //if drop happens only shortly, the alert must be recognized

class ImpactSensor {
public:
	ImpactSensor(LSM6DS3 * lsm6ds3);
	void setup();
	void loop();
	bool dropDetected(void);
	bool dropDetectedOnce(void);
	virtual ~ImpactSensor();
private:
	LSM6DS3 * _lsm6ds3;
	bool _dropDetected;
	bool _dropDetectedOnce;
	unsigned int _dropActiveCounter;
	int config_free_fall_detect(void);
};

#endif /* IMPACTSENSOR_H_ */
