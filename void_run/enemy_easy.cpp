#pragma once
#include <iostream>
#include "enemy_easy.h"

EasyEnemy::EasyEnemy(Entity* p, int health, int strength, int dex, float expReward)
	: BaseEnemyComponent{ p, health, strength, dex, expReward } {}
	
void EasyEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true)
	{
		srand(time(0));
		int enemyAI = rand() % 2; //Random number from 0-1. 0 is attack, 1 is pass.
		if (enemyAI == 0) {
			std::cout << "The enemy attacks!";
			attackEnemy(_strength);
			EndTurn();
		}
		else if (enemyAI == 1) {
			std::cout << "The enemy passes its turn!";
			EndTurn();
		}
	}
}