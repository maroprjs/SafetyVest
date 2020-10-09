/*
 * Modem.cpp
 *
 *  Created on: 4 Feb 2020
 *      Author: maro
 */

#include "Modem.h"
#include "Debug.h"
#include <stdio.h>
//#include "geohash.h"
extern "C" {  //https://stackoverflow.com/questions/5559250/c-error-undefined-reference-to-function-but-it-is-defined
#include "geohash.h"
}


Modem::Modem(WioLTE* modem, SDClass* sd, char* geohash, interval_t connCheckInterval, interval_t locCheckInterval) {
	_modem = modem;
	_sd = sd;
	_connectionCheckInterval = connCheckInterval;
	_elapsedConnectionCheckTime = 0;
	_socketId = 0;
	_locationCheckInterval = locCheckInterval;
	_elapsedLocationCheckTime = 0;
	std::string s = UDP_HOST;
	//char cstr[s.size];
	//_udp_host[MAX_HOST_URL_LENGTH] = UDP_HOST;
	s.copy(_udp_host, s.size());
	_udp_port = UDP_PORT;
	_checkAliveCount = 0;
	_geohash = geohash;
	_altitude = 0;
	_latitude = 0;
	_longitude = 0;

}

void Modem::setup(){
	//init modem
	DPRINTLN("initLTE ON...\n");
	_modem->Init();
    DPRINTLN("Powering LTE ON...\n");
    _modem->PowerSupplyLTE(true);
	delay(500);
	_modem->PowerSupplyGNSS(true);
	  delay(500);
	DPRINTLN("### Turn on or reset.");
	if (!_modem->TurnOnOrReset()) {
	    DPRINTLN("### ERROR! Modem TurnOnOrReset ###");
	};


	//read config from SD card:
	//TODO:
	/*
	File myFile;

	DPRINTLN("###Modem Reading from "CONFIG_FILE_NAME".");
	myFile = _sd->open(CONFIG_FILE_NAME, FILE_WRITE); //TODO: take this off after test
	   if (myFile) {
	      DPRINTLN(CONFIG_FILE_NAME":");
		  while (myFile.available()) {
		     DPRINTLN(myFile.read());
		  }
		  myFile.close();
	  }else{
		  DPRINTLN("### ERROR! opening file ###");
	  };
	  if (_sd->exists(CONFIG_FILE_NAME)) {
		  DPRINTLN("example.txt exists.");
	  }
	  else {
		  DPRINTLN("example.txt doesn't exist.");
	  }*/
    //<--TODO

	DPRINTLN("### Connecting to \""APN"\".");
	if (!_modem->Activate(APN, USERNAME, PASSWORD)) {
	  DPRINTLN("### ERROR! Modem Activation###");
	};
    //power for sensors
	_modem->PowerSupplyGrove(true);

	//check sms and forward to maintainer:
	char str[100];
	int strLen = _modem->ReceiveSMS(str, sizeof (str));
	if (strLen < 0) {
		DPRINTLN("### ERROR! readning sms failed ###");
	};
	if (strLen > 0) {
		DPRINT("### SMS: ");DPRINT(str);DPRINTLN(" ###");

		  if (!_modem->SendSMS(DEFAULT_SMS_RECEIVER, str)) {
			  DPRINTLN("### ERROR! sending sms failed ###");
		  };
		/*test first above.
	    if (!_modem->DeleteReceivedSMS()) {
	    	DPRINTLN("### ERROR! deleteing sms failed ###");
	    };*/
	};

	//GNSS
	DPRINTLN("### Enable GNSS.");
	  if (!_modem->EnableGNSS()) {
		  DPRINTLN("### ERROR! enabling gnss failed ###");
	  }

	_elapsedConnectionCheckTime = millis();
	_elapsedLocationCheckTime = millis();
}

void Modem::loop() {

	//connectionCheck(); TODO: this one blocks transmission...find a better way
	locationCheck();


}

void Modem::connectionCheck(void ){
	if ( millis() >= (_elapsedConnectionCheckTime + _connectionCheckInterval)) {
	   //_elapsedTime = _elapsedTime - _statusCheckInterval;
       if (! _modem->PsActive()) {
    	  DPRINTLN("### ERROR! PS Not Active ...reactivation...###");
    	  reactivateModem();
       };
       if (! _modem->Ping(CHECK_ALIVE_HOST)) {
    	   DPRINTLN("### ERROR! PS alive check failed .###");
    	   _checkAliveCount++;
    	   if (_checkAliveCount >= MAX_ALIVE_COUNTS){
    		   DPRINTLN("### ERROR! PS alive check failed ....reactivate....###");
    		  reactivateModem();
    		  _checkAliveCount = 0;
    	   };
       };
	   _elapsedConnectionCheckTime = millis();
    };
}

void Modem::locationCheck(void ){
	if ( millis() >= (_elapsedLocationCheckTime + _locationCheckInterval)) {

		  DPRINTLN("### Get GNSS location.");
		  bool getLocation = _modem->GetGNSSLocation(&_longitude, &_latitude, &_altitude, &_utc);
		  if (getLocation) {
			  DPRINT("    long: ");
			  SerialUSB.println(_longitude, 6);
			  DPRINT("    lat: ");
			  SerialUSB.println(_latitude, 6);
			  DPRINT("    altitude: ");
			  SerialUSB.println(_altitude, 6);
			  DPRINT("    utc: ");
			  DPRINTLN(asctime(&_utc));
			  sprintf(_geohash, "%s", geohash_encode(_latitude, _longitude, 12)); //12 is precision default value(?)
			  //_geohash = geohash_encode(_latitude, _longitude, 12); //12 is precision default value(?)
		  }
		  else if (_modem->GetLastError() == WioLTE::E_GNSS_NOT_FIXED) {
			  DPRINTLN("### NOT FIXED GPS . ###");
			  if (_modem->GetLocation(&_longitude, &_latitude)){
				  DPRINT("    long: ");
				  SerialUSB.println(_longitude, 6);
				  DPRINT("    lat: ");
				  SerialUSB.println(_latitude, 6);
				  sprintf(_geohash, "%s", geohash_encode(_latitude, _longitude, 12)); //12 is precision default value(?)->set to 9 for ngeohash GUI(default value)
				  //_geohash = geohash_encode(_latitude, _longitude, 12); //12 is precision default value(?)
			  }else{
				  DPRINTLN("### NO CELL BASED LOCATION EITHER . ###");
				  sprintf(_geohash, "nofix");
			  };

		  }
		  else {
			  DPRINTLN("### ERROR! ###");
			  sprintf(_geohash, "nofix");
		  }

	   _elapsedLocationCheckTime = millis();
    };
}


void Modem::reactivateModem( void ){
	if (!_modem->TurnOnOrReset()) {
	    DPRINTLN("### ERROR! Modem TurnOnOrReset ###");
	};
	DPRINTLN("### Connecting to \""APN"\".");
	if (!_modem->Activate(APN, USERNAME, PASSWORD)) {
	  DPRINTLN("### ERROR! Modem Activation###");
	};
}

void Modem::sendUdpMessage(char* data){
	//DPRINTLN(_udp_host);
	//DPRINTLN(_udp_port);
	_socketId = _modem->SocketOpen(_udp_host, _udp_port, WioLTE::SOCKET_UDP);
	if (_socketId){
		if (! _modem->SocketSend(_socketId, data)) DPRINTLN("### ERROR sending udp message! ###");
		if (!_modem->SocketClose(_socketId)) DPRINTLN("### ERROR closing udp socket! ###");
	}else{
		DPRINTLN("### ERROR opening udp socket! ###");
	};
}

Modem::~Modem() {
	// TODO Auto-generated destructor stub
}

