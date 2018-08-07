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
	bool foundTopRamp = false;

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");
	delay(2000);

	while(digitalRead(communicationIn) == HIGH) {} 	// Waits for the top bot to give the signal to go
	delay(1000);

	while (true) {
		while (millis() - prevLoopStartTime < 10) { } //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		motorWheel.poll();
		checkForEwok(); // Must be called at beginning 

		if(rampTopFound() && ewokCount == 0 && !foundTopRamp) {
			motorWheel.runWithPID(200);
			foundTopRamp = true;
		}

		if(foundRightCliff() && ewokCount == 1 && !bridgeDeployed) {
			motorWheel.stop();
			delay(1000);
			motorWheel.reverse(200);
			delay(350);
			motorWheel.stop();
			delay(1000);
			motorWheel.turnLeft(80);
			motorWheel.stop();
			delay(1000);

			motorWheel.forward(150);
			while(!foundLeftCliff() && !foundRightCliff()) { delay(10); } // Gets to the cliff
			motorWheel.stop();
			unsigned long cliffAlignStartTime = millis();
			while((millis() - cliffAlignStartTime) <= 2000) { 
				if(alignCliffQRDs(motorWheel)) {
					motorWheel.reverse(160);
					delay(100);
				}
				delay(10); 
			}
			if(foundLeftCliff() || foundRightCliff()) {
				motorWheel.reverse(160);
				while(foundLeftCliff() || foundRightCliff()) {}
			}
			motorWheel.reverse(160);
    		delay(150);
    		motorWheel.forward(200); // Hard stop
    		delay(20);
    		motorWheel.stop();

			delay(1000);
			deployBridge();
			motorWheel.reverse(180);
			delay(150);
			motorWheel.stop();
			bridgeDeployed = true;
			motorWheel.forward(220);
			delay(750);
		}

		if(ewokCount >= 1 && bridgeDeployed) {
			int followForwardSpeed = (ewokCount == 1) ? 120 : 100;
			followBridgeQRDs(motorWheel, followForwardSpeed);
			LCD.clear(); LCD.print("Following: "); LCD.print(ewokCount);
			if(ewokCount == 2 && (leftBridgeTouchTriggered() || rightBridgeTouchTriggered())) {
				LCD.clear(); LCD.print("Touch triggered"); 
				motorWheel.stop();
				delay(1000);
				unsigned long alignTouchStartTime = millis();
				while(!alignTouchSensors(motorWheel)) { 
					delay(500); 
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
			motorWheel.forward(180); // Gets the wheels rolling
			delay(50);
			motorWheel.runWithPID(150);
		}
	}
}




