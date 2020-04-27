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

	if (isTurn && isFinishedTurn != true) //Only acts during its turn
	{
		srand(time(0));

		if (specialMove == 2) //A suicide charger will always use the most basic, yet most deadly, attack pattern, straying for nothing.
		{
			if (turnCounter == 1) //Turn one, it will start a suicide charge
			{
				std::cout << "The enemy uses its unique ability: Suicide Charge! \n";
				gameScene.UpdateTextBox("The enemy charges suicidally!"); //Loses 100HP, doubles STR and DEX
				currentHealth -= 100;
				_strength = _strength * 2;
				_dexterity = _dexterity * 2;
				EndTurn();
			}
			else if (turnCounter % 3 == 2 || turnCounter % 3 == 0) //It will then begin a pattern of Normal, Normal, Strong attack, repeating forever
			{
				std::cout << "The enemy makes a medium attack! \n"; //Medium attack
				gameScene.UpdateTextBox("The enemy makes an\nattack at you.");
				attackEnemy(_strength + 5, _dexterity, "MediumAttack");
				EndTurn();
			}
			else
			{
				std::cout << "The enemy makes a strong attack! \n"; //Strong attack
				gameScene.UpdateTextBox("The enemy makes a\npowerful attack!");
				attackEnemy(_strength * 2, _dexterity, "HeavyAttack");
				EndTurn();
			}
		}
		else if (charging == true) //If it previously charged a powerful attack (Only available to Charging enemies), its next action is always to unleash it
		{
			std::cout << "The enemy unleashes a powerful charged attack! \n"; //Launches charged attack
			gameScene.UpdateTextBox("The enemy unleashes\nits charged energy!");
			attackEnemy(_strength + 10, _dexterity + 30, "HeavyAttack");
			charging = false;
			EndTurn();
		}
		else if (specialMove == 0 && turnCounter == 1) //Always uses Excruciate on turn 1 if it has it
		{
			std::cout << "The enemy uses its unique attack: Excruciate! \n"; //Sets escape chance to 5%
			gameScene.UpdateTextBox("The enemy roars: You're\ntoo scared to run!");
			currentEnemy->setRunChance(5);
			EndTurn();
		}
		else if (specialMove == 1 && turnCounter != 1 && (currentEnemy->getStrength() < currentHealth)) //Never uses a Charge Shot on turn 1: It also won't do it if it has lower health than the player's strength (At risk of dying)
		{
			std::cout << "The enemy uses is charging a powerful charged shot!"; //Starts charging a powerful short to release next turn
			gameScene.UpdateTextBox("The enemy starts charging\na powerful assault...");
			charging = true;
			EndTurn();
		}
		else //If none of the conditions for a special attack are met, then we use a random chance for the last two options
		{
			int enemyAI = rand() % 5; //Random number from 0-4. 0-2 is medium attack, 3-4 is a heavy attack.

			if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
				std::cout << "The enemy makes a medium attack! \n"; //Medium Attack
				gameScene.UpdateTextBox("The enemy makes an\nattack at you.");
				attackEnemy(_strength + 5, _dexterity, "MediumAttack");
				EndTurn();
			}
			else if (enemyAI == 4) {
				std::cout << "The enemy makes a strong attack! \n"; //Strong Attack
				gameScene.UpdateTextBox("The enemy makes\na powerful attack!");
				attackEnemy(_strength * 2, _dexterity, "HeavyAttack");
				EndTurn();
			}
		}
	}
}

void ToughEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>(); //Sets sprite icons for the alien's unique abilities
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
		spriteManager->AddIcon("SuicideCharge", "SUICIDE CHARGE\nGives itself a big strength\nboost but taking a large\namount of damage", true);
	}
	BaseEnemyComponent::load();

}

void ToughEnemy::render()
{
	BaseEnemyComponent::render(); //Renders enemy
}