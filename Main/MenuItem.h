// MenuItem.h

#ifndef _MENUITEM_h
#define _MENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MenuItem {
 public:
 	static uint16_t MenuItemCount;

	String Name;
	uint16_t Value;
	uint16_t* EEPROMAddress;
	MenuItem(String name);
	void Save();
};

#endif

