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

enum DigitalState { on, off };
struct DigitalPinAndValue {
    DigitalPinAndValue(int pinNum, DigitalState _state);
    DigitalPinAndValue();
    int pinNumber;
    DigitalState state;
};
struct MotorOutput {
    MotorOutput(int motorNum, DigitalState value);
    MotorOutput();
    int motorNumber;
    DigitalPinAndValue digitalControl;
};
struct ServoOutput {
    ServoOutput(int servoPinNum, DigitalState digitalState1, DigitalState digitalState2);
    ServoOutput();
    int servoPinNumber;
    DigitalPinAndValue digitalControl1;
    DigitalPinAndValue digitalControl2;
};

extern MotorOutput topLeftMotor;
extern MotorOutput topRightMotor;
extern MotorOutput bottomLeftMotor;
extern MotorOutput bottomRightMotor;

extern ServoOutput clawGrabServo;
extern ServoOutput clawDumpServo;
extern ServoOutput storageDumpServoLeft;
extern ServoOutput storageDumpServoRight;
extern ServoOutput topBridgeUpperServo;
extern ServoOutput topBridgeLowerServo;
extern ServoOutput bottomBridgeUppserServo;
extern ServoOutput bottomBridgeLowerServo;

extern int topNearTapeFollowQRD;
extern int topFarTapeFollowQRD;
extern int topCliffQRD;
extern int bottomCliffQRD;
extern int bottomFarTapeFollowQRD;
extern int bottomNearTapeFollowQRD;

#endif