// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

const int defaultTurnSpeed = 150;

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid)
{
	motorSpeed = speed.value;
	runWithPID = true;
}

// Default parameter of 0, which runs at defualtTurnSpeed
// Default parameter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnLeft(int angle, int speed, bool backup)
{
	runWithPID = false;
	int turnSpeed = (speed == 0) ? defaultTurnSpeed : speed;
	motor.speed(leftMotor, -turnSpeed);
	if (backup)
	{
		motor.speed(rightMotor, -turnSpeed);
		delay(400);
	}
	motor.speed(rightMotor, turnSpeed);
	delay(angle * delayPerDegreeTurn.value);
	stop();
}

// Default parameter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnRight(int angle, int speed, bool backup)
{
	runWithPID = false;
	int turnSpeed = (speed == 0) ? defaultTurnSpeed : speed;
	motor.speed(rightMotor, -turnSpeed);
	if (backup)
	{
		motor.speed(leftMotor, -turnSpeed);
		delay(400);
	}
	motor.speed(leftMotor, turnSpeed);
	delay(angle * delayPerDegreeTurn.value);
	stop();
}

// Default perapeter of 0, which runs motorSpeed from the menu
void MotorWheel::forward(int speed)
{
	runWithPID = false;
	if (speed == 0)
	{
		motor.speed(leftMotor, motorSpeed);
		motor.speed(rightMotor, motorSpeed);
	}
	else
	{
		motor.speed(leftMotor, speed);
		motor.speed(rightMotor, speed);
	}
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

void MotorWheel::stop()
{
	runWithPID = false;
	motor.stop_all();
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
