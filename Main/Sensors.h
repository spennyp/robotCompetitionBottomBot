// Sensors.h

#ifndef _SENSORS_h
#define _SENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern bool clawTriggered();
extern bool foundCliff();
extern bool bridgeAligned();
extern bool leftBridgeAligned();
extern bool rightBridgeAligned();

#endif