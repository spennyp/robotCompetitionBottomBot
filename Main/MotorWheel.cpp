// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid) {
	motorSpeed = speed.Value;
}

//Assumes motor 0 is the left wheel and motor 1 is the right wheel
//Top / bottom is arbitrary in below function calls due to shared pins

void MotorWheel::turnLeft() {
	motor.speed(topLeftMotor.motorNumber, -motorSpeed);
	motor.speed(topRightMotor.motorNumber, motorSpeed);
}

void MotorWheel::turnRight() {
	motor.speed(topLeftMotor.motorNumber, motorSpeed);
	motor.speed(topRightMotor.motorNumber, -motorSpeed);
}

void MotorWheel::forward() {
	motor.speed(topLeftMotor.motorNumber, motorSpeed);
	motor.speed(topRightMotor.motorNumber, motorSpeed);
}

void MotorWheel::reverse() {
	motor.speed(topLeftMotor.motorNumber, -motorSpeed);
	motor.speed(topRightMotor.motorNumber, -motorSpeed);
}

void MotorWheel::runWithPID() {
	int err = pid.getError();
	// when err < 0 turns right. when err > 0 turns left
	motor.speed(topLeftMotor.motorNumber, motorSpeed - err);
	motor.speed(topRightMotor.motorNumber, motorSpeed + err);

	// add dynamic speed changing?
	// ie. if motor is consistently moving straight increase motor power
	// if the motor is oscillating between (far) left and (far) right decrease motor power
}

void MotorWheel::stop() {
	//motor.stop_all();
	motor.stop(0);
	motor.stop(1);
}

void MotorWheel::switchToTopMotors() {
	digitalWrite(topLeftMotor.digitalControl.pin, HIGH);
}

