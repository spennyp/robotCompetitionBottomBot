// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Sensors.h"
#include "MotorWheel.h"
#include "Claw.h"
#include "Test.h"

Claw claw;
MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));

const int bridgeDropDelay = 2000; // [ms]

// Reset constants
const int bottomBridgeServoResetPosition = 90;
const int topBridgeLowerServoResetPosition = 0;
const int topBridgeUpperServoResetPosition = 90;
const int leftDumpServoResetPosition = 160;
const int rightDumpServoResetPosition = 10;

// Deploy constants
const int bottomBridgeServoDeployPosition = 150;
const int topBridgeLowerServoDeployPosition = 90;
const int topBridgeUpperServoDeployPosition = 0;
const int dumpDeployAngle = 150;

int cliffCount = 0;

// API
void run() {
	reset();
	unsigned long prevLoopStartTime = millis();
	int numberOfTeddiesGrabbed = 0;
	systemDiagnostics();


	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	reset();
	delay(2000);

	while(true) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		// TODO: Add run code

		// TODO: Remove this for competition
		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				LCD.print("Stop");
				motorWheel.stop();
				break;
			}
		}
	}
}


// Helpers

void reset() {
	// TODO: add reset code
}

// TODO: Fix this
void deployBridge() {
	// setServo(topBridgeLowerServo, topBridgeLowerServoDeployPosition);
	// delay(bridgeDropDelay / 2);
	// setServo(topBridgeUpperServo, topBridgeUpperServoDeployPosition);
	// delay(bridgeDropDelay);
}

void activateDumper() {
	// setServo(storageDumpServoLeft, leftDumpServoResetPosition - dumpDeployAngle, false);
	// setServo(storageDumpServoRight, rightDumpServoResetPosition + dumpDeployAngle, false);
}

// If all else fails
void codeRed() {
	unsigned long prevLoopStartTime = millis();
	delay(3000); // Time to take top bot off bottom
	motorWheel.runWithPID = true;

	while(true) {
		while (millis() - prevLoopStartTime < 10) {}
		prevLoopStartTime = millis();

		// TODO: Write this
	}
}
