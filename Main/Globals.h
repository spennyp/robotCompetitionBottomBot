// Globals.h

#ifndef _GLOBALS_h
#define _GLOBALS_h
#include <motor.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern motorClass motor;

enum DigitalValue { ON, OFF };
struct DigitalPinAndValue {
    int pin;
    int value;
};
struct MotorOutput {
    int motorNumber;
    DigitalPinAndValue digitalControl;
};
struct ServoOutput {
    int servoNumber;
    DigitalPinAndValue digitalOut1;
    DigitalPinAndValue digitalOut2;
};

extern MotorOutput topLeftMotor;
extern MotorOutput topRightMotor;
extern MotorOutput bottomLeftMotor;
extern MotorOutput bottomRightMotor;

extern ServoOutput clawGrabServo;
extern ServoOutput clawDumpServo;
extern ServoOutput storageDumpServoLeft;
extern ServoOutput storageDumpServoRight;
extern ServoOutput topBridgeServo;
extern ServoOutput bottomBridgeServo;

extern int topNearTapeFollowQRD;
extern int topFarTapeFollowQRD;
extern int topCliffQRD;
extern int bottomCliffQRD;
extern int bottomFarTapeFollowQRD;
extern int bottomNearTapeFollowQRD;

#endif