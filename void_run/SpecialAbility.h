#pragma once
#include "cmp_player.h"

class BasePlayerComponent;

class SpecialAbility
{
protected:
	std::shared_ptr<BasePlayerComponent> player;
	int APCost;
public:
	std::string texName;

	SpecialAbility() = default;

	void update(double dt);
	virtual void doEffect() {}
	void updatePlayer(std::shared_ptr<BasePlayerComponent> pl);
	int getAPCost();

};