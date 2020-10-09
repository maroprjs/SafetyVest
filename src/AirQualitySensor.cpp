/*
 * AirQualitySensor.cpp
 *
 *  Created on: 5 Feb 2020
 *      Author: maro
 */

#include "AirQualitySensor.h"

#include "Debug.h"

AirQualitySensor::AirQualitySensor(airquality_t* airquality, sensorPin_t sensorPin, interval_t interval) {
	_sampleWindow = interval;
	_sampleInterval = interval;
	_sensorPin = sensorPin;
	//_noiseLevel = 0;
	//_elapsedTime = 0;
	_signalMax = SIGNAL_MAX;
	_signalMin = SIGNAL_MIN;
	_sample = 0;
	_lastSample = 0;
	_peakToPeak = 0;
	_sampleCount = 0;
	_sampleSum = 0;
	_avgSample = 0;
	_airquality = airquality;
	_startMillis = 0;
	_lastAvgValueUpdated = 0;
	_stopped = true;
}

void AirQualitySensor::setup(){
	DPRINTLN("AirQualitySensor::begin() called");
	pinMode(_sensorPin, INPUT_ANALOG);
	*_airquality = AIR_QUALITY::FRESH_AIR;
	_startMillis = millis(); // Start of sample window <-make sure this is called as one of the last function in setup
	_lastAvgValueUpdated = millis();
	start(); // Start of sample window <-make sure this is called as one of the last function in setup

}

void AirQualitySensor::start(){
	//_signalMax = SIGNAL_MIN;
	//_signalMin = SIGNAL_MAX;
	//_sample = 0;
	//_lastSample = 0;
	//_peakToPeak = 0;
	//_sampleCount = 0;
	//_sampleSum = 0;
	//_avgSample = 0;
	_stopped = false;

}
void AirQualitySensor::stop(){
	_stopped = true;

}

//note, this is called in main loop()
void AirQualitySensor::loop() {

	   if (! _stopped){

		   //Dont use together! (startMillis interfere)
		   //handleSampleWindow(); // collect data for given time window
		   handleSampleInterval(); // collect data at every given time interval
	   }
}

// collect data for given time window
//adafruit microfon niose levels:
void AirQualitySensor::handleSampleWindow(void){
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

    }else{
 	      _peakToPeak = _signalMax - _signalMin;  // max - min = peak-peak amplitude
		  _signalMax = SIGNAL_MIN;
		  _signalMin = SIGNAL_MAX;
		  _startMillis= millis();  // Start of sample window

    }

}

// collect data at every given time interval
//https://github.com/Seeed-Studio/Grove_Air_quality_Sensor
void AirQualitySensor::handleSampleInterval(void){

	if(millis() > _sampleInterval +_startMillis) {
       _lastSample = _sample;
       _sample = analogRead(_sensorPin);
       _sampleSum += _sample;
       _sampleCount ++;

       updateAvgValue();
       if (_sample - _lastSample > HIGH_POLLUTION_THR || _sample > FORCE_SIGNAL_THR) {
    	   *_airquality = AIR_QUALITY::FORCE_SIGNAL;
       } else if ((_sample - _lastSample > HIGH_POLLUTION_THR && _sample < FORCE_SIGNAL_THR)
                  || _sample - _avgSample > HIGH_POLLUTION_MAX_AVG_DIFF) {
    	   *_airquality = AIR_QUALITY::HIGH_POLLUTION;
       } else if ((_sample - _lastSample > LOW_POLLUTION_THR && _sample < FORCE_SIGNAL_THR)
                  || _sample - _avgSample > LOW_POLLUTION_MAX_AVG_DIFF) {
    	   *_airquality = AIR_QUALITY::LOW_POLLUION;
       } else {
           *_airquality = AIR_QUALITY::FRESH_AIR;
       };
       //DPRINT(_sample);DPRINT(" ");DPRINT(_lastSample);DPRINT(" ");DPRINTLN(_sample - _avgSample);
       _startMillis= millis();
    };
}

void AirQualitySensor::updateAvgValue(void) {
    if (millis() - _lastAvgValueUpdated > AVG_SAMPLE_INTERVAL) {
        _avgSample = _sampleSum / _sampleCount;
        _lastAvgValueUpdated = millis();

        _sampleSum = 0;
        _sampleCount = 0;
    }
}

sensorPin_t AirQualitySensor::getPeakToPeakAmplitude(){
	return _peakToPeak;
}


AirQualitySensor::~AirQualitySensor() {
	// TODO Auto-generated destructor stub
}

