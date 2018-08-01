// Globals.h

#ifndef _GLOBALS_h
#define _GLOBALS_h
#include <motor.h>
#include <TINAH_Servo.h>
#include <TINAH_BufferedLCD.h>
#include <phys253.h>
#include "Menu.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// Helpers
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
extern int leftMotor;
extern int rightMotor;
extern int winchMotor;


// Servos
class ServoOutput {
    public:
        ServoOutput(TINAH::Servo servo, DigitalState digitalState1, DigitalState digitalState2);
        ServoOutput();
        TINAH::Servo servo;
        DigitalPinAndValue digitalControl1;
        DigitalPinAndValue digitalControl2;
        int lastAngle;
};
void setServo(ServoOutput servoInfo, int angle, bool sweep = false);
extern ServoOutput leftStorageDumpServo;
extern ServoOutput rightStorageDumpServo;
extern ServoOutput rightBridgeServo;
extern ServoOutput leftBridgeServo;
extern ServoOutput clawDumpServo;
extern ServoOutput clawGrabServo;
extern ServoOutput ejectServo;
extern ServoOutput bottomBridgeServo;


// Digital pins
extern int topHall;
extern int bottomHall;
extern int frontTouchSensor;


// Analog pins
extern int farTapeFollowQRD;
extern int nearTapeFollowQRD;
extern int cliffQRD;
extern int clawIR;

#endif