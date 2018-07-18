// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Sensors.h"
#include "MotorWheel.h"
#include "Claw.h"
#include "Menu.h"

Claw claw;
MotorWheel motorWheel(speed, PID(proportionalGain, derivativeGain, integralGain, pidThreshold));

const int firstBridgeDropDelay = 2000; // [ms]


void run() {
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

// TODO: Write this
void runBottomBot() {
    if(bottomBotFoundCliff()) {
		motorWheel.stop();
		deployFirstBridge();
		delay(firstBridgeDropDelay);
	}

    bottomBotPlankCheck();
}

// TODO: Write this
void runTopBot(int numberOfTeddiesGrabbed) {
    if(digitalRead(topBotFrontTouchSensor) && numberOfTeddiesGrabbed >= 4) {
        motorWheel.stop();
        activateDumper();
    }
}

void switchToTopBot() {
	claw.switchToTopBot(); // Should be a redundent call
	motorWheel.switchToTopBot();
}

// TODO: Write this
void deployFirstBridge() {
	// TODO: add bridge deploying code here
}

// TODO: Write this
void activateDumper() {
	// TODO: add code to activate the dumper here
}

/// Checks if the bottom bot is in position to deploy top bot, and adjusts if not
void bottomBotPlankCheck() {
	bool lPlank = leftPlankInPosition();
	bool rPlank = rightPlankInPosition();
	if(lPlank && rPlank) {
		switchToTopBot();
	} else if(lPlank) {
		motorWheel.turnLeft(5);
	} else if(rPlank) {
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
