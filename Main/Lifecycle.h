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
void bottomBotAlignmentCheck();
void codeRed();


#endif
