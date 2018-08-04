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
	bool bridgeDeployed = false;

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");
	delay(2000);

	while(digitalRead(communicationIn)) {} 	// Waits for the top bot to give the signal to go
	delay(1000);

	while (true) {
		while (millis() - prevLoopStartTime < 10) { } //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		motorWheel.poll();
		checkForEwok();

		if(ewokCount == 1 && !bridgeDeployed) {
			motorWheel.forward(100); // This left turn needs tuning
			delay(300);
			motorWheel.turnLeft(90);
			delay(1000);
			motorWheel.forward();
			while(!foundLeftCliff()) {}
			motorWheel.stop();
			deployBridge();
			bridgeDeployed = true;
		} 

		if(ewokCount >= 1) {
			if(alignBridgeQRDS(motorWheel) && ewokCount == 2) {
				motorWheel.stop();
				delay(1000);
				detatchTopBot();
				LCD.clear(); LCD.print("Detatched"); 
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
	motorWheel.runWithPID = true;
	resetBridge();
	digitalWrite(communicationOut, HIGH);
}

//Stops bot when an ewok is found. It then reverses a little bit and stops again when perfectly aligned.
void checkForEwok() {
	if (clawTriggered()) {
		motorWheel.stop();
		while(clawTriggered()) {}
		ewokCount++;
		delay(500);
	}
}


