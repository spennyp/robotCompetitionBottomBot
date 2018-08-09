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
extern int bridgeLeftServoResetPosition;

// Deploy constants
extern int bridgeLeftServoDeployPosition;

// Sensors
extern bool clawTriggered();
extern bool foundRightCliff();
extern bool foundLeftCliff();
extern bool leftBridgeTouchTriggered();
extern bool rightBridgeTouchTriggered();
extern bool rampTopFound();


// Core Functionality

extern void deployBridge();
extern void resetBridge();


// RunHelpers

extern void checkForEwok();
extern bool atTopOfRamp();
extern bool hitFirstEdge();
extern void makeFirstLeftTurn();
extern void alignForBridgeDrop();
extern void alignCliffQRDs();
extern bool followBridgeQRDs(int forwardSpeed);
extern bool triggeredBridgeTouch();
extern bool alignTouchSensors();
extern void detatchTopBot();


// Setup

extern void setupRobot();


// Reset

extern void reset();
extern void softReset();

#endif