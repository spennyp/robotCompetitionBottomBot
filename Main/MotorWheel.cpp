// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid) {
	motorSpeed = speed.Value;
	runWithPID = true;
}

// Top/bottom is arbitrary in below function calls due to shared pins

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

void MotorWheel::stop() {
	motor.stop_all();
	// motor.stop(topLeftMotor.motorNumber);
	// motor.stop(topRightMotor.motorNumber);
}


// Lifecycle

void MotorWheel::poll() {
	if(runWithPID) {
		int err = pid.getError();
		// when err < 0 turns right. when err > 0 turns left
		motor.speed(topLeftMotor.motorNumber, motorSpeed - err);
		motor.speed(topRightMotor.motorNumber, motorSpeed + err);

		// add dynamic speed changing?
		// ie. if motor is consistently moving straight increase motor power
		// if the motor is oscillating between (far) left and (far) right decrease motor power
	}
}

void MotorWheel::switchToTopBot() {
	digitalWrite(topLeftMotor.digitalControl.pinNumber, HIGH);
}

