#pragma once
#include <iostream>
#include "enemy_medium.h"
#include "Game.h"

MediumEnemy::MediumEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}
	
bool cursed = false;
bool hasRegenerated;
bool consecutiveMisses;

void MediumEnemy::update(double dt)
{

	BaseEnemyComponent::update(dt);

	srand(time(0));

	if (isTurn && isFinishedTurn != true)
	{
		if (cursed == true)
		{
			attackEnemy(5, 10000, ""); //If the alien has used a curse, the player takes 5 damage at the start of each of the alien turns
			gameScene.UpdateTextBox("You're hurt by your curse.");
		}

		if (specialMove == 1 && currentHealth <= 40 && hasRegenerated == false) //If it has Regeneration, and it's at or below 40% it will use this. One time only.
		{
			std::cout << "The enemy uses its unique ability: Regeneration! \n";
			gameScene.UpdateTextBox("The enemy regenerates!");
			currentHealth += ((_maxHealth - currentHealth) / 2);
			hasRegenerated = true;
			EndTurn();
		}
		else if (specialMove == 3 && turnCounter % 5 == 1) //If it has Curse, it uses it every fifth turn (1, 6, 11, 16, etc)
		{
			std::cout << "The enemy uses its unique attack: Curse! \n";
			gameScene.UpdateTextBox("The enemy curses you!");
			cursed = true;
			EndTurn();
		}
		else if ((specialMove == 0) && (((currentHealth * 0.4) >= (currentEnemy->getCurrentHealth() * 0.3)) && ((currentHealth * 0.4) <= (currentEnemy->getCurrentHealth() * 0.45))))
		{
			std::cout << "The enemy uses its unique attack: Pain Share! \n"; //Uses pain share if it will deal 30-45% of the player's health but not kill itself
			gameScene.UpdateTextBox("The enemy share its pain with you!");
			int painShared = (currentHealth * 0.2);
			currentHealth -= painShared;
			attackEnemy(painShared, 10000, "MediumAttack"); //Deals damage equal to pain shared. Always has 10,000 to hit.
			EndTurn();
		}
		else if (specialMove == 2 && consecutiveMisses >= 2) //If the enemy has missed twice in a row, they move to spamming their always hit attack
		{
			std::cout << "The enemy uses its unique attack: Orbital Strike! \n";
			gameScene.UpdateTextBox("The enemy scores a bullseye!");
			attackEnemy(_strength, 100000, "MediumAttack"); //Attack, always hit
			EndTurn();
		}
		else if (specialMove == 2) //Otherwise, AI is a bit different for Bullseye enemies
		{
			int enemyAI = rand() % 6; //Random number from 0-5. 0-2 is light attack, 3-4 is medium attack, 5 is orbital strike.
			if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) {
				std::cout << "The enemy makes a weak attack! \n"; //Weak attack
				gameScene.UpdateTextBox("The enemy attacks you weakly.");
				if (!attackEnemy(_strength, _dexterity, "MediumAttack"))
				{
					consecutiveMisses++; //Counts consecutive misses so it can switch to more accurate moves
				}
				else
				{
					consecutiveMisses = 0;
				}
				EndTurn();
			}
			else if (enemyAI == 3 || enemyAI == 4) {
				std::cout << "The enemy makes a medium attack! \n"; //Medium attack
				gameScene.UpdateTextBox("The enemy makes an attack.");
				if (!attackEnemy(_strength + 5, _dexterity, "MediumAttack"))
				{
					consecutiveMisses++; //Counts consecutive misses so it can switch to more accurate moves
				}
				else
				{
					consecutiveMisses = 0;
				}
				EndTurn();
			}
			else if (enemyAI == 5) {
				std::cout << "The enemy uses its unique attack: Orbital Strike! \n";
				gameScene.UpdateTextBox("The enemy scores a bullseye.");
				attackEnemy(_strength, 100000, "MediumAttack"); //Attack, always hit
				EndTurn();
			}
		}
		else
		{
			int enemyAI = rand() % 2; //Random number from 0-4. 0 is light attack, 1 is medium attack.

			if (enemyAI == 0)
			{
				std::cout << "The enemy makes a weak attack! \n"; //Weak Attack
				gameScene.UpdateTextBox("The enemy attacks you weakly.");
				attackEnemy(_strength, _dexterity, "MediumAttack");
				EndTurn();
			}
			else if (enemyAI == 1)
			{
				std::cout << "The enemy makes a medium attack! \n"; //Medium Attack
				gameScene.UpdateTextBox("The enemy makes an attack at you.");
				attackEnemy(_strength + 5, _dexterity, "MediumAttack");
				EndTurn();
			}
		}
	}
}

void MediumEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>(); //Get icons for unique attacks
	spriteManager = sm[0];

	if (specialMove == 0)
	{
		spriteManager->AddIcon("PainShare", "PAIN SHARE\nDamages itself to inflict large damage\nto player", true);
	}
	if (specialMove == 1)
	{
		spriteManager->AddIcon("Regeneration", "REGENERATION\nHeals once per battle", true);
	}
	if (specialMove == 2)
	{
		spriteManager->AddIcon("Bullseye", "BULLSEYE\nAn attack that never misses", true);
	}
	if (specialMove == 3)
	{
		spriteManager->AddIcon("Curse", "CURSE\nCurses the player, dealing \ndamage every turn", true);
	}
	BaseEnemyComponent::load();

	consecutiveMisses = 0;
}

void MediumEnemy::render()
{
	BaseEnemyComponent::render(); //Render the enemy
}