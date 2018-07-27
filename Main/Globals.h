// Globals.h

#ifndef _GLOBALS_h
#define _GLOBALS_h
#include <motor.h>
#include <TINAH_Servo.h>
#include <TINAH_BufferedLCD.h>
#include <phys253.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// Helpers
enum ClawHomePosition { top, bottom };
enum DigitalState { on = HIGH, off = LOW };
struct DigitalPinAndValue {
    DigitalPinAndValue(int pinNum, DigitalState _state);
    DigitalPinAndValue();
    int pinNumber;
    DigitalState state;
};


// LCD
extern TINAH::BufferedLCD LCD;


// Motors
extern motorClass motor;
struct MotorOutput {
    MotorOutput(int motorNum, DigitalState value);
    MotorOutput();
    int motorNumber;
    DigitalPinAndValue digitalControl;
};
extern MotorOutput topLeftMotor;
extern MotorOutput topRightMotor;
extern MotorOutput bottomLeftMotor;
extern MotorOutput bottomRightMotor;
extern int winchMotor;


// Servos
struct ServoOutput {
    ServoOutput(TINAH::Servo servo, DigitalState digitalState1, DigitalState digitalState2);
    ServoOutput();
    TINAH::Servo servo;
    DigitalPinAndValue digitalControl1;
    DigitalPinAndValue digitalControl2;
};
void setServo(ServoOutput servoInfo, int angle);
extern ServoOutput clawGrabServo;
extern ServoOutput clawDumpServo;
extern ServoOutput storageDumpServoLeft;
extern ServoOutput storageDumpServoRight;
extern ServoOutput topBridgeRightServo;
extern ServoOutput topBridgeLeftServo;
extern ServoOutput bottomBridgeServoA;
extern ServoOutput topBridgeLowServo;

// QRD's, analog pins
extern int topNearTapeFollowQRD;
extern int topFarTapeFollowQRD;
extern int topCliffQRD;
extern int bottomCliffQRD;
extern int bottomFarTapeFollowQRD;
extern int bottomNearTapeFollowQRD;


// Digital pins
extern int codeRedSwitch;
extern int topHall;
extern int middleHall;
extern int bottomHall;
extern int clawIR;
extern int leftPlankQRD; // through comparator
extern int rightPlankQRD; // through comparator
extern int topBotFrontTouchSensor;

extern ClawHomePosition startingHomePosition;

#endif