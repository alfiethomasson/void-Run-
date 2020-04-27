#include "SpecialAbility.h"

void SpecialAbility::update(double dt)
{

}

//Updates player 
void SpecialAbility::updatePlayer(std::shared_ptr<BasePlayerComponent> pl)
{
	player = pl;
}

//Getters
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

std::string SpecialAbility::getName()
{
	return name;
}

//Setters
void SpecialAbility::setKey(sf::Keyboard::Key newKey)
{
	key = newKey;
}

void SpecialAbility::setAPCost(int newCost)
{
	APCost = newCost;
}