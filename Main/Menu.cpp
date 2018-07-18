// Menu.cpp

#include "Menu.h"
#include "Globals.h"
#include <LiquidCrystal.h>
#include <avr/EEPROM.h>

uint16_t MenuItem::MenuItemCount = 0;

// Add Menu items here and in .h
MenuItem speed = MenuItem("Speed");
MenuItem proportionalGain = MenuItem("P-gain");
MenuItem derivativeGain = MenuItem("D-gain");
MenuItem integralGain = MenuItem("I-gain");
MenuItem pidThreshold = MenuItem("PID-thresh");
MenuItem menuItems[] = { speed, proportionalGain, derivativeGain, integralGain, pidThreshold };

void menu() {
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