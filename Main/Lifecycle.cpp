// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Test.h"

MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));


// API
void run()
{
	reset();
	unsigned long prevLoopStartTime = millis();
	int numberOfTeddiesGrabbed = 0;


	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	reset();
	delay(2000);

	LCD.clear();
	LCD.print("Running");
	LCD.setCursor(0, 1);
	LCD.print("Stop to return");
	delay(1000);

	while (true)
	{
		while (millis() - prevLoopStartTime < 10)
		{
		} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		if (cliffCount == 0)
		{
			motorWheel.poll();
		}
		else
		{
			motorWheel.poll(100);
		}
		checkForEwok();
		checkCliffs(motorWheel);
		alignBridgeQRDS(motorWheel);

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

void reset(){
	// TODO: add reset code
	motorWheel.runWithPID = true;
	// setServo(bottomServo, bottomBridgeServoResetPosition)
}

//Stops bot when an ewok is found. It then reverses a little bit and stops again when perfectly aligned.
void checkForEwok(){
	if(digitalRead(stopPin)){
		motorWheel.stop();
		delay(250); //delay is so that there is a quarantee that the ewok is or is not in the claw
		//if the ewok is not in the claw then the bot reverses slowly until the ewok is in the claw again
		while(!digitalRead(stopPin)){
			motorWheel.reverse(50);
			delay(10);
		}
		//once the ewok is in the claw again the bot is stopped until the top bot has fully reset
		while(digitalRead(stopPin)){
			motorWheel.stop();
			delay(10);
		}
		delay(250);
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
