/*
 * NoiseSensor.cpp
 *
 *  Created on: 3 Feb 2020
 *      Author: maro
 */

#include "NoiseSensor.h"
#include "Debug.h"

NoiseSensor::NoiseSensor(noiseLevel_t* noise, sensorPin_t sensorPin, interval_t interval) {
	_sampleWindow = interval;
	_sensorPin = sensorPin;
	_noiseLevel = 0;
	//_elapsedTime = 0;
	_signalMax = SIGNAL_MAX;
	_signalMin = SIGNAL_MIN;
	_sample = 0;
	_peakToPeak = noise;
	_startMillis = 0;
	_stopped = true;
}

void NoiseSensor::setup(){
	DPRINTLN("NoiseSensor::begin() called");
	pinMode(_sensorPin, INPUT_ANALOG);
	start(); // Start of sample window <-make sure this is called as one of the last function in setup

}

void NoiseSensor::start(){
	_signalMax = SIGNAL_MIN;
	_signalMin = SIGNAL_MAX;
	_sample = 0;
	*_peakToPeak = 0;
	_startMillis= millis(); // Start of sample window <-make sure this is called as one of the last function in setup
	_stopped = false;

}
void NoiseSensor::stop(){
	_stopped = true;

}

//note, this is called in main loop()
void NoiseSensor::loop() {

	   if (! _stopped){
	      // collect data for given time window
	      if(millis() - _startMillis < _sampleWindow)
	      {
	         _sample = analogRead(_sensorPin);
	         if (_sample < SIGNAL_MAX)  // toss out spurious readings
	         {
	            if (_sample > _signalMax)
	            {
	               _signalMax = _sample;  // save just the max levels
	            }
	            else if (_sample < _signalMin)
	            {
	               _signalMin = _sample;  // save just the min levels
	            }
	         }
	         //_startMillis = millis();
	      }
	      else{
	   	      *_peakToPeak = _signalMax - _signalMin;  // max - min = peak-peak amplitude
			  _signalMax = SIGNAL_MIN;
			  _signalMin = SIGNAL_MAX;
		      _startMillis= millis();  // Start of sample window
	      }
	   }
}


sensorPin_t NoiseSensor::getPeakToPeakAmplitude(){
	return *_peakToPeak;
}

NoiseSensor::~NoiseSensor() {
	// TODO Auto-generated destructor stub
}

