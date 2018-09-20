// Test.h

#ifndef _TEST_h
#define _TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Diagnostics

extern void systemDiagnostics();


// Sensor Test

extern void sensorTest();
extern void testPIDQRD();
extern void testCliffQRD();
extern void testBridgeQRD();
extern void testCommunicationOut();
extern void testBridgeTouch();


// System Test

extern void systemTest();
extern void testCliffAlign();
extern void testBridge();
extern void testBridgeQRDFollow();
extern void testBridgeTouchSensorAlign();
extern void testTurning();


#endif