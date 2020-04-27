#pragma once
#include <iostream>
#include "enemy_easy.h"
#include "game.h"

EasyEnemy::EasyEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}

bool enraged;
bool usedSwiftFoot;
bool criticalCondition;
bool hasEnraged;

void EasyEnemy::update(double dt)
{
	BaseEnemyComponent::update(dt);
	if (currentHealth <= 20)
	{
		criticalCondition = true;
	}
	else
	{
		criticalCondition = false;
	}

	srand(time(0));

	if (isTurn && isFinishedTurn != true)
	{
		if (specialMove == 0 && (currentEnemy->getDexterity() < _dexterity) && turnCounter == 1) { //If the enemy's special attack is Swift Foot and they have better dexterity, they use it on the first round of combat
			std::cout << "The enemy uses its unique ability: Swift Foot! \n";
			gameScene.UpdateTextBox("The enemy starts dodging, appearing to become faster.");
			_dexterity += 5; //The monster gains +5 to dexterity
			usedSwiftFoot = true;
			EndTurn();
		}
		else if (specialMove == 0 && usedSwiftFoot == false) //Whenever the enemy misses an attack (Or on the second round of combat, if it didn't use it turn one), it will follow up by using Swift Foot, as it tries to have a greater accuracy before attacking again
		{
			std::cout << "The enemy uses its unique ability: Swift Foot! \n";
			gameScene.UpdateTextBox("The enemy starts dodging, appearing to become faster.");
			_dexterity += 5; //The monster gains +5 to dexterity
			usedSwiftFoot = true;
			EndTurn();
		}
		else if (specialMove == 1 && turnCounter % 3 == 1 && criticalCondition == false) //Every third turn (1, 4, 7, 10, etc) the alien will use Double Slice unless it is critical
		{
			std::cout << "The enemy uses its unique attack: Double Slice! \n";
			gameScene.UpdateTextBox("The enemy attacks twice with reckless abandon!");
			attackEnemy(_strength, _dexterity - 10); //Double slice simply has the enemy make two individual attacks
			attackEnemy(_strength, _dexterity - 10); //These attacks both have a -10 to hit
			EndTurn();
		}
		else if (specialMove == 1 && turnCounter % 2 == 1 && criticalCondition == true) //If they are below 40%, they'll switch to using it every other turn (1, 3, 5, 7, 9 etc)
		{
			std::cout << "The enemy uses its unique attack: Double Slice! \n";
			gameScene.UpdateTextBox("The enemy swings twice with reckless abandon!");
			attackEnemy(_strength, _dexterity - 10);
			attackEnemy(_strength, _dexterity - 10);
			EndTurn();
		}
		else if (specialMove == 2 && currentHealth <= _maxHealth && hasEnraged == false) //The first time the alien goes below its max HP, it always enrages
		{
			std::cout << "The enemy uses its unique attack: Enrage! \n";
			gameScene.UpdateTextBox("The enemy thrashes in a fit of rage!");
			enraged = true;
			hasEnraged = true;
			currentHealth += 10;
			EndTurn();
		}
		else if (enraged == true) //Any time the enemy is angy, it unleashes a powerful attack
		{
			std::cout << "The enemy unleashes its rage! \n";
			gameScene.UpdateTextBox("The enemy unleashes its rage!");
			attackEnemy(_strength*2, _dexterity - 5);
			enraged = false;
			EndTurn();
		}
		else if (specialMove == 2) //The basic strucutre is slightly different for enemies that can enrage
		{
			int enemyAI = rand() % 5; //Random number from 0-4. 0-2 is light attack, 3 is enrage, 4 is a medium attack.

			if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2 ) {
				std::cout << "The enemy makes a weak attack! \n";
				gameScene.UpdateTextBox("The enemy attacks you weakly.");
				attackEnemy(_strength, _dexterity);
				EndTurn();
			}
			else if (enemyAI == 3) {
				std::cout << "The enemy uses its unique attack: Enrage! \n";
				gameScene.UpdateTextBox("The enemy thrashes in a fit of rage!");
				enraged = true;
				hasEnraged = true;
				currentHealth += 10;
				EndTurn();
			}
			else if (enemyAI == 4) {
				std::cout << "The enemy makes a medium attack! \n";
				gameScene.UpdateTextBox("The enemy makes an attack at you!");
				attackEnemy(_strength + 5, _dexterity);
				EndTurn();
			}
		}
		else //If none of the conditions for a special attack are met, then we use a random chance for the last two options
		{
			int enemyAI = rand() % 5; //Random number from 0-4. 0-2 is light attack, 3 is enrage, 4 is a medium attack.

			if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
				std::cout << "The enemy makes a weak attack! \n";
				gameScene.UpdateTextBox("The enemy attacks you weakly.");
				attackEnemy(_strength, _dexterity);
				EndTurn();
			}
			else if (enemyAI == 4) {
				std::cout << "The enemy makes a medium attack! \n";
				gameScene.UpdateTextBox("The enemy makes an attack at you!");
				attackEnemy(_strength + 5, _dexterity);
				EndTurn();
			}
		}
	}
}

void EasyEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>();
	spriteManager = sm[0];

	if (specialMove == 0)
	{
		spriteManager->AddIcon("Dodge", "SWIFT FEET\nHigher chance to dodge", true);
	}
	if (specialMove == 2)
	{
		spriteManager->AddIcon("Enrage", "ENRAGE\nEnrages for one turn to heal and\nhit hard next turn", true);
	}
	if (specialMove == 1)
	{
		spriteManager->AddIcon("DoubleSlice", "DOUBLE SLICE\nMakes two attacks in one turn", true);
	}
	BaseEnemyComponent::load();	
}

void EasyEnemy::render()
{
	BaseEnemyComponent::render();
}