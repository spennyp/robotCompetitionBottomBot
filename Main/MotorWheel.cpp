// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

const int delayPerDegreeTurnTopBot = 7; // For top bot
const int delayPerDegreeTurnBottomBot = 28;

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid) {
	motorSpeed = speed.value;
	runWithPID = true;
	topBot = false;
}

// Top/bottom is arbitrary in below function calls due to shared pins

void MotorWheel::turnLeft(int turnAngle, bool backup) {
	runWithPID = false;
	motor.speed(topLeftMotor.motorNumber, -150);
	if(backup) {
		motor.speed(topRightMotor.motorNumber, -150);
		delay(400);
	}
	motor.speed(topRightMotor.motorNumber, 150);
	if(topBot) {
		delay(turnAngle * delayPerDegreeTurnTopBot);
	} else {
		delay(turnAngle * delayPerDegreeTurnBottomBot);
	}
	stop();
}

void MotorWheel::turnRight(int turnAngle, bool backup) {
	runWithPID = false;
	motor.speed(topRightMotor.motorNumber, -150);
	if(backup) {
		motor.speed(topLeftMotor.motorNumber, -150);
		delay(400);
	}
	motor.speed(topLeftMotor.motorNumber, 150);
	if(topBot) {
		delay(turnAngle * delayPerDegreeTurnTopBot);
	} else {
		delay(turnAngle * delayPerDegreeTurnBottomBot);
	}
	stop();
}

void MotorWheel::forward() {
	runWithPID = false;
	motor.speed(topLeftMotor.motorNumber, motorSpeed);
	motor.speed(topRightMotor.motorNumber, motorSpeed);
}

void MotorWheel::reverse() {
	runWithPID = false;
	motor.speed(topLeftMotor.motorNumber, -motorSpeed);
	motor.speed(topRightMotor.motorNumber, -motorSpeed);
}

void MotorWheel::stop() {
	runWithPID = false;
	motor.stop_all();
}


// Lifecycle

void MotorWheel::poll() {
	if(runWithPID) {
		int err;
		if(topBot) {
			err = pid.getTopError();
		} else {
			err = pid.getBottomError();
		}
		// when err < 0 turns right. when err > 0 turns left
		motor.speed(topLeftMotor.motorNumber, motorSpeed - err);
		motor.speed(topRightMotor.motorNumber, motorSpeed + err);
	} 
}

void MotorWheel::switchToTopBot() {
	digitalWrite(topLeftMotor.digitalControl.pinNumber, HIGH);
	topBot = true;
}

// add dynamic speed changing?
// ie. if motor is consistently moving straight increase motor power
// if the motor is oscillating between (far) left and (far) right decrease motor power

