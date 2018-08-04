// Helpers.h

#ifndef _HELPERS_h
#define _HELPERS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else 
#include "WProgram.h" 
#endif
#include "MotorWheel.h"

extern int bridgeDropDelay;

// Reset constants
extern int bridgeServoResetPosition;

// Deploy constants
extern int bridgeServoDeployPosition;

// Sensors
extern int cliffCount;
extern bool bridgeQRDSAligned;
extern bool clawTriggered();
extern bool foundLeftCliff();
extern bool foundRightCliff();
extern void detatchTopBot();


// RunHelpers
extern void deployBridge();
extern void resetBridge();
extern bool bridgeAligned();
extern bool leftBridgeAligned();
extern bool rightBridgeAligned();
extern void checkCliffs(MotorWheel motorWheel);
extern bool alignBridgeQRDS(MotorWheel motorWheel);
extern bool alignCliffQRDS(MotorWheel motorWheel);

#endif