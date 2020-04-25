#pragma once
#include <iostream>
#include "enemy_boss.h"

BossEnemy::BossEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}

void BossEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true)
	{
		int enemyAI; // = ?		

		if (enemyAI == 0) {
			EndTurn();
		}
	}
}