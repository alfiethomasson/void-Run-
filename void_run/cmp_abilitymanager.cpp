#include "cmp_abilitymanager.h"

AbilityManager::AbilityManager(Entity* p, int maxSpecial)
	: maxSpecials{ maxSpecial }, Component(p) {};

void AbilityManager::update(double dt)
{

}

void AbilityManager::Load()
{

}

void AbilityManager::combatCheck()
{
	for (auto a : specials)
	{
   		a->doEffect();
	}
}

bool AbilityManager::addAbility(std::shared_ptr<SpecialAbility> ability)
{
	if (specials.size() < maxSpecials)
	{
	//	std::shared_ptr<SpecialAbility> temp = std::make_shared<SpecialAbility>(ability);
		specials.push_back(ability);
		return true;
	}
	else
	{
		std::cout << "Ability Limit reached!\n";
		return false;
	}
}

void AbilityManager::removeAbility(int position)
{
	specials.erase(specials.begin() + position);
}