// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Sensors.h"
#include "MotorWheel.h"
#include "Claw.h"
#include "Menu.h"

Claw claw;
MotorWheel motorWheel(speed, PID(proportionalGain, derivativeGain, integralGain, pidThreshold));

const int bridgeDropDelay = 2000; // [ms]

// TODO: Figure out all these contants

// Reset constants
const int bottomBridgeLeftServoResetPosition = 0;
const int bottomBridgeRightServoResetPosition = 90;
const int topBridgeLowerServoResetPosition = 0;
const int topBridgeUpperServoResetPosition = 90;
const int leftDumpServoResetPosition = 0;
const int rightDumpServoResetPosition = 180;

// Deploy constants
const int bottomBridgeLeftServoDeployPosition = 90;
const int bottomBridgeRightServoDeployPosition = 0;
const int topBridgeLowerServoDeployPosition = 90;
const int topBridgeUpperServoDeployPosition = 0;
const int leftDumpServoDumpPosition = 180;
const int rightDumpServoDumpPosition = 0;


// API

void run() {
	reset();
	unsigned long prevLoopStartTime = millis();
	int numberOfTeddiesGrabbed = 0;
	bool switchedToTopBot = false;

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	while(true) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		if(checkCodeRedSwitch()) { 
			codeRed(); 
		}

		if(clawIRTriggered()) {
			motorWheel.stop();
			claw.grab();
			numberOfTeddiesGrabbed ++;
			if(numberOfTeddiesGrabbed == 2) {
				claw.switchToTopBot();
				switchedToTopBot = true;
			}
		}

		if(switchedToTopBot) {
            runTopBot(numberOfTeddiesGrabbed);
		} else {
            runBottomBot();
        }

        motorWheel.poll();
		if(claw.poll()) {
			motorWheel.runWithPID = true;
		}

		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				loop();
			}
		}
	}
}


// Helpers

void reset() {
	claw.reset();
	setServo(bottomBridgeLeftServo, bottomBridgeLeftServoResetPosition);
	setServo(bottomBridgeRightServo, bottomBridgeRightServoResetPosition);
	setServo(topBridgeLowerServo, topBridgeLowerServoResetPosition);
	setServo(topBridgeUpperServo, topBridgeUpperServoResetPosition);
	setServo(storageDumpServoLeft, leftDumpServoResetPosition);
	setServo(storageDumpServoRight, rightDumpServoResetPosition);
}

// TODO: Write this
void runBottomBot() {
    if(bottomBotFoundCliff()) {
		motorWheel.stop();
		deployBottomBridge();
		delay(bridgeDropDelay);
	}

    bottomBotPlankCheck();
}

// TODO: Write this
void runTopBot(int numberOfTeddiesGrabbed) {
    if(endOfCourse() && numberOfTeddiesGrabbed >= 4) {
        motorWheel.stop();
        activateDumper();
    }
}

void switchToTopBot() {
	claw.switchToTopBot(); // Should be a redundent call
	motorWheel.switchToTopBot();
}

void deployBottomBridge() {
	setServo(bottomBridgeLeftServo, bottomBridgeLeftServoDeployPosition);
	setServo(bottomBridgeRightServo, bottomBridgeRightServoDeployPosition);
	delay(bridgeDropDelay);
}

void deployTopBridge() {
	setServo(topBridgeLowerServo, topBridgeLowerServoDeployPosition);
	delay(bridgeDropDelay / 2);
	setServo(topBridgeUpperServo, topBridgeUpperServoDeployPosition);
	delay(bridgeDropDelay);
}

void activateDumper() {
	setServo(storageDumpServoLeft, leftDumpServoDumpPosition);
	setServo(storageDumpServoRight, rightDumpServoDumpPosition);
}

/// Checks if the bottom bot is in position to deploy top bot, and adjusts if not
void bottomBotPlankCheck() {
	bool lPlank = leftPlankInPosition();
	bool rPlank = rightPlankInPosition();
	if(lPlank && rPlank) {
		switchToTopBot();
	} else if(lPlank) {
		motorWheel.stop();
		motorWheel.turnLeft(5);
	} else if(rPlank) {
		motorWheel.stop();
		motorWheel.turnRight(5);
	}
}

// If all else fails
void codeRed() {
	unsigned long prevLoopStartTime = millis();
	switchToTopBot();
	delay(3000); // Time to take top bot off bottom
	motorWheel.runWithPID = true;

	while(true) {
		while (millis() - prevLoopStartTime < 10) {}
		prevLoopStartTime = millis();

		motorWheel.poll();

		if(clawIRTriggered()) {
			motorWheel.stop();
			claw.grab();
			delay(2000);
			motorWheel.turnLeft(180);
			motorWheel.forward();
		}

		if(topBotFoundCliff()) {
			motorWheel.stop();
		}
	}
}
