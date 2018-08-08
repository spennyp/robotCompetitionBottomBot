// Helpers.cpp

#include "Helpers.h"
#include "Globals.h"

// Delays
extern int bridgeDropDelay = 2000;

extern int bridgeLeftServoResetPosition = 0;
extern int bridgeRightServoResetPosition = 90;

	// Deploy constants
	extern int bridgeLeftServoDeployPosition = 90;
extern int bridgeRightServoDeployPosition = 0;

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
    bottomLeftServo.write(bridgeLeftServoResetPosition);
	bottomRightServo.write(bridgeRightServoResetPosition);
}

bool leftBridgeTouchTriggered() {
	return (digitalRead(leftBridgeTouch) == LOW);
}

bool rightBridgeTouchTriggered() {
	return (digitalRead(rightBridgeTouch) == LOW);
}

bool rampTopFound() {
	return (analogRead(rightCliffQRD) >= rampTopThreshold.value);
}

// Run helpers

// bool alignCliffQRDs(MotorWheel motorWheel) {
// 	if(foundLeftCliff()) {
// 		motor.speed(leftMotor, -180);
// 	} else {
// 		motor.speed(leftMotor, 160);
// 	}
// 	if(foundRightCliff()) {
// 		motor.speed(rightMotor, -180);
// 	} else {
// 		motor.speed(rightMotor, 160);
// 	}
// 	delay(75);
// }

 bool alignCliffQRDs(MotorWheel motorWheel) {
 	bool leftCliff = foundLeftCliff();
 	bool rightCliff = foundRightCliff();
 	if(leftCliff && rightCliff) {
 		motorWheel.stop();
 		return true;
 	} else if(leftCliff && !rightCliff) {
		motor.speed(leftMotor, -160);
		motor.speed(rightMotor, 160);
		delay(100);
 	} else if(!leftCliff && rightCliff) {
		motor.speed(leftMotor, 160);
		motor.speed(rightMotor, -160);
		delay(100);
 	} else {
		motorWheel.forward(160);
 	}
 	return false;
 }

void deployBridge() {
	bottomLeftServo.write(bridgeLeftServoDeployPosition);
	bottomRightServo.write(bridgeRightServoDeployPosition);
	delay(2000); // Wait for bridge to deploy
	digitalWrite(communicationOut, HIGH); // Tells top bot to lower the claw again
	delay(2000); // Wait for claw to lower
}

bool followBridgeQRDs(MotorWheel motorWheel, int forwardSpeed) {
	int leftValue = analogRead(leftBridgeQRD);
	int rightValue = analogRead(rightBridgeQRD);
	LCD.clear(); LCD.print(leftValue - rightValue);
	if((rightValue - leftValue) >= bridgeQRDAlignDifference.value) {
		motor.speed(leftMotor, forwardSpeed - 40);
		motor.speed(rightMotor, forwardSpeed + 40);
	} else if((leftValue - rightValue) >= bridgeQRDAlignDifference.value) {
		motor.speed(leftMotor, forwardSpeed + 40);
		motor.speed(rightMotor, forwardSpeed - 40);
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
		motor.speed(leftMotor, -90);
		motor.speed(rightMotor, -90);
		delay(300);
		motor.speed(leftMotor, 60);
		motor.speed(rightMotor, 180);
	} else if(!left && right) {
		motor.speed(leftMotor, -90);
		motor.speed(rightMotor, -90);
		delay(300);
		motor.speed(leftMotor, 180);
		motor.speed(rightMotor, 60);
	} else {
		motorWheel.forward(100);
	}
	return false;
}


void detatchTopBot() {
	digitalWrite(communicationOut, LOW);
}