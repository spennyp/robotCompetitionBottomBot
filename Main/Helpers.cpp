// Helpers.cpp

#include "Helpers.h"
#include "Globals.h"

// Delays
extern int bridgeDropDelay = 2000;

extern int bridgeServoResetPosition = 0;

// Deploy constants
extern int bridgeServoDeployPosition = 90;

int cliffCount = 0;
bool bridgeQRDSAligned = false;


// Sensors

bool clawTriggered() {
    return (digitalRead(communicationIn) == LOW);
}

bool foundRightCliff() {
    return (analogRead(rightCliffQRD) > cliffThreshold.value);
}

bool foundLeftCliff() {
	return (analogRead(leftCliffQRD) > cliffThreshold.value);
}

void resetBridge() {
    bottomServo.write(bridgeServoResetPosition);
}

bool leftBridgeQRDAligned() {
    return (analogRead(leftBridgeQRD) < alignmentThreshold.value);
}

bool rightBridgeQRDAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value);
}

bool leftBridgeTouchTriggered() {
	return (digitalRead(leftBridgeTouch) == LOW);
}

bool rightBridgeTouchTriggered() {
	return (digitalRead(rightBridgeTouch) == LOW);
}


// Run helpers

void deployBridge() {
	bottomServo.write(bridgeServoDeployPosition);
	delay(2000); // Wait for bridge to deploy
	digitalWrite(communicationOut, HIGH); // Tells top bot to lower the claw again
	delay(2000); // Wait for claw to lower
}

bool followBridgeQRDs(MotorWheel motorWheel) {
	bool isLeftBridgeAligned = leftBridgeQRDAligned();
	bool isRightBridgeAligned = rightBridgeQRDAligned();
	if(isLeftBridgeAligned && !isRightBridgeAligned) {
		motor.speed(leftMotor, 60);
		motor.speed(rightMotor, 100);
	} else if(!isLeftBridgeAligned && isRightBridgeAligned) {
		motor.speed(leftMotor, 100);
		motor.speed(rightMotor, 60);
	} else {
		motorWheel.forward(80);
	}
}

bool alignCliffQRDs(MotorWheel motorWheel) {
	bool leftCliff = foundLeftCliff();
	bool rightCliff = foundRightCliff();
	if(leftCliff && rightCliff) {
		motorWheel.stop();
		return true;
	} else if(leftCliff && !rightCliff) {
		motor.speed(leftMotor, -100);
		motor.speed(rightMotor, 100);
	} else if(!leftCliff && rightCliff) {
		motor.speed(leftMotor, 100);
		motor.speed(rightMotor, -100);
	} else {
		motorWheel.forward(100);
	}
	return false;
}

bool alignTouchSensors(MotorWheel motorWheel) {
	bool left = leftBridgeTouchTriggered();
	bool right = rightBridgeTouchTriggered();
	if(left && right) {
		motorWheel.stop();
		return true;
	} else if(left && !right) {
		motor.speed(leftMotor, -75);
		motor.speed(rightMotor, 75);
	} else if(!left && right) {
		motor.speed(leftMotor, 75);
		motor.speed(rightMotor, -75);
	} else {
		motorWheel.forward(80);
	}
	return false;
}


void detatchTopBot() {
	digitalWrite(communicationOut, LOW);
}