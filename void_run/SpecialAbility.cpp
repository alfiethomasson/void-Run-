#include "SpecialAbility.h"

void SpecialAbility::update(double dt)
{

}

void SpecialAbility::updatePlayer(std::shared_ptr<BasePlayerComponent> pl)
{
	player = pl;
}

int SpecialAbility::getAPCost()
{
	return APCost;
}