
/*
    Name:       Main.ino
    Created:	7/9/2018 11:44:46 AM
    Author:     LAPTOP-6SDBLG4R\Willi
*/

#include "Motor.h"
#include "PID.h"
#include <ServoTINAH.h>
#include <phys253pins.h>
#include <phys253.h>
#include <motor.h>
#include <avr/EEPROM.h>
#include <LiquidCrystal.h>
#include "MenuItem.h"

uint16_t MenuItem::MenuItemCount = 0;
/* Add the menu items here */
MenuItem Speed = MenuItem("Speed");
MenuItem ProportionalGain = MenuItem("P-gain");
MenuItem DerivativeGain = MenuItem("D-gain");
MenuItem IntegralGain = MenuItem("I-gain");
MenuItem PIDThreshold = MenuItem("PID-thresh");
MenuItem menuItems[] = { Speed, ProportionalGain, DerivativeGain };

void setup()
{
	#include <phys253setup.txt>
	Serial.begin(9600);
	LCD.clear();
	LCD.home();
}

void loop()
{
	LCD.clear(); LCD.home();
	LCD.print("Press start");
	LCD.setCursor(0, 1);
	LCD.print("to open menu");
	delay(100);

	if (startbutton())
	{
		delay(100);
		if (startbutton())
		{
			Menu();
		}
	}
	else if (stopbutton())
	{
		delay(100);
		if (stopbutton())
		{
			Run();
		}
	}
}

void Menu()
{
	LCD.clear(); LCD.home();
	LCD.print("Entering menu");
	delay(500);

	while (true)
	{
		/* Show MenuItem value and knob value */
		int menuIndex = knob(6) * (MenuItem::MenuItemCount) / 1024;
		LCD.clear(); LCD.home();
		LCD.print(menuItems[menuIndex].Name); LCD.print(" "); LCD.print(menuItems[menuIndex].Value);
		LCD.setCursor(0, 1);
		LCD.print("Set to "); LCD.print(knob(7)); LCD.print("?");
		delay(100);

		/* Press start button to save the new value */
		if (startbutton())
		{
			delay(100);
			if (startbutton())
			{
				menuItems[menuIndex].Value = knob(7);
				menuItems[menuIndex].Save();
				delay(250);
			}
		}

		/* Press stop button to exit menu */
		if (stopbutton())
		{
			delay(100);
			if (stopbutton())
			{
				LCD.clear(); LCD.home();
				LCD.print("Leaving menu");
				delay(500);
				return;
			}
		}
	}
}
<<<<<<< HEAD
=======

void Run()
{
	//Check Sensors
	//Drive
	//Deploy Claw
	//Deploy Bridge
	//Deploy Small Bot
}
>>>>>>> Initial MotorWheel class created
