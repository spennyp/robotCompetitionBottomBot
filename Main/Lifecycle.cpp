// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Test.h"

MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));
int stopCount;

// API
void run() {
	reset();
	unsigned long prevLoopStartTime = millis();
	cliffCount = 0;
	stopCount = 0;

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");
	delay(2000);
	//Waits for the top bot to give the signal to go
	while(stopPin) {}

	while (true) {
		while (millis() - prevLoopStartTime < 10) { } //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		motorWheel.poll();
		checkForEwok();

		if(foundLeftCliff()) {
			motorWheel.stop();
			if(cliffCount == 0) {
				delay(1000);
				motorWheel.turnLeft(130, 100, false);
				delay(1000);
			} else if(cliffCount == 1) {
				LCD.clear(); LCD.print("Now deploy");
				deployBridge();
				delay(bridgeDropDelay); 
			}
			cliffCount++;
			motorWheel.runWithPID = true;
		}
		if(stopCount == 2) {
			motorWheel.turnLeft(30,100,false);
		}



		// if (cliffCount == 0) {
		// 	motorWheel.poll();
		// }
		// else
		// {
		// 	motorWheel.poll(125);
		// }
		// LCD.clear(); LCD.home();
		// // checkForEwok();
		// checkCliffs(motorWheel);
		// while(!alignBridgeQRDS(motorWheel)){
		// 	delay(10);
		// }

		// //Exits run() loop for good
		// if(bridgeQRDSAligned){
		// 	motorWheel.stop();
		// 	break;
		// }

		// TODO: Remove this for competition
		if (stopbutton())
		{
			delay(100);
			if (stopbutton())
			{
				LCD.print("Stop");
				motorWheel.stop();
				break;
			}
		}
	}
}

// Helpers

//Resets any vars and servo positions
void reset()
{
	cliffCount = 0;
	stopCount = 0;
	motorWheel.runWithPID = true;
	bridgeQRDSAligned = false;
	resetBridge();

}

//Stops bot when an ewok is found. It then reverses a little bit and stops again when perfectly aligned.
void checkForEwok()
{
	if (!digitalRead(stopPin))
	{
		motorWheel.stop();
		delay(1000); //delay is so that there is a guarantee that the ewok is or is not in the claw
		//if the ewok is not in the claw then the bot reverses slowly until the ewok is in the claw again
		// while(!digitalRead(stopPin)){
		// 	delay(10);
		// }
		while (digitalRead(stopPin))
		{
			motorWheel.reverse(50);
			delay(10);
		}
		//once the ewok is in the claw again the bot is stopped until the top bot has fully reset
		while (!digitalRead(stopPin))
		{
			motorWheel.stop();
			delay(10);
		}
		delay(250);
		stopCount++;
		motorWheel.runWithPID = true;
	}
}

// If all else fails
void codeRed()
{
	unsigned long prevLoopStartTime = millis();
	delay(3000); // Time to take top bot off bottom
	motorWheel.runWithPID = true;

	while (true)
	{
		while (millis() - prevLoopStartTime < 10)
		{
		}
		prevLoopStartTime = millis();

		// TODO: Write this
	}
}
