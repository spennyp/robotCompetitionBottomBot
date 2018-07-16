// Globals.cpp

#include "Globals.h"
#include <TINAH_Pins.h>

const int motorContolPin = 0;
const int leftMotor = 0;
const int rightMotor = 1;
const DigitalState digitalOn = on;
const DigitalState digitalOff = off;
const int servoControlPin1 = 1;
const int servoControlPin2 = 2;
const int sonalClearDuration = 2; // [micro s]
const int sonarPulseDuration = 10; // [micro s]
const int speedOfSound = 0.34; // [mm / (micro s)]


// Motors
MotorOutput::MotorOutput(int motorNum, DigitalState state) {
    motorNumber = motorNum;
    DigitalPinAndValue pinAndVal(motorContolPin, state);
    digitalControl = pinAndVal;
};
MotorOutput::MotorOutput() {};

struct MotorOutput topLeftMotor(leftMotor, digitalOn);
struct MotorOutput topRightMotor(rightMotor, digitalOn);
struct MotorOutput bottomLeftMotor(leftMotor, digitalOff);
struct MotorOutput bottomRightMotor(rightMotor, digitalOff);
int winchMotor = 2;


// Servos
TINAH::Servo servo0(TINAH::pins::servo[0]);
TINAH::Servo servo1(TINAH::pins::servo[1]);
TINAH::Servo servo2(TINAH::pins::servo[2]);

ServoOutput::ServoOutput(TINAH::Servo _servo, DigitalState digitalState1, DigitalState digitalState2) {
    servo = _servo;
    DigitalPinAndValue pinAndVal1(servoControlPin1, digitalState1);
    DigitalPinAndValue pinAndVal2(servoControlPin2, digitalState2);
    digitalControl1 = pinAndVal1;
    digitalControl2 = pinAndVal2;
}
ServoOutput::ServoOutput() {};

void setServo(ServoOutput servoInfo, int angle) {
    digitalWrite(servoInfo.digitalControl1.pinNumber, servoInfo.digitalControl1.state);
    digitalWrite(servoInfo.digitalControl2.pinNumber, servoInfo.digitalControl2.state);
    servoInfo.servo.write(angle);
}

struct ServoOutput clawGrabServo(servo0, digitalOff, digitalOn);
struct ServoOutput clawDumpServo(servo1, digitalOff, digitalOff);
struct ServoOutput storageDumpServoLeft(servo0, digitalOn, digitalOff);
struct ServoOutput storageDumpServoRight(servo1, digitalOff, digitalOn);
struct ServoOutput topBridgeUpperServo(servo0, digitalOff, digitalOff);
struct ServoOutput topBridgeLowerServo(servo1, digitalOn, digitalOn);
struct ServoOutput bottomBridgeUppserServo(servo0, digitalOn, digitalOn);
struct ServoOutput bottomBridgeLowerServo(servo1, digitalOn, digitalOff);


// Limit Switches, digital pins
int topLimitSwitch = 9;
int middleLimitSwitch = 10;
int bottomLimitSwitch = 11;
ClawHomePosition startingHomePosition = bottom;


// Sensors, analog Pins
int topFarTapeFollowQRD = 0;
int topNearTapeFollowQRD = 1;
int topCliffQRD = 2;
int bottomFarTapeFollowQRD = 3;
int bottomNearTapeFollowQRD = 4;
int bottomCliffQRD = 5;


// Claw IR, digital pin
int clawIR = 12;


// Helpers
DigitalPinAndValue::DigitalPinAndValue(int pinNum, DigitalState _state) {
    pinNumber = pinNum;
    state = _state;
};
DigitalPinAndValue::DigitalPinAndValue() {};
















