// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MotorWheel
{
private:
	uint16_t motorSpeed;
	PID pid;

 public:
	MotorWheel(MenuItem speed, PID pid);
	void turn(Direction dir);
	void forward();
	void runWithPID();
	void stop();
};

#endif

