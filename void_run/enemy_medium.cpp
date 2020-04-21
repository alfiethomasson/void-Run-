#pragma once
#include <iostream>
#include "enemy_medium.h"

MediumEnemy::MediumEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}
	
bool cursed = false;

void MediumEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true)
	{
		srand(time(0));
		int enemyAI = rand() % 8; //Random number from 0-7. 1-2 is light attack, 3-6 is medium attack, 7-8 is unique ability.

		if (cursed == true) {
			attackEnemy(5, 10000); //If the alien has used a curse, the player takes 5 damage at the start of each of the alien turns
		}

		if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
			std::cout << "The enemy makes a weak attack! \n";
			attackEnemy(_strength, _dexterity);
			EndTurn();
		}
		else if (enemyAI == 3 || enemyAI == 4 || enemyAI == 5) {
			std::cout << "The enemy makes a medium attack! \n";
			attackEnemy(_strength + 5, _dexterity);
			EndTurn();
		}
		else if (enemyAI == 6 || enemyAI == 7) {
			if (specialMove == 0) {
				std::cout << "The enemy uses its unique attack: Pain Share! \n";
				int painShared = (currentHealth * 0.2);
				currentHealth -= painShared;
				attackEnemy(painShared, 10000); //Deals damage equal to pain shared. Always has 10,000 to hit.
				EndTurn();
			}
			else if (specialMove == 1) {
				std::cout << "The enemy uses its unique attack: Regeneration! \n";
				currentHealth += ((_maxHealth - currentHealth) / 2);
				EndTurn();
			}
			else if (specialMove == 2) {
				std::cout << "The enemy uses its unique attack: Orbital Strike! \n";
				attackEnemy(_strength, 100000); //Attack, always hit
				EndTurn();
			}
			else if (specialMove == 3) {
				std::cout << "The enemy uses its unique attack: Curse! \n";
				cursed = true;
				EndTurn();
			}
		}
	}
}

void MediumEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>();
	spriteManager = sm[0];

	if (specialMove == 0)
	{

	}
	if (specialMove == 1)
	{

	}
	if (specialMove == 2)
	{

	}
	if (specialMove == 3)
	{

	}
}