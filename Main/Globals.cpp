// Globals.cpp

#include "Globals.h"


// Constants
const DigitalState digitalOn = on;
const DigitalState digitalOff = off;
const int servoControlPin1 = 1;
const int servoControlPin2 = 2;


// Motors
int leftMotor = 0;
int rightMotor = 1;


// Servos
TINAH::Servo bottomLeftServo(TINAH::pins::servo[0]);
TINAH::Servo bottomRightServo(TINAH::pins::servo[1]);

// Digital pins
int communicationOut = 5; // tinah outputs 7 and 6 dont work
int communicationIn = 8;
int leftBridgeTouch = 9;
int rightBridgeTouch = 10;


// Analog Pins
int farTapeFollowQRD = 2;
int nearTapeFollowQRD = 1;
int rightCliffQRD = 5;
int leftCliffQRD = 0;
int rightBridgeQRD = 4;
int leftBridgeQRD = 3;

// Helpers
DigitalPinAndValue::DigitalPinAndValue(int pinNum, DigitalState _state) {
    pinNumber = pinNum;
    state = _state;
};
DigitalPinAndValue::DigitalPinAndValue() {};



















