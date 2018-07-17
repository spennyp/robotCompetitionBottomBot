// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

// TODO: Calibrate this number, take into account motor speed
const int loopsPerAngleTurn = 10;

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid) {
	motorSpeed = speed.Value;
	runWithPID = true;
	hardCodeTurning = false;
	numberOfLoopsForTurn = 0;
	turnLoopCount = 0;
}

// Top/bottom is arbitrary in below function calls due to shared pins

void MotorWheel::turnLeft(int turnAngle) {
	hardCodeTurning = true;
	motor.speed(topLeftMotor.motorNumber, -motorSpeed);
	motor.speed(topRightMotor.motorNumber, motorSpeed);
	numberOfLoopsForTurn = turnAngle * loopsPerAngleTurn;
}

void MotorWheel::turnRight(int turnAngle) {
	hardCodeTurning = true;
	motor.speed(topLeftMotor.motorNumber, motorSpeed);
	motor.speed(topRightMotor.motorNumber, -motorSpeed);
	numberOfLoopsForTurn = turnAngle * loopsPerAngleTurn;
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
	motor.stop_all();
}


// Lifecycle

int MotorWheel::poll() {
	if(hardCodeTurning) {
		turnLoopCount ++;
		if(turnLoopCount == numberOfLoopsForTurn) {
			hardCodeTurning = false;
			if(!runWithPID) {
				stop();
			}
		}
	} else if(runWithPID) {
		int err = pid.getError();
		// when err < 0 turns right. when err > 0 turns left
		motor.speed(topLeftMotor.motorNumber, motorSpeed - err);
		motor.speed(topRightMotor.motorNumber, motorSpeed + err);

		return err;
	} 
}

void MotorWheel::switchToTopBot() {
	digitalWrite(topLeftMotor.digitalControl.pinNumber, HIGH);
}

// add dynamic speed changing?
// ie. if motor is consistently moving straight increase motor power
// if the motor is oscillating between (far) left and (far) right decrease motor power

