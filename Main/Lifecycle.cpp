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

// API
void run() {
	reset();
	unsigned long prevLoopStartTime = millis();
	int numberOfTeddiesGrabbed = 0;
	bool switchedToTopBot = false;

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	digitalWrite(0, LOW); // Runs bottom motots

	while(true) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		// // if(checkCodeRedSwitch()) { 
		// // 	codeRed(); 
		// // }

		// LCD.clear(); 
		// LCD.print("N: ");
		// LCD.print(analogRead(topNearTapeFollowQRD));
		// LCD.setCursor(0,1);
		// LCD.print("F: ");
		motorWheel.turnLeft(90, true);
		delay(2000);
		motorWheel.turnRight(90, true);
		delay(2000);

		// LCD.clear(); LCD.print("Cliff: "); LCD.print(analogRead(bottomCliffQRD));

		// motorWheel.poll();

		// if(switchedToTopBot) {
        //     runTopBot(numberOfTeddiesGrabbed);
		// } else {
        //     runBottomBot(numberOfTeddiesGrabbed);
        // }

		// if(clawIRTriggered()) {
		// 	// motorWheel.stop();
		// 	claw.grab();
		// 	numberOfTeddiesGrabbed ++;
		// }

		// if(claw.poll()) {
		// 	if(numberOfTeddiesGrabbed == 1) {
		// 		motorWheel.turnLeft(90, true);
		// 	} else if(numberOfTeddiesGrabbed == 2) {
		// 		claw.switchToTopBot();
		// 		// switchedToTopBot = true;
		// 		motorWheel.turnLeft(10, false);
		// 		motorWheel.forward();
		// 	} else if(numberOfTeddiesGrabbed == 5) {
		// 		motorWheel.turnRight(90, true);
		// 		motorWheel.forward();
		// 	}

		// 	if(numberOfTeddiesGrabbed != 2) {
		// 		motorWheel.runWithPID = true;
		// 	}
		// }

        // motorWheel.poll();

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
	claw.reset();
//  setServo(bottomBridgeServoA, bottomBridgeServoResetPosition);
// 	setServo(topBridgeLowerServo, topBridgeLowerServoResetPosition);
// 	setServo(topBridgeUpperServo, topBridgeUpperServoResetPosition);
// 	setServo(storageDumpServoLeft, leftDumpServoResetPosition);
//  setServo(storageDumpServoRight, rightDumpServoResetPosition);
}

// TODO: Write this
void runBottomBot(int numberOfTeddiesGrabbed) {
    if(bottomBotFoundCliff()) {
		motorWheel.stop();
		motorWheel.turnLeft(90, true);

		// if(numberOfTeddiesGrabbed == 1) {
		// 	deployBottomBridge();
		// } else {
		// 	// TODO: Handle this, maybe turn left?
		// }
	}

	if(numberOfTeddiesGrabbed == 2) {
		bottomBotPlankCheck();
	}
}

void runTopBot(int numberOfTeddiesGrabbed) {
    // if(endOfCourse() && numberOfTeddiesGrabbed == 6) {
    //     motorWheel.stop();
    //     activateDumper();
	// 	while(true) {}
    // }

	// if(numberOfTeddiesGrabbed == 4) {
	// 	motorWheel.turnLeft(90, true);
	// 	motorWheel.runWithPID = true;
	// }

	// if(numberOfTeddiesGrabbed == 5) {
	// 	motorWheel.turnLeft(90, true);
	// 	motorWheel.forward();
	// }

	if(topBotFoundCliff()) {
		// if(numberOfTeddiesGrabbed == 5) {
			// motorWheel.stop();
			// deployTopBridge();
			// motorWheel.forward();
		// } else if (numberOfTeddiesGrabbed == 6) {
			// motorWheel.turnLeft(90, true);
			// motorWheel.runWithPID = true;
			// delay(1000);
			// motorWheel.forward();
		// }

		motorWheel.stop();
		motorWheel.turnLeft(90, true);
		delay(1000);
		motorWheel.forward();
	}
}

void switchToTopBot() {
	claw.switchToTopBot(); // Should be a redundent call
	motorWheel.switchToTopBot();
	motorWheel.forward();
}

void deployBottomBridge() {
	setServo(bottomBridgeServoA, bottomBridgeServoDeployPosition);
	delay(bridgeDropDelay);
}

// TODO: Check this
void deployTopBridge() {
	// setServo(topBridgeLowerServo, topBridgeLowerServoDeployPosition);
	// delay(bridgeDropDelay / 2);
	// setServo(topBridgeUpperServo, topBridgeUpperServoDeployPosition);
	// delay(bridgeDropDelay);
}

void activateDumper() {
	setServo(storageDumpServoLeft, leftDumpServoResetPosition - dumpDeployAngle);
	setServo(storageDumpServoRight, rightDumpServoResetPosition + dumpDeployAngle);
}

/// Checks if the bottom bot is in position to deploy top bot, and adjusts if not
void bottomBotPlankCheck() {
	bool lPlank = leftPlankInPosition();
	bool rPlank = rightPlankInPosition();
	if(lPlank && rPlank) {
		motorWheel.stop();
		switchToTopBot();
	} else if(lPlank) {
		motorWheel.stop();
		motorWheel.turnLeft(5, false);
	} else if(rPlank) {
		motorWheel.stop();
		motorWheel.turnRight(5, false);
	}
}

// If all else fails
void codeRed() {
	// unsigned long prevLoopStartTime = millis();
	// switchToTopBot();
	// delay(3000); // Time to take top bot off bottom
	// motorWheel.runWithPID = true;

	// while(true) {
	// 	while (millis() - prevLoopStartTime < 10) {}
	// 	prevLoopStartTime = millis();

	// 	motorWheel.poll();

	// 	if(clawIRTriggered()) {
	// 		motorWheel.stop();
	// 		claw.grab();
	// 		delay(2000);
	// 		motorWheel.turnLeft(180);
	// 		motorWheel.forward();
	// 	}

	// 	if(topBotFoundCliff()) {
	// 		motorWheel.stop();
	// 	}
	// }
}
