// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Sensors.h"
#include "MotorWheel.h"
#include "Test.h"

MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));

const int bridgeDropDelay = 2000; // [ms]
const int bridgeDriveDelay = 3000;

// Reset constants
const int bridgeServoResetPosition = 90;

// Deploy constants
const int bottomBridgeServoDeployPosition = 150;

int cliffCount = 0;
bool bridgeQRDSAligned = false;

// API
void run()
{
	reset();
	unsigned long prevLoopStartTime = millis();
	// systemDiagnostics();

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

		// LCD.clear();
		// LCD.home();
		// LCD.print("L: ");
		// LCD.print(analogRead(leftCliffQRD));
		// LCD.print(" R: ");
		// LCD.print(analogRead(rightCliffQRD));

		// while (!alignCliffQRDS())
		// {
		// 	LCD.clear();
		// 	LCD.home();
		// 	LCD.print("L: ");
		// 	LCD.print(analogRead(leftCliffQRD));
		// 	LCD.print(" R: ");
		// 	LCD.print(analogRead(rightCliffQRD));
		// 	delay(10);
		// }

		if (cliffCount == 0)
		{
			motorWheel.poll();
		}
		else
		{
			motorWheel.poll(125);
		}
		LCD.clear(); LCD.home();
		LCD.print("C: "); LCD.print(analogRead(0));
		LCD.setCursor(0,1); LCD.print("N: "); LCD.print(analogRead(1)); LCD.print("F: "); LCD.print(analogRead(2));
		// checkForEwok();
		checkCliffs();
		while(!alignBridgeQRDS()){
			delay(10);
		}
		if(bridgeQRDSAligned){
			motorWheel.stop();
			break;
		}

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
	motorWheel.runWithPID = true;
	bridgeQRDSAligned = false;
	RCServo0.write(bridgeServoResetPosition);
}

//Stops bot when an ewok is found. It then reverses a little bit and stops again when perfectly aligned.
void checkForEwok()
{
	if (digitalRead(stopPin))
	{
		motorWheel.stop();
		delay(250); //delay is so that there is a quarantee that the ewok is or is not in the claw
		//if the ewok is not in the claw then the bot reverses slowly until the ewok is in the claw again
		while (!digitalRead(stopPin))
		{
			motorWheel.reverse(50);
			delay(10);
		}
		//once the ewok is in the claw again the bot is stopped until the top bot has fully reset
		while (digitalRead(stopPin))
		{
			motorWheel.stop();
			delay(10);
		}
		delay(250);
	}
}

//Performs maneuvers necessary to navigate cliffs.
void checkCliffs()
{
	bool foundCliffs = foundLeftCliff();
	if (foundCliffs && cliffCount == 0)
	{
		motorWheel.stop();
		motorWheel.reverse(100);
		delay(50);
		motorWheel.turnLeft(90, 110, false);
		motorWheel.runWithPID = true;
		cliffCount++;
	}
	else if (foundCliffs && cliffCount == 1)
	{
		motorWheel.stop();
		delay(1000);
		while (!alignCliffQRDS())
		{
			delay(10);
		}
		// motorWheel.reverse(100);
		// delay(20);
		// deployBridge();
		// cliffCount++;
		// delay(bridgeDropDelay);
		// motorWheel.forward(150);
		// delay(bridgeDriveDelay);
		// motorWheel.runWithPID = true;
	}
}

bool alignBridgeQRDS()
{
	bool isLeftBridgeAligned = leftBridgeAligned();
	bool isRightBridgeAligned = rightBridgeAligned();
	if (cliffCount == 2 && isLeftBridgeAligned && isRightBridgeAligned)
	{
		motorWheel.stop();
		digitalWrite(detachPin, HIGH);
		bridgeQRDSAligned = true;
		return true;
	}
	else if (cliffCount == 2 && isLeftBridgeAligned && !isRightBridgeAligned)
	{
		motor.speed(leftMotor, -75);
		motor.speed(rightMotor, 100);
		return false;
	}
	else if (cliffCount == 2 && !isLeftBridgeAligned && isRightBridgeAligned)
	{
		motor.speed(leftMotor, 100);
		motor.speed(rightMotor, -75);
		return false;
	}
	//breaks out of while loop
	return true;
}

bool alignCliffQRDS()
{
	bool isLeftCliffAligned = foundLeftCliff();
	bool isRightCliffAligned = foundRightCliff();
	if (isLeftCliffAligned && isRightCliffAligned)
	{
		motorWheel.stop();
		return true;
	}
	else if (isLeftCliffAligned && !isRightCliffAligned)
	{
		motor.speed(leftMotor, -100);
		motor.speed(rightMotor, 0);
		return false;
	}
	else if (!isLeftCliffAligned && isRightCliffAligned)
	{
		motor.speed(leftMotor, 0);
		motor.speed(rightMotor, -100);
		return false;
	} 
	else if (!isLeftCliffAligned && !isRightCliffAligned)
	{
		motorWheel.stop();
		return true;
	}
}

void deployBridge()
{
	RCServo0.write(bottomBridgeServoDeployPosition);
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
