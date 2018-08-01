// Menu.h

#include "MenuItem.h"

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern void menu();
extern MenuItem menuItems[];

// Add menu items here
extern MenuItem motorSpeed; 
extern MenuItem proportionalGain;
extern MenuItem derivativeGain;
extern MenuItem pidThreshold;
extern MenuItem cliffThreshold;
extern MenuItem delayPerDegreeTurn;
extern MenuItem alignmentThreshold;

#endif
