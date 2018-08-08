// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Test.h"

MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));
int numberOfTeddiesGrabbed;
bool bridgeDeployed;
bool foundTopRamp;

void run() {
	unsigned long prevLoopStartTime = millis();
	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	setupRobot();
	while(digitalRead(communicationIn) == HIGH) {} 	// Waits for the top bot to give the signal to go
	delay(1000);

	while (true) {
		while (millis() - prevLoopStartTime < 10) { } //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		motorWheel.poll();
		checkForEwok(); // Must be called at beginning 

		if(atTopOfRamp()) {
			motorWheel.runWithPID(200);
			foundTopRamp = true;
		}

		if(hitFirstEdge()) {
			makeFirstLeftTurn();
			alignForBridgeDrop();
			delay(500);
			deployBridge();
			motorWheel.forward(220); // Drive fast over bridge
			delay(750);
		}

		if(bridgeDeployed) {
			int followForwardSpeed = (numberOfTeddiesGrabbed == 1) ? 120 : 100;
			followBridgeQRDs(followForwardSpeed);
			if(triggeredBridgeTouch()) {
				motorWheel.stop();
				delay(500);
				unsigned long alignTouchStartTime = millis();
				while(!alignTouchSensors()) { 
					delay(500); 
					if((millis() - alignTouchStartTime) >= 5000) { break; }
				} // Delay to stop oscilation, timer to insure it doesnt get stuck in this loop
				motorWheel.stop();
				delay(500);
				detatchTopBot();
				LCD.clear(); LCD.print("DETATCHED!!");
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









