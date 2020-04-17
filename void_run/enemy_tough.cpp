#pragma once
#include <iostream>
#include "enemy_tough.h"

ToughEnemy::ToughEnemy(Entity* p, int health, int strength, int dex, float expReward)
	: BaseEnemyComponent{ p, health, strength, dex, expReward } {}
	
void ToughEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true)
	{
		srand(time(0));
		int enemyAI = rand() % 6; //Random number from 0-5. 1-2 is medium attack, 3-4 is unique ability, 5 is a heavy attack.
		if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
			std::cout << "The enemy makes a weak attack! \n";
			attackEnemy(_strength+5);
			EndTurn();
		}
		else if (enemyAI == 3 || enemyAI == 4) {
			std::cout << "The enemy would use its unique attack here, if I'd programmed it! \n";
			EndTurn();
		}
		else if (enemyAI == 5) {
			std::cout << "The enemy makes a strong attack! \n";
			attackEnemy(_strength*2);
			EndTurn();
		}
	}
}