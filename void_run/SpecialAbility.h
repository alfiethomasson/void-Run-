#pragma once
#include "cmp_player.h"

class BasePlayerComponent;

class SpecialAbility
{
protected:
	std::shared_ptr<BasePlayerComponent> player;
	int APCost;
	std::string description;
	std::string texName;
	sf::Keyboard::Key key;
public:

	SpecialAbility() = default;

	void update(double dt);
	virtual void doEffect() {}
	void updatePlayer(std::shared_ptr<BasePlayerComponent> pl);
	int getAPCost();
	std::string getDescription();
	std::string getTexName();

	void setKey(sf::Keyboard::Key newKey);
	void setAPCost(int newCost);

};