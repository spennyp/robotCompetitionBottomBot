// Lifecycle.h

#ifndef _LIFECYCLE_h
#define _LIFECYCLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern void run();
void runBottomBot();
void runTopBot(int numberOfTeddiesGrabbed);
void switchToTopBot();
void switchToTopBot();
void deployFirstBridge();
void deployFirstBridge();
void deploySecondBridge();
void activateDumper();
void codeRed();

#endif
