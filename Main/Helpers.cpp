// Helpers.cpp

#include "Helpers.h"
#include "Globals.h"
#include "MotorWheel.h"


extern int bridgeLeftServoResetPosition = 0;
extern int bridgeRightServoResetPosition = 90;

// Deploy constants
extern int bridgeLeftServoDeployPosition = 90;
extern int bridgeRightServoDeployPosition = 0;



// Lifecycle veriables
extern MotorWheel motorWheel;
extern int numberOfTeddiesGrabbed;
extern bool bridgeDeployed;
extern bool foundTopRamp;


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

bool leftBridgeTouchTriggered() {
	return (digitalRead(leftBridgeTouch) == LOW);
}

bool rightBridgeTouchTriggered() {
	return (digitalRead(rightBridgeTouch) == LOW);
}

bool rampTopFound() {
	return (analogRead(rightCliffQRD) >= rampTopThreshold.value);
}


// Core Functionality

extern void deployBridge();
extern void resetBridge();

void deployBridge() {
	bottomLeftServo.write(bridgeLeftServoDeployPosition);
	bottomRightServo.write(bridgeRightServoDeployPosition);
	delay(2000); // Wait for bridge to deploy
	digitalWrite(communicationOut, HIGH); // Tells top bot to lower the claw again
	delay(2000); // Wait for claw to lower
	motorWheel.reverse(180);
	delay(150);
	motorWheel.stop();
	bridgeDeployed = true;
}

void resetBridge() {
    bottomLeftServo.write(bridgeLeftServoResetPosition);
	bottomRightServo.write(bridgeRightServoResetPosition);
}


// RunHelpers

void checkForEwok() {
	if(clawTriggered()) {
		motorWheel.stop();
		numberOfTeddiesGrabbed++; // Must be above
		if(numberOfTeddiesGrabbed == 1) {
			digitalWrite(communicationOut, LOW); // Tells the claw to stay raised for the bridge drop
		}

		motorWheel.stop();
		while(clawTriggered()) {} // Waits until top bot is done picking up
		delay(500);

		if(numberOfTeddiesGrabbed == 1) {
			motorWheel.forward(180); // Gets the wheels rolling
			delay(50);
			motorWheel.runWithPID(150);
		}
	}
}

bool atTopOfRamp() {
	return (rampTopFound() && numberOfTeddiesGrabbed == 0 && !foundTopRamp);
}

bool hitFirstEdge() {
	return (foundRightCliff() && numberOfTeddiesGrabbed == 1 && !bridgeDeployed);
}

void makeFirstLeftTurn() {
	motorWheel.stop();
	delay(500);
	motorWheel.reverse(200);
	delay(350);
	motorWheel.stop();
	delay(1000);
	motorWheel.turnLeft(80);
	motorWheel.stop();
	delay(1000);
}

void alignForBridgeDrop() {
	motorWheel.forward(150);
	while(!foundLeftCliff() && !foundRightCliff()) { delay(10); } // Gets to the cliff
	motorWheel.stop();

    unsigned long cliffAlignStartTime = millis();
    while((millis() - cliffAlignStartTime) <= 2000) { 
        if(alignCliffQRDs()) {
            motorWheel.reverse(160);
            delay(100);
        }
        delay(10); 
    }

    if(foundLeftCliff() || foundRightCliff()) {
        motorWheel.reverse(160);
        while(foundLeftCliff() || foundRightCliff()) {}
    }
	motorWheel.hardStop();
}

bool alignCliffQRDs() {
	bool leftCliff = foundLeftCliff();
	bool rightCliff = foundRightCliff();
	if(leftCliff && rightCliff) {
		motorWheel.stop();
		return true;
	} else if(leftCliff && !rightCliff) {
		motor.speed(leftMotor, -190);
		motor.speed(rightMotor, 190);
		delay(100);
	} else if(!leftCliff && rightCliff) {
		motor.speed(leftMotor, 190);
		motor.speed(rightMotor, -190);
		delay(100);
	} else {
		motorWheel.forward(190);
	}
	return false;
}

bool followBridgeQRDs(int forwardSpeed) {
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

bool triggeredBridgeTouch() {
	return (numberOfTeddiesGrabbed == 2 && (leftBridgeTouchTriggered() || rightBridgeTouchTriggered()));
}

bool alignTouchSensors() {
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


// Setup

void setupRobot() {
	numberOfTeddiesGrabbed = 0;
	bridgeDeployed = false;
	foundTopRamp = false;
	reset();
}


// Reset

void reset() {
	resetBridge();
	digitalWrite(communicationOut, HIGH);
	motorWheel.runWithPID();
}

void softReset() {
	motorWheel.stop();
	resetBridge();
	digitalWrite(communicationOut, HIGH);
}
