// PID.cpp

#include "PID.h"

PID::PID(MenuItem pGain, MenuItem dGain, MenuItem iGain, MenuItem PIDThreshold) {
	threshold = PIDThreshold.Value;
	p = pGain.Value;
	d = dGain.Value;
}

PID::PIDState PID::getState() {
	//Potentially different Analog read positions
	int lSensor = analogRead(0);
	int rSensor = analogRead(1);
	if (lSensor >= threshold && rSensor >= threshold) {
		state = STRAIGHT;
	}
	else if (lSensor < threshold && rSensor >= threshold) {
		state = LEFT;
	}
	else if (lSensor >= threshold && rSensor < threshold) {
		state = RIGHT;
	}
	else if (lastState == LEFT || lastState == RIGHT) {
		state = lastState == LEFT ? FAR_LEFT : FAR_RIGHT;
	}
	else {
		state = lastState;
	}
	return state;
}

uint16_t PID::getError() {
	uint16_t pErr = 0, dErr = 0;
	int16_t err = 0;
	PIDState state = getState();
	pErr = p * ((int)state);
	dErr = d * ((int)state);
	err = pErr + dErr;
	return err;
}

