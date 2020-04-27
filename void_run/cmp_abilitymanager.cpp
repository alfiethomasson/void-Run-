#include "cmp_abilitymanager.h"

AbilityManager::AbilityManager(Entity* p, int maxSpecial, CombatUI *ui)
	: maxSpecials{ maxSpecial }, combatUI{ *ui }, Component(p) {};

void AbilityManager::update(double dt)
{

}

void AbilityManager::Load()
{
	//Updates player component
	auto p = _parent->GetCompatibleComponent<BasePlayerComponent>();
	player = p[0];
}

//Called when its the players turn, checks if any special item bounding boxes are 
//pressed and does that specials effect if so
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

	//Loops through all specials and if their key is pressed (special 1 key, Q default) then do effect
	for (auto a : specials)
	{
   		a->checkKey();
	}
}

//Resets all special abilities to default
void AbilityManager::resetAbility()
{
	for (auto a : specials)
	{
		a->Reset();
	}
}

//Does all special effects at the start of player turn
void AbilityManager::StartTurnCheck()
{
	for (auto a : specials)
	{
		a->turnStart();
	}
}

//Adds ability to ability manager
bool AbilityManager::addAbility(std::shared_ptr<SpecialAbility> ability)
{
	if (specials.size() < maxSpecials) // if the size of specials vector is less than max specials allowed
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

//Removes ability at certain position
void AbilityManager::removeAbility(int position)
{
	specials.erase(specials.begin() + position);
}

//Returns all specials
std::vector<std::shared_ptr<SpecialAbility>> AbilityManager::getSpecials()
{
	return specials;
}