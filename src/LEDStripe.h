/*
 * LEDStripe.h
 *
 *  Created on: 8 Mar 2020
 *      Author: maro
 */

#ifndef LEDSTRIPE_H_
#define LEDSTRIPE_H_

#include "TypeDefs.h"

#define LEDS_ON LOW //motordriver inverses
#define LEDS_OFF HIGH

#define NUM_OF_ALARM_LED_STATES (5)

typedef struct onOffTimeSet_t { //this is On Off time for the driving pin of the LED stripe
   uint8_t on;
   uint8_t off;
} onOffTimeSet;

class LEDStripe {
public:
	LEDStripe(sensorPin_t sensorPin);
	virtual ~LEDStripe();
	void setup(void);
	void loop(void);
	void alarmOn(int countDown);
private:
	sensorPin_t _sensorPin;
	elapsedMillis_t _lastPinUpdate;
	elapsedMillis_t _onOffTime;
	int _countDown;
	int _alarmStateCount;
	onOffTimeSet_t* _onOffTimeSet;

	int getOffTime(void);
	int getOnTime(void);
	void animateAlarm(void);


};

#endif /* LEDSTRIPE_H_ */
