#pragma once
#include <iostream>
#include "ecm.h"
#include "cmp_player.h"
#include "cmp_abilitymanager.h"
//#include "Game.h"

class Item {
protected:
	Entity user;
	sf::Texture tex;
	std::string texName;
	sf::Sprite sprite;
	std::shared_ptr<BasePlayerComponent> player;
public:
	int strengthMod;
	int healthMod;
	int dexMod;
	std::string description;
	std::string name;

	Item(int strength, int health, int dexterity, std::string name, std::string desc, std::string texName);
	Item() = default;
	virtual void Equip(Entity newUser, bool addStat);
	virtual void Unequip(int position);
	void Load();

	sf::Sprite& getSprite();

};

class SpecialItem : public Item {
protected:
	std::shared_ptr<SpecialAbility> special;
public:
	SpecialItem(int strength, int health, int dexterity, std::string name,
		std::string desc, std::string texName, std::shared_ptr<SpecialAbility> sp);
	SpecialItem() = default;

	void Equip(Entity newUser, bool addStat);
	void Unequip(int position);
	void Load();

};
