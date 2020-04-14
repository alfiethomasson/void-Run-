#pragma once
#include <iostream>
#include "ecm.h"

class Item {
protected:
	Entity user;
public:
	int strengthMod;
	int healthMod;
	int dexMod;
	std::string description;

	Item(int strength, int health, int dexterity, std::string desc);

	void Equip(Entity newUser);
	void Unequip();
	void Load();

};