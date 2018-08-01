// Globals.cpp

#include "Globals.h"
#include <TINAH_Pins.h>


// Constants
const DigitalState digitalOn = on;
const DigitalState digitalOff = off;
const int servoControlPin1 = 1;
const int servoControlPin2 = 2;


// Motors
int leftMotor = 0;
int rightMotor = 1;


// Servos
TINAH::Servo servo0(TINAH::pins::servo[0]);

int bottomServo = 0;

// Digital pins
int stopPin = 8;
int detachPin = 7;

// Analog Pins
int farTapeFollowQRD = 2;
int nearTapeFollowQRD = 1;
int rightcliffQRD = 0;
int rightBridgeQRD = 4;
int leftBridgeQRD = 3;
int leftCliffQRD = 5;

// Helpers
DigitalPinAndValue::DigitalPinAndValue(int pinNum, DigitalState _state) {
    pinNumber = pinNum;
    state = _state;
};
DigitalPinAndValue::DigitalPinAndValue() {};



















