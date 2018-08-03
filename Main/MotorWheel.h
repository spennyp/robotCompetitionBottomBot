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
		void turnLeft(int angle, int speed = 0, bool backup = true);
		void turnOne(int angle, int speed);
		void turnRight(int angle,  int speed = 0, bool backup = true);
		void forward(int speed = 0);
		void reverse(int speed = 0);
		void stop();
		bool runWithPID;
		void poll(int speed = 0);
};

#endif

