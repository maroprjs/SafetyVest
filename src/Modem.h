/*
 * Modem.h
 *
 *  Created on: 4 Feb 2020
 *      Author: maro
 *
 *
 *      ref:
 *         http://wiki.seeedstudio.com/Wio_LTE_Cat.1/
 *         https://www.techiedelight.com/convert-string-char-array-cpp/
 */

#ifndef MODEM_H_
#define MODEM_H_

#include "TypeDefs.h"
#include <WioLTEforArduino.h>
#include <SD.h>                    // https://github.com/Seeed-Studio/SD



//#define CONFIG_FILE_NAME "modem.txt"
#define APN                    "internet"
#define USERNAME               ""
#define PASSWORD               ""
#define UDP_HOST               "127.0.0.1"
#define UDP_PORT               8888
#define CHECK_ALIVE_HOST       "127.0.0.1"
#define DEFAULT_SMS_RECEIVER  "0012345678"

#define DEFAULT_CONNECTION_CHECK_INTERVAL 120000 //TODO: every two minutes?
#define MAX_ALIVE_COUNTS       3 //reboot modem after three failed checks
#define DEFAULT_LOCATION_CHECK_INTERVAL 60000
#define MAX_DATA_SIZE 1024
#define MAX_HOST_URL_LENGTH    100



class Modem {
public:
	Modem(WioLTE* modem,SDClass* sd, char* geohash, interval_t connCheckInterval = DEFAULT_CONNECTION_CHECK_INTERVAL, interval_t locCheckInterval = DEFAULT_LOCATION_CHECK_INTERVAL);

	void setup();
	void loop();
	void sendUdpMessage(char* data);
	virtual ~Modem();
private:
	WioLTE* _modem;
	SDClass* _sd;
	char _udp_host[MAX_HOST_URL_LENGTH];// = UDP_HOST;
	udpPort_t _udp_port;// = UDP_PORT;
	socketId_t _socketId;
	elapsedMillis_t _elapsedConnectionCheckTime;
	interval_t _connectionCheckInterval;
	checkAliveCounter_t _checkAliveCount;
	elapsedMillis_t _elapsedLocationCheckTime;
	interval_t _locationCheckInterval;
	char * _geohash;
	double _longitude;
	double _latitude;
    double _altitude;
    struct tm _utc;
	void reactivateModem( void );
	void connectionCheck(void);
	void locationCheck(void);

};

#endif /* MODEM_H_ */
