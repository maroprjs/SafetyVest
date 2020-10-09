/*
 * LEDStripe.cpp
 *
 *  Created on: 8 Mar 2020
 *      Author: maro
 */

#include "LEDStripe.h"

LEDStripe::LEDStripe(sensorPin_t sensorPin) {
	_sensorPin = sensorPin;
	_lastPinUpdate = 0;
	_countDown = 0;
	_onOffTime = 0;
	_onOffTimeSet = NULL;
	_alarmStateCount = 0;

}

void LEDStripe::setup(){
	pinMode(_sensorPin, OUTPUT);//alarm LEDs
	digitalWrite(_sensorPin, LEDS_OFF);

	_onOffTimeSet = new onOffTimeSet_t[NUM_OF_ALARM_LED_STATES];
	_onOffTimeSet[0].on = 50; _onOffTimeSet[0].off = 50;
	_onOffTimeSet[1].on = 50; _onOffTimeSet[1].off = 50;
	_onOffTimeSet[2].on = 50; _onOffTimeSet[2].off = 50;
	_onOffTimeSet[3].on = 50; _onOffTimeSet[3].off = 50;
	_onOffTimeSet[4].on = 0; _onOffTimeSet[4].off = 3000;

	_lastPinUpdate = millis();
}

void LEDStripe::loop(){
	animateAlarm();
}

int LEDStripe::getOffTime(void){
	_alarmStateCount++;
	return _onOffTimeSet[_alarmStateCount - 1].off;
}

int LEDStripe::getOnTime(void){
	return _onOffTimeSet[_alarmStateCount].on;
}

void LEDStripe::animateAlarm(){
	if (_countDown){

	   if (millis() >= (_lastPinUpdate + _onOffTime)){
		   int onoff = (digitalRead(_sensorPin) == LEDS_OFF) ? getOnTime() : getOffTime();
		   _onOffTime = onoff;
		   digitalWrite(_sensorPin, !digitalRead(_sensorPin));
		   _lastPinUpdate = millis();
	   };

	   if (_alarmStateCount == NUM_OF_ALARM_LED_STATES) {
		   digitalWrite(_sensorPin, LEDS_OFF);
		   _countDown--;
		   _alarmStateCount = 0;
	   }
	};
}

void LEDStripe::alarmOn(int countDown ){
	_countDown = countDown;
	_lastPinUpdate = millis();
}


LEDStripe::~LEDStripe() {
	// TODO Auto-generated destructor stub
}

