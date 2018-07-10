// Motor.h

#ifndef _MOTORWHEEL_h
#define _MOTORWHEEL_h
#include "PID.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MotorWheel {
private:
	uint16_t motorSpeed;
	PID pid;

 public:
	enum Direction { LEFT, RIGHT };
	MotorWheel(MenuItem speed, PID pid);
	void turn(Direction dir);
	void forward();
	void runWithPID();
	void stop();
};

#endif

