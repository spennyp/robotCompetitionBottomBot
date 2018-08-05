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

bool bridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value && analogRead(leftBridgeQRD) < alignmentThreshold.value);
}

bool leftBridgeAligned() {
    return (analogRead(leftBridgeQRD) < alignmentThreshold.value);
}

bool rightBridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value);
}

void detatchTopBot() {
	digitalWrite(communicationOut, LOW);
}


// Run helpers

void deployBridge() {
	bottomServo.write(bridgeServoDeployPosition);
	delay(2000); // Wait for bridge to deploy
	digitalWrite(communicationOut, HIGH); // Tells top bot to lower the claw again
	delay(2000); // Wait for claw to lower
}

bool alignBridgeQRDs(MotorWheel motorWheel) {
	bool isLeftBridgeAligned = leftBridgeAligned();
	bool isRightBridgeAligned = rightBridgeAligned();
	if(isLeftBridgeAligned && isRightBridgeAligned) {
		return true;
	} else if(isLeftBridgeAligned && !isRightBridgeAligned) {
		motor.speed(leftMotor, 125);
		motor.speed(rightMotor, 150);
		return false;
	} else if(!isLeftBridgeAligned && isRightBridgeAligned) {
		motor.speed(leftMotor, 150);
		motor.speed(rightMotor, 125);
		return false;
	} else {
		motorWheel.forward(125);
		return false;
	}
}

bool alignCliffQRDs(MotorWheel motorWheel) {
	bool leftCliff = foundLeftCliff();
	bool rightCliff = foundRightCliff();
	if(leftCliff && rightCliff) {
		motorWheel.stop();
		return true;
	} else if(leftCliff && !rightCliff) {
		motor.speed(leftMotor, -50);
		motor.speed(rightMotor, 50);
		return false;
	} else if(!leftCliff && rightCliff) {
		motor.speed(leftMotor, 50);
		motor.speed(rightMotor, -50);
		return false;
	} else {
		motorWheel.forward(75);
		return false;
	}
}