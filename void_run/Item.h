#pragma once
#include <iostream>
#include "ecm.h"

class Item {
protected:
	Entity user;
	sf::Texture tex;
	sf::Sprite sprite;
	std::string texName;
public:
	int strengthMod;
	int healthMod;
	int dexMod;
	std::string description;

	Item(int strength, int health, int dexterity, std::string desc, std::string texName);

	void Equip(Entity newUser);
	void Unequip();
	void Load();

	sf::Sprite& getSprite();

};
