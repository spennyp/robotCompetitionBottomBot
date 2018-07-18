// Lifecycle.h

#ifndef _LIFECYCLE_h
#define _LIFECYCLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// API
extern void run();

// Helpers
void reset();
void runBottomBot();
void runTopBot(int numberOfTeddiesGrabbed);
void switchToTopBot();
void deployBottomBridge();
void deployTopBridge();
void activateDumper();
void bottomBotPlankCheck();
void codeRed();

#endif
