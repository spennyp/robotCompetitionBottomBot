// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

const int defaultTurnSpeed = 200;

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid)
{
	motorSpeed = speed.value;
	runWithPID = true;
}

// Default parameter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnLeft(int angle, int speed, bool backup) {
	runWithPID = false;
	int turnSpeed = (speed == 0) ? defaultTurnSpeed : speed;
	motor.speed(leftMotor, -turnSpeed);
	if (backup) {
		motor.speed(rightMotor, -turnSpeed);
		delay(200);
	}
	motor.speed(rightMotor, turnSpeed);
	delay(angle * delayPerDegreeTurn.value);
	stop();
}

// Default parameter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnRight(int angle, int speed, bool backup) {
	runWithPID = false;
	int turnSpeed = (speed == 0) ? defaultTurnSpeed : speed;
	motor.speed(rightMotor, -turnSpeed);
	if (backup)
	{
		motor.speed(leftMotor, -turnSpeed);
		delay(200);
	}
	motor.speed(leftMotor, turnSpeed);
	delay(angle * delayPerDegreeTurn.value);
	stop();
}

// Default perapeter of 0, which runs motorSpeed from the menu
void MotorWheel::forward(int speed)
{
	runWithPID = false;
	int forwardSpeed = (speed == 0) ? motorSpeed : speed;

	motor.speed(leftMotor, forwardSpeed);
	motor.speed(rightMotor, forwardSpeed);
}

void MotorWheel::reverse(int speed)
{
	runWithPID = false;
	if (speed == 0)
	{
		motor.speed(leftMotor, -motorSpeed);
		motor.speed(rightMotor, -motorSpeed);
	}
	else
	{
		motor.speed(leftMotor, -speed);
		motor.speed(rightMotor, -speed);
	}
}

void MotorWheel::stop() {
	runWithPID = false;
	motor.speed(leftMotor, 0);
	motor.speed(rightMotor, 0);
}

// Lifecycle

void MotorWheel::poll(int speed)
{
	if (runWithPID)
	{
		int err = pid.getError();
		// when err < 0 turns right. when err > 0 turns left
		if (!speed)
		{
			motor.speed(leftMotor, motorSpeed - err);
			motor.speed(rightMotor, motorSpeed + err);
		}
		else
		{
			motor.speed(leftMotor, speed - err);
			motor.speed(rightMotor, speed + err);
		}
	}
}
