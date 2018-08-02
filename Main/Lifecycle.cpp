// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Sensors.h"
#include "MotorWheel.h"
#include "Test.h"

MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));


int cliffCount = 0;

// API
void run()
{
	reset();
	unsigned long prevLoopStartTime = millis();
	systemDiagnostics();

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
		checkCliffs();
		alignBridgeQRDS();

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

void reset()
{
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

//Performs maneuvers necessary to navigate cliffs.
void checkCliffs()
{
	bool foundCliffs = foundCliff();
	if (foundCliffs && cliffCount == 0)
	{
		motorWheel.stop();
		motorWheel.reverse(100);
		delay(50);
		motorWheel.turnLeft(90, 100, false);
		motorWheel.runWithPID = true;
		cliffCount++;
	}
	else if (foundCliffs && cliffCount == 1)
	{
		motorWheel.reverse(100);
		delay(20);
		deployBridge();
		cliffCount++;
		delay(bridgeDropDelay);
		motorWheel.forward(150);
		delay(bridgeDriveDelay);
		motorWheel.runWithPID = true;
	}
}

void alignBridgeQRDS(){
	bool isLeftBridgeAligned = leftBridgeAligned();
	bool isRightBridgeAligned = rightBridgeAligned();
	if(cliffCount == 2 && isLeftBridgeAligned && isRightBridgeAligned){
		motorWheel.stop();
		digitalWrite(detachPin, HIGH);
		while(true){
			delay(5000);
		}
	} else if(cliffCount == 2 && isLeftBridgeAligned && !isRightBridgeAligned){
		motor.speed(leftMotor, -75);
		motor.speed(rightMotor, 100);
	} else if(cliffCount == 2 && !isLeftBridgeAligned && isRightBridgeAligned){
		motor.speed(leftMotor, 100);
		motor.speed(rightMotor, -75);
	}
}

void deployBridge()
{
	// setServo(bottomServo, bottomBridgeServoDeployPosition);
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
