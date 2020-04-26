#include "cmp_abilitymanager.h"

AbilityManager::AbilityManager(Entity* p, int maxSpecial, CombatUI *ui)
	: maxSpecials{ maxSpecial }, combatUI{ *ui }, Component(p) {};

void AbilityManager::update(double dt)
{

}

void AbilityManager::Load()
{
	auto p = _parent->GetCompatibleComponent<BasePlayerComponent>();
	player = p[0];
}

void AbilityManager::combatCheck(sf::Vector2f cursPos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (combatUI.getSp1Box().contains(cursPos))
		{
			if (player->CheckAP(specials.at(0)->getAPCost()))
			{
				specials.at(0)->doEffect();
			}
		}
		else if (combatUI.getSp2Box().contains(cursPos))
		{
			if (player->CheckAP(specials.at(1)->getAPCost()))
			{
				specials.at(1)->doEffect();
			}
		}
		else if (combatUI.getSp3Box().contains(cursPos))
		{
			if (player->CheckAP(specials.at(2)->getAPCost()))
			{
				specials.at(2)->doEffect();
			}
		}
		else if (combatUI.getSp4Box().contains(cursPos))
		{
			if (player->CheckAP(specials.at(3)->getAPCost()))
			{
				specials.at(3)->doEffect();
			}
		}
	}

	for (auto a : specials)
	{
   		a->checkKey();
	}
}

void AbilityManager::resetAbility()
{
	for (auto a : specials)
	{
		a->Reset();
	}
}

void AbilityManager::StartTurnCheck()
{
	for (auto a : specials)
	{
		a->turnStart();
	}
}

bool AbilityManager::addAbility(std::shared_ptr<SpecialAbility> ability)
{
	if (specials.size() < maxSpecials)
	{
		
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

std::vector<std::shared_ptr<SpecialAbility>> AbilityManager::getSpecials()
{
	return specials;
}