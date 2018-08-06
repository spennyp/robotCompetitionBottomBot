// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Test.h"

MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));
int ewokCount;

// API
void run() {
	reset();
	unsigned long prevLoopStartTime = millis();
	ewokCount = 0;
	int cliffAlignCount = 0;
	bool bridgeDeployed = false;

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");
	delay(2000);

	while(digitalRead(communicationIn) == HIGH) {} 	// Waits for the top bot to give the signal to go
	delay(1000);

	while (true) {
		while (millis() - prevLoopStartTime < 10) { } //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		motorWheel.poll();
		checkForEwok(); // Must be called at beginning 

		if(foundRightCliff() && ewokCount == 1 && !bridgeDeployed) {
			motorWheel.stop();
			delay(1000);
			motorWheel.reverse(120);
			delay(200);
			motorWheel.stop();
			delay(1000);
			motorWheel.turnLeft(80);
			motorWheel.stop();
			delay(1000);
			while(cliffAlignCount < 3) {
				if(alignCliffQRDs(motorWheel)) {
					motorWheel.reverse(75);
					while(foundLeftCliff() && foundRightCliff()) {}
					motorWheel.stop();
					cliffAlignCount ++;
				}
			}
			delay(1000);
			deployBridge();
			bridgeDeployed = true;
			motorWheel.forward();
			delay(1000);
		}

		if(ewokCount >= 1 && bridgeDeployed) {
			int followForwardSpeed = (ewokCount == 1) ? 100 : 60;
			followBridgeQRDs(motorWheel, followForwardSpeed);
			LCD.clear(); LCD.print("Following: "); LCD.print(ewokCount);
			if(ewokCount == 2 && (leftBridgeTouchTriggered() || rightBridgeTouchTriggered())) {
				LCD.clear(); LCD.print("Touch triggered"); 
				motorWheel.stop();
				delay(1000);
				unsigned long alignTouchStartTime = millis();
				while(!alignTouchSensors(motorWheel)) { 
					delay(100); 
					if((millis() - alignTouchStartTime) >= 5000) { break; }
				} // Delay to stop oscilation, timer to insure it doesnt get stuck in this loop
				motorWheel.stop();
				delay(1000);
				detatchTopBot();
				LCD.clear(); LCD.print("DETATCHED!!"); 
				delay(5000);
				break;
			}
		} 

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

//Resets any vars and servo positions
void reset() {
	ewokCount = 0;
	motorWheel.runWithPID();
	resetBridge();
	digitalWrite(communicationOut, HIGH);
}

// Stops bot when an ewok is found.
void checkForEwok() {
	if(clawTriggered()) {
		motorWheel.stop();
		ewokCount++; // Must be above
		if(ewokCount == 1) {
			digitalWrite(communicationOut, LOW); // Tells the claw to stay raised for the bridge drop
		}

		motorWheel.stop();
		while(clawTriggered()) {}
		delay(1000);

		if(ewokCount == 1) {
			motorWheel.runWithPID(140);
		}
	}
}




