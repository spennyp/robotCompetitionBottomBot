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
extern MenuItem speed; 
extern MenuItem proportionalGain;
extern MenuItem derivativeGain;
extern MenuItem integralGain;
extern MenuItem pidThreshold;

#endif
