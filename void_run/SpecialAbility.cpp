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

std::string SpecialAbility::getDescription()
{
	return description;
}

std::string SpecialAbility::getTexName()
{
	return texName;
}

void SpecialAbility::setKey(sf::Keyboard::Key newKey)
{
	key = newKey;
}

void SpecialAbility::setAPCost(int newCost)
{
	APCost = newCost;
}