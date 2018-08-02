// Helpers.h

#ifndef _HELPERS_h
#define _HELPERS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else 
#include "WProgram.h" 
#endif


// Sensors
extern bool clawTriggered();
extern bool foundCliff();


// RunHelpers
extern void activateDumper();
extern void resetDumper();
extern void deployBridge();
extern void resetBridge();
extern bool bridgeAligned();
extern bool leftBridgeAligned();
extern bool rightBridgeAligned();

#endif