// PID.cpp

#include "PID.h"
enum class PIDState
{
	FAR_LEFT = -5,
	LEFT = -1,
	STRAIGHT = 0,
	RIGHT = 1,
	FAR_RIGHT = 5
};

PID::PID(MenuItem pGain, MenuItem dGain, MenuItem iGain, MenuItem PIDThreshold)
{
	threshold = PIDThreshold.Value;
	p = pGain.Value;
	d = dGain.Value;
}

PIDState PID::getState()
{
	//Potentially different Analog read positions
	int lSensor = analogRead(0);
	int rSensor = analogRead(1);
	if (lSensor >= threshold && rSensor >= threshold) {
		state = PIDState::STRAIGHT;
	}
	else if (lSensor < threshold && rSensor >= threshold) {
		state = PIDState::LEFT;
	}
	else if (lSensor >= threshold && rSensor < threshold) {
		state = PIDState::RIGHT;
	}
	else if (lastState == PIDState::LEFT || lastState == PIDState::RIGHT) {
		state = lastState == PIDState::LEFT ? PIDState::FAR_LEFT
			: PIDState::FAR_RIGHT;
	}
	else {
		state = lastState;
	}
	return state;
}

uint16_t PID::getError(PIDState state)
{
	uint16_t pErr = 0, dErr = 0;
	int16_t err = 0;
	pErr = p * ((int)state);
	dErr = d * ((int)state);
	err = pErr + dErr;
	return err;
}

