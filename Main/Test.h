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
extern void testServo();
extern void testPIDQRD();
extern void testCliffQRD();
extern void testTurning();


#endif