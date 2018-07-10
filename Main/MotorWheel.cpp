// Motor.cpp

#include "MotorWheel.h"
#include <ServoTINAH.h>
#include <phys253pins.h>
#include <phys253.h>
#include <motor.h>

enum class Direction
{
	LEFT,
	RIGHT
};

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid)
{
	motorSpeed = speed.Value;
}

//Assumes motor 0 is the left wheel and motor 1 is the right wheel
void MotorWheel::turn(Direction dir)
{
	switch (dir)
	{
	case Direction::LEFT:
		motor.speed(0, -motorSpeed);
		motor.speed(1, motorSpeed);
		break;
	case Direction::RIGHT:
		motor.speed(0, motorSpeed);
		motor.speed(1, -motorSpeed);
		break;
	default:
		break;
	}
}

void MotorWheel::forward()
{
	motor.speed(0, motorSpeed);
	motor.speed(1, motorSpeed);
}

void MotorWheel::runWithPID()
{
	int err = pid.getError();
	motor.speed(0, motorSpeed - err);
	motor.speed(1, motorSpeed);
}

void MotorWheel::stop()
{
	//motor.stop_all();
	motor.stop(0);
	motor.stop(1);
}