// PID.h

#ifndef _PID_h
#define _PID_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PID
{
private:
	uint16_t threshold, i, p, d;
	PIDState state, lastState;
	PIDState getState();
 public:
	PID(MenuItem pGain, MenuItem dGain, MenuItem iGain, MenuItem PIDThreshold);
	uint16_t getError(PIDState state);
};

#endif

