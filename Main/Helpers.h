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
extern bool foundRightCliff();
extern bool foundLeftCliff();
extern bool leftBridgeQRDAligned();
extern bool rightBridgeQRDAligned();
extern bool leftBridgeTouchTriggered();
extern bool rightBridgeTouchTriggered();


// RunHelpers
extern bool alignCliffQRDs(MotorWheel motorWheel);
extern void deployBridge();
extern void resetBridge();
extern bool followBridgeQRDs(MotorWheel motorWheel, int forwardSpeed);
extern bool alignTouchSensors(MotorWheel motorWheel);
extern void detatchTopBot();

#endif