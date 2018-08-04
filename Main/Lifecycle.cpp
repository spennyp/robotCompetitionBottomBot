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

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");
	delay(2000);

	//Waits for the top bot to give the signal to go
	// while(digitalRead(stopPin)) {}
	delay(1000);

	while (true) {
		while (millis() - prevLoopStartTime < 10) { } //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		motorWheel.poll();
		checkForEwok();

		if(ewokCount >= 1) {
			if(alignBridgeQRDS(motorWheel) && ewokCount == 2) {
				motorWheel.stop();
				delay(1000);
				detatchTopBot();
			}
		} 

		if(ewokCount == 1) {
			motorWheel.turnLeft(90);
			delay(1000);
			motorWheel.forward();
			while(!foundLeftCliff()) {}
			motorWheel.stop();
			delay(1000);
			deployBridge();
			delay(2000);
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
	bridgeQRDSAligned = false;
	resetBridge();
	digitalWrite(detachPin, HIGH);
}

//Stops bot when an ewok is found. It then reverses a little bit and stops again when perfectly aligned.
void checkForEwok() {
	if (digitalRead(stopPin) == LOW) {
		motorWheel.stop();
		delay(1000); //delay is so that there is a guarantee that the ewok is or is not in the claw
		//if the ewok is not in the claw then the bot reverses slowly until the ewok is in the claw again
	
		if(digitalRead(stopPin) == HIGH) {
			motorWheel.reverse(50);
			while(digitalRead(stopPin) != LOW) {}
		}
		
		//once the ewok is in the claw again the bot is stopped until the top bot has fully reset
		while (digitalRead(stopPin) == LOW) {}

		delay(250);
		ewokCount++;
	}
}


