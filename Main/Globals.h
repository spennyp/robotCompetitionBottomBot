// Globals.h

#ifndef _GLOBALS_h
#define _GLOBALS_h
#include <motor.h>
#include <TINAH_Servo.h>
#include <TINAH_BufferedLCD.h>
#include <phys253.h>
#include <TINAH_Pins.h>
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



// Servos
extern TINAH::Servo bottomServo;

// Digital pins
extern int communicationOut;
extern int communicationIn;


// Analog pins
extern int farTapeFollowQRD;
extern int nearTapeFollowQRD;
extern int cliffQRD;
extern int rightBridgeQRD;
extern int leftBridgeQRD;

#endif