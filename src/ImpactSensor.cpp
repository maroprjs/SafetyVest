/*
 * ImpactSensor.cpp
 *
 *  Created on: 6 Feb 2020
 *      Author: maro
 */

#include "ImpactSensor.h"
#include "Debug.h"
#include <Arduino.h>

ImpactSensor::ImpactSensor(LSM6DS3 * lsm6ds3) {
	_lsm6ds3 = lsm6ds3;
	_dropActiveCounter = 0;
	_dropDetected = false;
	_dropDetectedOnce = false;

}

void ImpactSensor::setup(){
	if( _lsm6ds3->begin() != 0 )
	{
		DPRINTLN("### ERROR LSM6DS3 Device error! ####");
	}else{
		DPRINTLN("LSM6DS3 Device OK!");
	    if(0 != config_free_fall_detect()) DPRINTLN("### ERROR LSM6DS3 Failed to configure! ###");
	};
}

int ImpactSensor::config_free_fall_detect(void)
{
	uint8_t error = 0;
  uint8_t dataToWrite = 0;

  dataToWrite |= LSM6DS3_ACC_GYRO_BW_XL_200Hz;
  dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_2g;
  dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_416Hz;

  error += _lsm6ds3->writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);
	error += _lsm6ds3->writeRegister( LSM6DS3_ACC_GYRO_WAKE_UP_DUR, 0x00 );
  error += _lsm6ds3->writeRegister(LSM6DS3_ACC_GYRO_FREE_FALL, 0x33);
  error += _lsm6ds3->writeRegister( LSM6DS3_ACC_GYRO_MD1_CFG, 0x10 );
	error += _lsm6ds3->writeRegister( LSM6DS3_ACC_GYRO_MD2_CFG, 0x10 );
  error += _lsm6ds3->writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, 0x01);

  return error;
}

void ImpactSensor::loop(void){
   uint8_t readDataByte = 0;
   //Read the wake-up source register
   _lsm6ds3->readRegister(&readDataByte, LSM6DS3_ACC_GYRO_WAKE_UP_SRC);
   //Mask off the FF_IA bit for free-fall detection
   readDataByte &= 0x20;
   if( readDataByte )
   {
	  DPRINTLN("Free fall detected!  ");
	  _dropDetected = true;
	  _dropDetectedOnce = true;
	  _dropActiveCounter = 0;
   };
}

bool ImpactSensor::dropDetected(void){
	//DPRINTLN("drop detected called");
	if (_dropDetected){
		_dropActiveCounter++;
		//DPRINT(_dropActiveCounter);
		if (_dropActiveCounter >= REMAIN_ACTIVE_COUNT){
			_dropActiveCounter = 0;
			_dropDetected = false;
		};
	}

	return _dropDetected;
}

bool ImpactSensor::dropDetectedOnce(void){
	bool retVal = false;
	if (_dropDetectedOnce){
		retVal = true;
		_dropDetectedOnce = false;

	}

	return retVal;
}

ImpactSensor::~ImpactSensor() {
	// TODO Auto-generated destructor stub
}

