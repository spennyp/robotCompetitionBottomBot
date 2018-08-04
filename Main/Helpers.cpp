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
    return digitalRead(stopPin);
}

bool foundLeftCliff() {
    return (analogRead(leftCliffQRD) > cliffThreshold.value);
}
bool foundRightCliff() {
    return (analogRead(rightCliffQRD) > cliffThreshold.value);
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
	digitalWrite(detachPin, LOW);
}


// Run helpers

void deployBridge() {
	//Tells the top bot to close the claw so that the bridge can be dropped
	digitalWrite(detachPin, HIGH);
	delay(1000);
	digitalWrite(detachPin, LOW);
	bottomServo.write(bridgeServoDeployPosition);
}

bool alignBridgeQRDS(MotorWheel motorWheel) {
	bool isLeftBridgeAligned = leftBridgeAligned();
	bool isRightBridgeAligned = rightBridgeAligned();
	if(isLeftBridgeAligned && isRightBridgeAligned) {
		motorWheel.stop();
		digitalWrite(detachPin, HIGH);
		bridgeQRDSAligned = true;
		return true;
	} else if(isLeftBridgeAligned && !isRightBridgeAligned) {
		motor.speed(leftMotor, 75);
		motor.speed(rightMotor, 100);
		return false;
	} else if(!isLeftBridgeAligned && isRightBridgeAligned) {
		motor.speed(leftMotor, 100);
		motor.speed(rightMotor, 75);
		return false;
	} else {
		motorWheel.forward(100);
		return false;
	}
}