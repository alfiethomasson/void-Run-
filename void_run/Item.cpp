#include "Item.h"
#include "cmp_player.h"

Item::Item(int strength, int health, int dexterity, std::string desc)
	: strengthMod {strength},
	healthMod{ health }, dexMod{ dexterity }, description{ desc } {}

void Item::Equip(Entity newUser)
{
	user = newUser;
	auto p = user.GetCompatibleComponent<BasePlayerComponent>();
	auto s = p[0];

	s->addStats(strengthMod, healthMod, dexMod);
}

void Item::Unequip()
{
	auto p = user.GetCompatibleComponent<BasePlayerComponent>();
	auto s = p[0];

	s->addStats(-strengthMod, -healthMod, -dexMod);
}

void Item::Load()
{
	
}