#pragma once
#include <iostream>
#include "enemy_tough.h"
#include "Game.h"

ToughEnemy::ToughEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove} {}
	
bool charging;

void ToughEnemy::update(double dt)
{

	BaseEnemyComponent::update(dt);

	if (isTurn && isFinishedTurn != true)
	{
		srand(time(0));

		if (specialMove == 2) //A suicide charger will always use the most basic, yet most deadly, attack pattern, straying for nothing.
		{
			if (turnCounter == 1) //Turn one, it will start a suicide charge
			{
				std::cout << "The enemy uses its unique ability: Suicide Charge! \n";
				gameScene.UpdateTextBox("The enemy charges suicidally!");
				currentHealth -= 100;
				_strength = _strength * 2;
				_dexterity = _dexterity * 2;
				EndTurn();
			}
			else if (turnCounter % 3 == 2 || turnCounter % 3 == 0) //It will then begin a matter of Normal, Normal, Strong attack, repeating forever
			{
				std::cout << "The enemy makes a medium attack! \n";
				gameScene.UpdateTextBox("The enemy makes an attack at you.");
				attackEnemy(_strength + 5, _dexterity);
				EndTurn();
			}
			else
			{
				std::cout << "The enemy makes a strong attack! \n";
				gameScene.UpdateTextBox("The enemy makes a powerful attack!");
				attackEnemy(_strength * 2, _dexterity);
				EndTurn();
			}
		}
		else if (charging == true)
		{
			std::cout << "The enemy unleashes a powerful charged attack! \n";
			gameScene.UpdateTextBox("The enemy unleashes its charged energy!");
			attackEnemy(_strength + 10, _dexterity + 30);
			charging = false;
			EndTurn();
		}
		else if (specialMove == 0 && turnCounter == 1)
		{
			std::cout << "The enemy uses its unique attack: Excruciate! \n";
			gameScene.UpdateTextBox("The enemy roars: You're too scared to run!");
			currentEnemy->setRunChance(5);
			EndTurn();
		}
		else if (specialMove == 1 && turnCounter != 1 && (currentEnemy->getStrength() < currentHealth))
		{
			std::cout << "The enemy uses is charging a powerful charged shot!";
			gameScene.UpdateTextBox("The enemy starts charging a powerful assault...");
			charging = true;
			EndTurn();
		}
		else //If none of the conditions for a special attack are met, then we use a random chance for the last two options
		{
			int enemyAI = rand() % 5; //Random number from 0-4. 0-2 is medium attack, 3-4 is a heavy attack.

			if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
				std::cout << "The enemy makes a medium attack! \n";
				gameScene.UpdateTextBox("The enemy makes an attack at you.");
				attackEnemy(_strength + 5, _dexterity);
				EndTurn();
			}
			else if (enemyAI == 4) {
				std::cout << "The enemy makes a strong attack! \n";
				gameScene.UpdateTextBox("The enemy makes a powerful attack!");
				attackEnemy(_strength * 2, _dexterity);
				EndTurn();
			}
		}
	}
}

void ToughEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>();
	spriteManager = sm[0];

	if (specialMove == 0)
	{
		spriteManager->AddIcon("Excruciate", "EXCRUCIATE\nDrastically lowers chance of escape", true);
	}
	if (specialMove == 1)
	{
		spriteManager->AddIcon("ChargedAttack", "CHARGED ATTACK\nCharges for one turn to\nunleash a powerful attack", true);
	}
	if (specialMove == 2)
	{
		spriteManager->AddIcon("SuicideCharge", "SUICIDE CHARGE\nGives itself a big strength\nboost but takes more damage", true);
	}
	BaseEnemyComponent::load();

}

void ToughEnemy::render()
{
	BaseEnemyComponent::render();
}