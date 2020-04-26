#pragma once
#include "cmp_player.h"

class BasePlayerComponent;

class SpecialAbility
{
protected:
	std::shared_ptr<BasePlayerComponent> player;
	int APCost;
	std::string description;
	std::string name;
	std::string texName;
	sf::Keyboard::Key key;
public:

	SpecialAbility() = default;

	void update(double dt);
	virtual void doEffect() {}
	virtual void turnStart() {}
	virtual void Reset() {}
	virtual void checkKey() {}
	void updatePlayer(std::shared_ptr<BasePlayerComponent> pl);
	int getAPCost();
	std::string getDescription();
	std::string getTexName();
	std::string getName();

	void setKey(sf::Keyboard::Key newKey);
	void setAPCost(int newCost);

};