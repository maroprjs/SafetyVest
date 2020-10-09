/*
 * NoiseSensor.h
 *
 *  Created on: 3 Feb 2020
 *      Author: maro
 *
 *      //ref:
 *      https://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels
 */

#ifndef NOISESENSOR_H_
#define NOISESENSOR_H_

#include "TypeDefs.h"
#include <WioLTEforArduino.h>


#define DEFAULT_SAMPLE_WINDOW 200
#define DEFAULT_SENSOR_PIN WioLTE::A5
#define SIGNAL_MAX 4096 //WioLTE ADC = 12bit
#define SIGNAL_MIN 0

class NoiseSensor {
public:
	NoiseSensor(noiseLevel_t* noise, sensorPin_t sensorPin = DEFAULT_SENSOR_PIN, interval_t interval = DEFAULT_SAMPLE_WINDOW);
	void setup();
	void loop();
	void start();
	void stop();
	sensorPin_t getPeakToPeakAmplitude();
	virtual ~NoiseSensor();
private:
	interval_t _sampleWindow;
	sensorPin_t _sensorPin;
	//elapsedMillis_t _elapsedTime;
	noiseLevel_t _noiseLevel;
	sensorPin_t _signalMax;
	sensorPin_t _signalMin;
	sensorPin_t _sample;
	sensorPin_t * _peakToPeak;
	elapsedMillis_t _startMillis;
	bool _stopped;
};

#endif /* NOISESENSOR_H_ */
