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


// Run helpers

//Performs maneuvers necessary to navigate cliffs.
// void checkCliffs(MotorWheel motorWheel) {
// 	bool foundCliffs = foundLeftCliff();
// 	if (foundCliffs && cliffCount == 0) {
// 		motorWheel.stop();
// 		motorWheel.reverse(100);
// 		delay(50);
// 		motorWheel.turnLeft(90, 110, false);
// 		motorWheel.runWithPID = true;
// 		cliffCount++;
// 	} else if (foundCliffs && cliffCount == 1) {
// 		motorWheel.stop();
// 		delay(1000);
// 		while (!alignCliffQRDS(motorWheel)) {
// 			delay(10);
// 		}
// 		// motorWheel.reverse(100);
// 		// delay(20);
// 		// deployBridge();
// 		// cliffCount++;
// 		// delay(bridgeDropDelay);
// 		// motorWheel.forward(150);
// 		// delay(bridgeDriveDelay);
// 		// motorWheel.runWithPID = true;
// 	}
// }

bool alignBridgeQRDS(MotorWheel motorWheel) {
	bool isLeftBridgeAligned = leftBridgeAligned();
	bool isRightBridgeAligned = rightBridgeAligned();
	if(cliffCount == 2 && isLeftBridgeAligned && isRightBridgeAligned) {
		motorWheel.stop();
		digitalWrite(detachPin, HIGH);
		bridgeQRDSAligned = true;
		return true;
	} else if(cliffCount == 2 && isLeftBridgeAligned && !isRightBridgeAligned) {
		motor.speed(leftMotor, -75);
		motor.speed(rightMotor, 100);
		return false;
	} else if(cliffCount == 2 && !isLeftBridgeAligned && isRightBridgeAligned) {
		motor.speed(leftMotor, 100);
		motor.speed(rightMotor, -75);
		return false;
	}
	return true;
}

bool alignCliffQRDS(MotorWheel motorWheel) {
	bool isLeftCliffAligned = foundLeftCliff();
	bool isRightCliffAligned = foundRightCliff();
	if(isLeftCliffAligned && isRightCliffAligned) {
		motorWheel.stop();
		//may need to reverse a small bit
		return true;
	} else if (isLeftCliffAligned && !isRightCliffAligned) {
		motor.speed(leftMotor, -50);
		motor.speed(rightMotor, 0);
		return false;
	} else if (!isLeftCliffAligned && isRightCliffAligned) {
		motor.speed(leftMotor, 0);
		motor.speed(rightMotor, -50);
		return false;
	} else if (!isLeftCliffAligned && !isRightCliffAligned) {
		motorWheel.stop();
		//may need to drive forward a small bit
		return false;
	} 
    return false;
}

void deployBridge() {
	//Tells the top bot to close the claw so that the bridge can be dropped
	digitalWrite(detachPin, HIGH);
	delay(1000);
	digitalWrite(detachPin, LOW);
	bottomServo.write(bridgeServoDeployPosition);
}