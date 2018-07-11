// Globals.cpp

#include "Globals.h"

static int motorContolPin = 0;
static int servoControlPin1 = 1;
static int servoControlPin2 = 2;
static int leftMotor = 0;
static int rightMotor = 1;
static int servoMotor1 = 0;
static int servoMotor2 = 1;
static DigitalState digitalOn = on;
static DigitalState digitalOff = off;

DigitalPinAndValue::DigitalPinAndValue(int pinNum, DigitalState _state) {
    pinNumber = pinNum;
    state = _state;
};
DigitalPinAndValue::DigitalPinAndValue() {};

MotorOutput::MotorOutput(int motorNum, DigitalState state) {
    motorNumber = motorNum;
    DigitalPinAndValue pinAndVal(motorContolPin, state);
    digitalControl = pinAndVal;
};
MotorOutput::MotorOutput() {};

ServoOutput::ServoOutput(int servoPinNum, DigitalState digitalState1, DigitalState digitalState2) {
    servoPinNumber = servoPinNum;
    DigitalPinAndValue pinAndVal1(servoControlPin1, digitalState1);
    DigitalPinAndValue pinAndVal2(servoControlPin2, digitalState2);
    digitalControl1 = pinAndVal1;
    digitalControl2 = pinAndVal2;
}
ServoOutput::ServoOutput() {};

struct MotorOutput topLeftMotor(leftMotor, digitalOn);
struct MotorOutput topRightMotor(rightMotor, digitalOn);
struct MotorOutput bottomLeftMotor(leftMotor, digitalOff);
struct MotorOutput bottomRightMotor(rightMotor, digitalOff);

struct ServoOutput clawGrabServo(servoMotor1, digitalOff, digitalOn);
struct ServoOutput clawDumpServo(servoMotor2, digitalOff, digitalOff);
struct ServoOutput storageDumpServoLeft(servoMotor1, digitalOn, digitalOff);
struct ServoOutput storageDumpServoRight(servoMotor2, digitalOff, digitalOn);
struct ServoOutput topBridgeUpperServo(servoMotor1, digitalOff, digitalOff);
struct ServoOutput topBridgeLowerServo(servoMotor2, digitalOn, digitalOn);
struct ServoOutput bottomBridgeUppserServo(servoMotor1, digitalOn, digitalOn);
struct ServoOutput bottomBridgeLowerServo(servoMotor2, digitalOn, digitalOff);

// Analog pins
int topFarTapeFollowQRD = 0;
int topNearTapeFollowQRD = 1;
int topCliffQRD = 2;
int bottomFarTapeFollowQRD = 3;
int bottomNearTapeFollowQRD = 4;
int bottomCliffQRD = 5;


