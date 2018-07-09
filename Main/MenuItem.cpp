// MenuItem.cpp

#include "MenuItem.h"
#include <avr/EEPROM.h>

MenuItem::MenuItem(String name)
{
	MenuItemCount++;
	EEPROMAddress = (uint16_t*)(2 * MenuItemCount);
	Name = name;
	Value = eeprom_read_word(EEPROMAddress);
}

void MenuItem::Save()
{
	eeprom_write_word(EEPROMAddress, Value);
}