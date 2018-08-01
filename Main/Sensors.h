// Sensors.h

#ifndef _SENSORS_h
#define _SENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern bool clawIRTriggered();
extern bool foundCliff();
extern bool frontTouchSensorTriggered();
extern bool topHallTriggered();
extern bool bottomHallTriggered();

#endif