// PID.cpp

#include "PID.h"
#include "Globals.h"

const int8_t FAR_LEFT = -5, LEFT = -1, STRAIGHT = 0, RIGHT = 1, FAR_RIGHT = 5;

PID::PID(MenuItem pGain, MenuItem dGain, MenuItem iGain, MenuItem PIDThreshold) {
	threshold = PIDThreshold.Value;
	p = pGain.Value;
	d = dGain.Value;
}

int8_t PID::getState() {
	//Potentially different Analog read positions
	lastState = state;
	int lSensor = analogRead(topNearTapeFollowQRD);
	int rSensor = analogRead(topFarTapeFollowQRD);
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

int16_t PID::getError() {
	int16_t pErr = 0, dErr = 0;
	int16_t err = 0;
	int8_t state = getState();
	pErr = p * (state);
	dErr = d * (state - lastState);
	err = pErr + dErr;
	return err;
}

