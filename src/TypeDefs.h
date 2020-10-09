/*
 * TypeDefs.h
 *
 *  Created on: 3 Feb 2020
 *      Author: maro
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

//#include <WioLTEforArduino.h>
#include <Arduino.h>

enum AIR_QUALITY
{
	FORCE_SIGNAL                   = 0,
	HIGH_POLLUTION	               = 1,
	LOW_POLLUION                   = 2,
	FRESH_AIR                      = 3
};

typedef enum AIR_QUALITY airquality_t;
//typedef uint16_t airquality_t;

typedef unsigned long uint32_t;
//typedef unsigned int uint16_t;

typedef uint32_t interval_t;
typedef uint32_t elapsedMillis_t;

typedef float humidity_t;
typedef float temperature_t;
typedef float pressure_t;


typedef uint16_t noiseLevel_t;
typedef uint16_t sensorPin_t;

typedef uint16_t udpPort_t;
typedef uint16_t socketId_t;




typedef uint16_t checkAliveCounter_t;


#endif /* TYPEDEFS_H_ */
