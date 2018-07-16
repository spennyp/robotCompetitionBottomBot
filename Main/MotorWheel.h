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
	MotorWheel(MenuItem speed, PID pid);
	void turnLeft();
	void turnRight();
	void forward();
	void reverse();
	void stop();
	bool runWithPID;
	void switchToTopBot();
	void poll();
};

#endif

