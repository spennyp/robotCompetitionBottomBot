// PID.cpp

#include "PID.h"
#include "Globals.h"

const int8_t FAR_LEFT = -5, LEFT = -1, STRAIGHT = 0, RIGHT = 1, FAR_RIGHT = 5;

PID::PID(MenuItem pGain, MenuItem dGain, MenuItem iGain, MenuItem PIDThreshold) {
	threshold = PIDThreshold.value;
	p = pGain.value;
	d = dGain.value;
}

// For folling tape, not used for now
int8_t PID::getTapeState() {
	lastState = state;
	int lSensor = analogRead(topNearTapeFollowQRD);
	int rSensor = analogRead(topFarTapeFollowQRD);
	if (lSensor >= threshold && rSensor >= threshold) {
		state = STRAIGHT;
	} else if (lSensor < threshold && rSensor >= threshold) {
		state = LEFT;
	} else if (lSensor >= threshold && rSensor < threshold) {
		state = RIGHT;
	} else if (lastState == LEFT || lastState == RIGHT) {
		state = lastState == LEFT ? FAR_LEFT : FAR_RIGHT;
	} else {
		state = lastState;
	}
	return state;
}

int8_t PID::getEdgeState(bool topBot) {
	lastState = state;
	int nearSensor;
	int farSensor;
	if(topBot) {
		nearSensor = analogRead(topNearTapeFollowQRD);
		farSensor = analogRead(topFarTapeFollowQRD);
	} else {
		nearSensor = analogRead(bottomNearTapeFollowQRD);
		farSensor = analogRead(bottomFarTapeFollowQRD);
	}
	if(nearSensor <= threshold && farSensor >= threshold) {
		state = STRAIGHT;
	} else if(nearSensor < threshold && farSensor <= threshold) {
		state = LEFT;
	} else if(nearSensor >= threshold && farSensor > threshold) {
		state = RIGHT;
	} else {
		state = lastState;
	}
	return state;
}

int16_t PID::getTopError() {
	int16_t pErr = 0, dErr = 0;
	int16_t err = 0;
	int8_t state = getEdgeState(true);
	pErr = p * (state);
	dErr = d * (state - lastState);
	err = pErr + dErr;
	return err;
}

int16_t PID::getBottomError() {
	int16_t pErr = 0, dErr = 0;
	int16_t err = 0;
	int8_t state = getEdgeState(false);
	pErr = p * (state);
	dErr = d * (state - lastState);
	err = pErr + dErr;
	return err;
}



