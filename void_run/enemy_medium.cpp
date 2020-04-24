#pragma once
#include <iostream>
#include "enemy_medium.h"

MediumEnemy::MediumEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}
	
bool cursed = false;
bool hasRegenerated;
bool consecutiveMisses;

void MediumEnemy::update(double dt)
{

	BaseEnemyComponent::update(dt);

	srand(time(0));

	if (cursed == true)
	{
		attackEnemy(5, 10000); //If the alien has used a curse, the player takes 5 damage at the start of each of the alien turns
	}

	if (isTurn && isFinishedTurn != true)
	{
		if (specialMove == 1 && currentHealth <= 40 && hasRegenerated == false) //If it has Regeneration, and it's at or below 40% it will use this. One time only.
		{
			std::cout << "The enemy uses its unique ability: Regeneration! \n";
			currentHealth += ((_maxHealth - currentHealth) / 2);
			hasRegenerated = true;
			EndTurn();
		}
		else if (specialMove == 3 && turnCounter % 5 == 1) //If it has Curse, it uses it every fifth turn (1, 6, 11, 16, etc)
		{
			std::cout << "The enemy uses its unique attack: Curse! \n";
			cursed = true;
			EndTurn();
		}
	}
	else if ((specialMove == 0) && (((currentHealth * 0.4) >= (currentEnemy->getCurrentHealth() * 0.3)) && ((currentHealth * 0.4) <= (currentEnemy->getCurrentHealth() * 0.45))))
	{
		std::cout << "The enemy uses its unique attack: Pain Share! \n";
		int painShared = (currentHealth * 0.2);
		currentHealth -= painShared;
		attackEnemy(painShared, 10000); //Deals damage equal to pain shared. Always has 10,000 to hit.
		EndTurn();
	}
	else if (specialMove == 2 && consecutiveMisses >= 2)
	{
		std::cout << "The enemy uses its unique attack: Orbital Strike! \n";
		attackEnemy(_strength, 100000); //Attack, always hit
		EndTurn();
	}
	else if (specialMove == 2)
	{
		int enemyAI = rand() % 6; //Random number from 0-5. 0-2 is light attack, 3-4 is medium attack, 5 is orbital strike.
		if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
			std::cout << "The enemy makes a weak attack! \n";
			if (!attackEnemy(_strength, _dexterity))
			{
				consecutiveMisses++;
			}
			else
			{
				consecutiveMisses = 0;
			}
			EndTurn();
		}
		else if (enemyAI == 3 || enemyAI == 4) {
			std::cout << "The enemy makes a medium attack! \n";
			if (!attackEnemy(_strength + 5, _dexterity))
			{
				consecutiveMisses++;
			}
			else
			{
				consecutiveMisses = 0;
			}
			EndTurn();
		}
		else if (enemyAI == 5) {
			std::cout << "The enemy uses its unique attack: Orbital Strike! \n";
			attackEnemy(_strength, 100000); //Attack, always hit
			EndTurn();
		}
	}
	else
	{
		int enemyAI = rand() % 2; //Random number from 0-4. 0 is light attack, 1 is medium attack.

		if (enemyAI == 0)
		{
			std::cout << "The enemy makes a weak attack! \n";
			attackEnemy(_strength, _dexterity);
			EndTurn();
		}
		else if (enemyAI == 1)
		{
			std::cout << "The enemy makes a medium attack! \n";
			if (!attackEnemy(_strength + 5, _dexterity))
			EndTurn();
		}
	}
}

void MediumEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>();
	spriteManager = sm[0];

	if (specialMove == 0)
	{
		spriteManager->AddIcon("PainShare", "PAIN SHARE\nDamages itself to inflict large damage\nto player", true);
	}
	if (specialMove == 1)
	{
		spriteManager->AddIcon("Regeneration", "REGENERATION\nPassively heals every turn", true);
	}
	if (specialMove == 2)
	{
		spriteManager->AddIcon("Bullseye", "BULLSEYE\nAn attack that never misses", true);
	}
	if (specialMove == 3)
	{
		spriteManager->AddIcon("Curse", "CURSE\nCurses the player, dealing \ndamage every turn", true);
	}
	BaseEnemyComponent::load();

	consecutiveMisses = 0;
}

void MediumEnemy::render()
{
	BaseEnemyComponent::render();
}