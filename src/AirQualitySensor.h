/*
 * AirQualitySensor.h
 *
 *  Created on: 5 Feb 2020
 *      Author: maro
 *
 *      ref:
 *      https://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels
 *      http://wiki.seeedstudio.com/Grove-Air_Quality_Sensor_v1.3/
 *      https://github.com/Seeed-Studio/Grove_Air_quality_Sensor
 */

#ifndef AIRQUALITYSENSOR_H_
#define AIRQUALITYSENSOR_H_

#include "TypeDefs.h"
#include <WioLTEforArduino.h>


#define DEFAULT_SAMPLE_WINDOW 500 //= DEFAULT SAMPLE INTERVAL
#define AVG_SAMPLE_INTERVAL 500000

#define DEFAULT_SENSOR_PIN WioLTE::A4
#define SIGNAL_MAX 4096 //WioLTE ADC = 12bit
#define SIGNAL_MIN 0

#define FORCE_SIGNAL_THR (2800) // 700
#define HIGH_POLLUTION_THR (1600) //400
#define HIGH_POLLUTION_MAX_AVG_DIFF (600) //150
#define LOW_POLLUTION_THR (800) //200
#define LOW_POLLUTION_MAX_AVG_DIFF (200) //50

class AirQualitySensor {
public:
	AirQualitySensor(airquality_t* airquality, sensorPin_t sensorPin = DEFAULT_SENSOR_PIN, interval_t interval = DEFAULT_SAMPLE_WINDOW);
	void setup();
	void loop();
	void start();
	void stop();
	sensorPin_t getPeakToPeakAmplitude();
	virtual ~AirQualitySensor();

private:
	interval_t _sampleWindow;
	interval_t _sampleInterval;
	sensorPin_t _sensorPin;
	//elapsedMillis_t _elapsedTime;
	//noiseLevel_t _noiseLevel;
	sensorPin_t _signalMax;
	sensorPin_t _signalMin;
	sensorPin_t _sample; //= current sample
	sensorPin_t _lastSample;
	sensorPin_t _peakToPeak;
	uint32_t _sampleSum;
	uint16_t _sampleCount;
	sensorPin_t _avgSample;
	airquality_t* _airquality;
	elapsedMillis_t _startMillis;
	elapsedMillis_t _lastAvgValueUpdated;
	bool _stopped;

	void handleSampleWindow(void);
	void handleSampleInterval(void);
	void updateAvgValue(void);
};

#endif /* AIRQUALITYSENSOR_H_ */
