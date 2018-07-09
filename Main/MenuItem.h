// MenuItem.h

#ifndef _MENUITEM_h
#define _MENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MenuItem
{
 public:
	void Save();
};

void MenuItem::Save()
{
}

#endif

