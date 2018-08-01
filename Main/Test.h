// Test.h

#ifndef _TEST_h
#define _TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern void systemDiagnostics();
extern void testFullSystem();

extern void testDump();
extern void testClaw();
extern void testTouch();
extern void testPid();
extern void testBridge();

#endif