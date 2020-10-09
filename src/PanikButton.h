/*
 * PanikButton.h
 *
 *  Created on: 8 Mar 2020
 *      Author: maro
 */

#ifndef PANIKBUTTON_H_
#define PANIKBUTTON_H_

#include "TypeDefs.h"

#define PANIK_ON HIGH //motordriver inverses
#define PANIK_OFF LOW

#define BTN_REMAIN_PUSHED (100)

class PanikButton {
public:
	PanikButton(sensorPin_t sensorPin);
	void setup(void);
	void loop(void);
	void push(void);
	virtual ~PanikButton();
private:
	sensorPin_t _sensorPin;
	elapsedMillis_t _alarmStartedTime;
};

#endif /* PANIKBUTTON_H_ */
