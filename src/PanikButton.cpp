/*
 * PanikButton.cpp
 *
 *  Created on: 8 Mar 2020
 *      Author: maro
 */

#include "PanikButton.h"

PanikButton::PanikButton(sensorPin_t sensorPin) {
	_sensorPin = sensorPin;
	_alarmStartedTime = 0;

}

void PanikButton::setup(){
	pinMode(_sensorPin, OUTPUT);//panik button
	digitalWrite(_sensorPin, PANIK_OFF);
}

void PanikButton::loop(){
	if (millis() >= (_alarmStartedTime + BTN_REMAIN_PUSHED)){
		digitalWrite(_sensorPin, PANIK_OFF);
	}
}

void PanikButton::push(){
	digitalWrite(_sensorPin, PANIK_ON);
	_alarmStartedTime = millis();
}

PanikButton::~PanikButton() {
	// TODO Auto-generated destructor stub
}

