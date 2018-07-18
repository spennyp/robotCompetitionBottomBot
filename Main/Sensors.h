// Sensors.h

#ifndef _SENSORS_h
#define _SENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern bool checkCodeRedSwitch();
extern bool clawIRTriggered();
extern bool topBotFoundCliff();
extern bool bottomBotFoundCliff();
extern bool leftPlankInPosition();
extern bool rightPlankInPosition();

#endif