#pragma once
#include <iostream>
#include "enemy_easy.h"

EasyEnemy::EasyEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}

bool enraged;

void EasyEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true)
	{
		srand(time(0));
		int enemyAI = rand() % 6; //Random number from 0-5. 1-2 is light attack, 3-4 is unique ability, 5 is a medium attack.
		if (enraged == true) { //If the enemy used Enrage last turn, it will always make a weak attack.
			enemyAI = 0;
		}

		enemyAI = 3;

		if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
			std::cout << "The enemy makes a weak attack! \n";
			if (enraged == true) {
				attackEnemy(_strength+(_strength/2), _dexterity-5);
				enraged = false;
			}
			else {
				attackEnemy(_strength, _dexterity);
			}
			EndTurn();
		}
		else if (enemyAI == 3 || enemyAI == 4) {
			if (specialMove == 0) {
				std::cout << "The enemy uses its unique attack: Debuff! \n";
				_dexterity++; //Hacky fix: Simulates penalty to player's attack by increasing monster's dodge
				EndTurn();
			}
			else if (specialMove == 1) {
				std::cout << "The enemy uses its unique attack: Enrage! \n";
				enraged = true;
				currentHealth += 10;
				EndTurn();
			}
			else if (specialMove == 2) {
				std::cout << "The enemy uses its unique attack: Double Slice! \n";
				attackEnemy(_strength, _dexterity-10); //Currently makes two normal attacks
				attackEnemy(_strength, _dexterity-10); //When accuracy framework is in place, these will have a penalty to hit
				EndTurn();
			}
		}
		else if (enemyAI == 5) {
			std::cout << "The enemy makes a medium attack! \n";
			attackEnemy(_strength + 5, _dexterity);
			EndTurn();
		}
	}
}

void EasyEnemy::load()
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