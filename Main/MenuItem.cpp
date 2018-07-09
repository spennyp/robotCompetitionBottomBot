// 
// 
// 

#include "MenuItem.h"
#include <avr/EEPROM.h>

class MenuItem
{
public:
	String    Name;
	uint16_t  Value;
	uint16_t* EEPROMAddress;
	static uint16_t MenuItemCount;
	MenuItem(String name)
	{
		MenuItemCount++;
		EEPROMAddress = (uint16_t*)(2 * MenuItemCount);
		Name = name;
		Value = eeprom_read_word(EEPROMAddress);
	}

	void Save();

};

void MenuItem::Save()
{
	eeprom_write_word(EEPROMAddress, Value);
}