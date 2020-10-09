/*
 * Debug.h
 *
 *  Created on: 02.02.2020
 *      Author: maro
 */

#ifndef DEBUG_H_
#define DEBUG_H_




//#define DEBUG
#ifdef DEBUG
	//#define PRINT_INIT(x)	SerialUSB.begin(x)

	#define DPRINT(x)  	SerialUSB.print(x)
	#define DPRINTLN(x)  SerialUSB.println(x)
	#define ZVERSION "debug xxx " + String(__DATE__)

#else
	#define PRINT_INIT(...)
	#define DPRINT(...)
	#define DPRINTLN(...)
	#define ZVERSION "v1.1.0" + String(__DATE__)

#endif

	#define PRINT(x)  	SerialUSB.print(x)
	#define PRINTLN(x)  SerialUSB.println(x)
	#define ZUP_TIME " " + String(millis()/1000) + " [s]"

#endif /* DEBUG_H_ */
