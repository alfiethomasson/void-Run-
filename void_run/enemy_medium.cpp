#pragma once
#include <iostream>
#include "enemy_medium.h"

MediumEnemy::MediumEnemy(Entity* p, int health, int strength, int dex, float expReward)
	: BaseEnemyComponent{ p, health, strength, dex, expReward } {}
	
void MediumEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true)
	{
		srand(time(0));
		int enemyAI = rand() % 8; //Random number from 0-7. 1-2 is light attack, 3-6 is medium attack, 7-8 is unique ability.
		if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
			std::cout << "The enemy makes a weak attack! \n";
			attackEnemy(_strength);
			EndTurn();
		}
		else if (enemyAI == 3 || enemyAI == 4 || enemyAI == 5) {
			std::cout << "The enemy makes a medium attack! \n";
			attackEnemy(_strength + 5);
			EndTurn();
		}
		else if (enemyAI == 6 || enemyAI == 7) {
			std::cout << "The enemy would use its unique attack here, if I'd programmed it! \n";
			EndTurn();
		}
	}
}