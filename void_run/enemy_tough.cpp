#pragma once
#include <iostream>
#include "enemy_tough.h"

ToughEnemy::ToughEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove} {}
	
bool charging;

void ToughEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true)
	{
		srand(time(0));
		int enemyAI = rand() % 6; //Random number from 0-5. 1-2 is medium attack, 3-4 is unique ability, 5 is a heavy attack.
		if (charging == true) {
			enemyAI = 6; //6 means that it's unleasing a charged shot.
		}


		if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
			std::cout << "The enemy makes a medium attack! \n";
			attackEnemy(_strength+5, _dexterity);
			EndTurn();
		}
		else if (enemyAI == 3 || enemyAI == 4) {
			if (specialMove == 0) {
				std::cout << "The enemy uses its unique attack: Excruciate! \n";
				//This move will lower the player's chance of escape when implemented properly
				EndTurn();
			}
			else if (specialMove == 1) {
				std::cout << "The enemy uses its unique attack: Charged Shot! \n";
				charging = true;
				EndTurn();
			}
			else if (specialMove == 2) {
				std::cout << "The enemy uses its unique attack: Suicide Charge! \n";
				_strength = _strength * 1.6;
				_dexterity = _dexterity * 1.6;
				EndTurn();
			}
		}
		else if (enemyAI == 5) {
			std::cout << "The enemy makes a strong attack! \n";
			attackEnemy(_strength*2, _dexterity);
			EndTurn();
		}
		else if (enemyAI == 6) { //This is a charged shot
			std::cout << "The enemy unleashes a powerful charged attack! \n";
			attackEnemy(_strength + 10, _dexterity + 30);
			charging = false;
			EndTurn();
		}
	}
}

void ToughEnemy::load()
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
}