// PID.h

#ifndef _PID_h
#define _PID_h
#include "MenuItem.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PID {
 public:
 	enum PIDState { 
		FAR_LEFT = -5,
  		LEFT = -1,
  		STRAIGHT = 0,
  		RIGHT = 1,
  		FAR_RIGHT = 5
	};
	PID(MenuItem pGain, MenuItem dGain, MenuItem iGain, MenuItem PIDThreshold);
	uint16_t getError();
private:
	uint16_t threshold, i, p, d;
	PID::PIDState state, lastState;
	PID::PIDState getState();
};

#endif

