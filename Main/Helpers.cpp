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

bool leftBridgeTouchTriggered() {
	return (digitalRead(leftBridgeTouch) == LOW);
}

bool rightBridgeTouchTriggered() {
	return (digitalRead(rightBridgeTouch) == LOW);
}


// Run helpers

bool alignCliffQRDs(MotorWheel motorWheel) {
	bool leftCliff = foundLeftCliff();
	bool rightCliff = foundRightCliff();
	if(leftCliff && rightCliff) {
		motorWheel.stop();
		return true;
	} else if(leftCliff && !rightCliff) {
		motor.speed(leftMotor, -130);
		motor.speed(rightMotor, 130);
		delay(100);
	} else if(!leftCliff && rightCliff) {
		motor.speed(leftMotor, 130);
		motor.speed(rightMotor, -130);
		delay(100);
	} else {
		motorWheel.forward(130);
	}
	return false;
}

void deployBridge() {
	bottomServo.write(bridgeServoDeployPosition);
	delay(2000); // Wait for bridge to deploy
	digitalWrite(communicationOut, HIGH); // Tells top bot to lower the claw again
	delay(2000); // Wait for claw to lower
}

bool followBridgeQRDs(MotorWheel motorWheel, int forwardSpeed) {
	int leftValue = analogRead(leftBridgeQRD);
	int rightValue = analogRead(rightBridgeQRD);
	LCD.clear(); LCD.print(leftValue - rightValue);
	if((rightValue - leftValue) >= bridgeQRDAlignDifference.value) {
		motor.speed(leftMotor, forwardSpeed - 20);
		motor.speed(rightMotor, forwardSpeed + 20);
	} else if((leftValue - rightValue) >= bridgeQRDAlignDifference.value) {
		motor.speed(leftMotor, forwardSpeed + 20);
		motor.speed(rightMotor, forwardSpeed - 20);
	} else {
		motorWheel.forward(forwardSpeed);
	}
	delay(100);
}

bool alignTouchSensors(MotorWheel motorWheel) {
	bool left = leftBridgeTouchTriggered();
	bool right = rightBridgeTouchTriggered();
	if(left && right) {
		motorWheel.stop();
		return true;
	} else if(left && !right) {
		motor.speed(leftMotor, -100);
		motor.speed(rightMotor, -100);
		delay(200);
		motor.speed(leftMotor, -75);
		motor.speed(rightMotor, 75);
	} else if(!left && right) {
		motor.speed(leftMotor, -100);
		motor.speed(rightMotor, -100);
		delay(200);
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