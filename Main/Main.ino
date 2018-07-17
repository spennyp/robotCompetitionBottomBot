#include "Globals.h"
#include "MenuItem.h"
#include "MotorWheel.h"
#include "Claw.h"
#include <phys253.h>
#include <avr/EEPROM.h>
#include <LiquidCrystal.h>

uint16_t MenuItem::MenuItemCount = 0;
/* Add the menu items here */
MenuItem Speed = MenuItem("Speed");
MenuItem ProportionalGain = MenuItem("P-gain");
MenuItem DerivativeGain = MenuItem("D-gain");
MenuItem IntegralGain = MenuItem("I-gain");
MenuItem PIDThreshold = MenuItem("PID-thresh");
MenuItem menuItems[] = { Speed, ProportionalGain, DerivativeGain };

Claw claw;
MotorWheel motorWheel(Speed, PID(ProportionalGain, DerivativeGain, IntegralGain, PIDThreshold));

// TODO: Move this into a better place?
int cliffQRDThreshold = 200;
const int firstBridgeDropDelay = 2000; // [ms]

void setup() {
	#include <phys253setup.txt>
	Serial.begin(9600);
	LCD.clear();
	LCD.print("Uploaded :)");

	// Swithing first row of digital ins to outs
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);

	delay(1000);
}

void loop() {
	LCD.clear(); LCD.home();
	LCD.print("Start -> Run PID");
	LCD.setCursor(0, 1);
	LCD.print("Stop -> Menu");
	delay(100);

	if (stopbutton()) {
		delay(100);
		if (stopbutton()) {
			Menu();
		}
	}
	else if (startbutton()) {
		delay(100);
		if (startbutton()) {
			Run();
		}
	}
}

void Menu() {
	LCD.clear(); LCD.home();
	LCD.print("Entering menu");
	delay(500);

	while (true) {
		/* Show MenuItem value and knob value */
		int menuIndex = knob(6) * (MenuItem::MenuItemCount) / 1024;
		LCD.clear(); LCD.home();
		LCD.print(menuItems[menuIndex].Name); LCD.print(" "); LCD.print(menuItems[menuIndex].Value);
		LCD.setCursor(0, 1);
		LCD.print("Set to "); LCD.print(knob(7)); LCD.print("?");
		delay(100);

		/* Press start button to save the new value */
		if (startbutton()) {
			delay(100);
			if (startbutton()) {
				menuItems[menuIndex].Value = knob(7);
				menuItems[menuIndex].Save();
				delay(250);
			}
		}

		/* Press stop button to exit menu */
		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				LCD.clear(); LCD.home();
				LCD.print("Leaving menu");
				delay(500);
				return;
			}
		}
	}
}

void Run() {
	unsigned long prevLoopStartTime = millis();
	int numberOfTeddiesGrabbed = 0;
	bool switchedToTopBot = false;
	
	//Check Sensors
	//Drive
	//Deploy Claw
	//Deploy Bridge
	//Deploy Small Bot

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");
	while(true) {
		//Regulate speed of the main loop to 10 ms
		while (millis() - prevLoopStartTime < 10) {}
		prevLoopStartTime = millis();

		if(clawIRTriggered()) {
			motorWheel.stop();
			claw.grab();
			numberOfTeddiesGrabbed ++;
			if(numberOfTeddiesGrabbed == 2) {
				claw.switchToTopBot();
				switchedToTopBot = true;
			}
		}

		if(foundCliff(switchedToTopBot)) {
			if(!switchedToTopBot) {
				motorWheel.stop();
				deployFirstBridge();
				delay(firstBridgeDropDelay);
			}
		}

		motorWheel.poll();
		if(claw.poll()) {
			motorWheel.runWithPID = true;
		}

		// Run all bottom bot only code
		if(!switchedToTopBot) {
			bottomBotPlankCheck();
		}

		// Run all top bot only code
		if(switchedToTopBot) {
			if(digitalRead(topBotFrontTouchSensor) && numberOfTeddiesGrabbed >= 4) {
				motorWheel.stop();
				activateDumper();
			}
		}

		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				loop();
			}
		}
	}
}

void switchToTopBot() {
	claw.switchToTopBot(); // Should be a redundent call
	motorWheel.switchToTopBot();
}


// Helpers

/// Checks if there is an object between the claw arms
bool clawIRTriggered() {
	return digitalRead(clawIR);
}

/// Checks if the bottom bot is in position to deploy top bot, and adjusts if not
void bottomBotPlankCheck() {
	bool lPlankSensor = digitalRead(leftPlankQRD);
	bool rPlankSensor = digitalRead(rightPlankQRD);
	if(lPlankSensor && rPlankSensor) {
		switchToTopBot();
	} else if(lPlankSensor) {
		motorWheel.turnLeft(5);
	} else if(rPlankSensor) {
		motorWheel.turnRight(5);
	}
}

/// Checks if a cliff was found ahead 
// TODO: Make this cleaner?
bool foundCliff(bool switchedToTopBot) {
	return (!switchedToTopBot && analogRead(bottomCliffQRD) > cliffQRDThreshold) || (switchedToTopBot && analogRead(topCliffQRD) > cliffQRDThreshold);
}

/// Deploys the first bridge
void deployFirstBridge() {
	// TODO: add bridge deploying code here
}

void activateDumper() {
	// TODO: add code to activate the dumper here
}


