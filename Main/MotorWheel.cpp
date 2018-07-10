// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid) {
	motorSpeed = speed.Value;
}

//Assumes motor 0 is the left wheel and motor 1 is the right wheel
void MotorWheel::turn(Direction dir) {
	switch (dir) {
	case LEFT:
		motor.speed(0, -motorSpeed);
		motor.speed(1, motorSpeed);
		break;
	case RIGHT:
		motor.speed(0, motorSpeed);
		motor.speed(1, -motorSpeed);
		break;
	default:
		break;
	}
}

void MotorWheel::forward() {
	motor.speed(0, motorSpeed);
	motor.speed(1, motorSpeed);
}

void MotorWheel::runWithPID() {
	int err = pid.getError();
	motor.speed(0, motorSpeed - err);
	motor.speed(1, motorSpeed);
}

void MotorWheel::stop() {
	//motor.stop_all();
	motor.stop(0);
	motor.stop(1);
}
