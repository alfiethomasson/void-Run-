#pragma once
#include <iostream>
#include "enemy_boss.h"
#include "Game.h"

BossEnemy::BossEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}

int behaviour; //0: Aggressive. 1: Defensive. 2: Passive. 3: Desperate.
bool slimed;
int slimedCounter;

void BossEnemy::update(double dt)
{
	srand(time(0));
	int i = rand() % 5;

	if (slimed == true)
	{
		currentEnemy->setDexterity(-1);
		attackEnemy(5, 10000);
		slimedCounter++;
		gameScene.UpdateTextBox("The fluid coating you saps your strength.");
	}
	if (slimedCounter >= 4)
	{
		slimed = false;
		slimedCounter = 0;
	}

	if (_maxHealth * 0.7) //Whilst above 70% of HP, the enemy is most likely to be passive
	{
		i = rand() % 5;
		if (i == 0 || i == 1 || 1 == 2)		{behaviour = 2;}
		else if (i == 3)					{behaviour = 0;}
		else if (i == 4)					{behaviour = 1;}
	}
	else if (currentHealth <= (_maxHealth * 0.7) && currentHealth >= (_maxHealth * 0.4)) //When at 40%-70% of HP, the enemy is most likely to be aggressive
	{
		i = rand() % 5;
		if (i == 0 || i == 1 || 1 == 2)		{behaviour = 0;}
		else if (i == 3)					{behaviour = 1;}
		else if (i == 4)					{behaviour = 2;}
	}
	else if (currentHealth <= (_maxHealth * 0.4) && currentHealth >= (_maxHealth * 0.1)) //When at 40-70% oh HP, the enemy is most likely to be defensive
	{
		i = rand() % 4;
		if (i == 0 || i == 1 || 1 == 2)		{behaviour = 1;}
		else if (i == 3)					{behaviour = 0;}
	}
	else //Otherwise (below 10%), the enemy is DESPERATE
	{
		behaviour = 3;
	}
	

	if (isTurn && isFinishedTurn != true)
	{
		int enemyAI = rand() % 4;
		if (behaviour == 0) //Aggressive
		{
			if ((currentHealth <= _maxHealth*0.8 && enemyAI == 0) || ((currentHealth < _maxHealth*0.4) && enemyAI == 1)) //20% chance below 80%HP, 40% below 40% HP.
			{
				std::cout << "The enemy drains your life! \n";
				gameScene.UpdateTextBox("The Alien Lord absorbs your health!");
				if (attackEnemy(_strength, _dexterity))
				{
					currentHealth += _strength;
				}
				EndTurn();
			}
			else if ((currentEnemy->getCurrentHealth() >= currentHealth) || enemyAI == 2) //Flat 20% chance, or guaranteed if the player has more HP than the alien
			{
				std::cout << "The enemy attacks twice with a relentless determination! \n";
				gameScene.UpdateTextBox("The Alien Lord attacks twice with relentless determination.");
				attackEnemy(_strength * 1.5, _dexterity - 25);
				attackEnemy(_strength * 1.5, _dexterity - 25);
				EndTurn();
			}
			else if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) //If neither others happen, 60% chance for this shit
			{
				std::cout << "The enemy makes a strong attack! \n";
				gameScene.UpdateTextBox("The Alien Lord makes a powerful attack!");
				attackEnemy(_strength * 2, _dexterity);
				EndTurn();
			}
			else //If nothing else, medium attack time
			{
				std::cout << "The enemy makes a medium attack! \n";
				gameScene.UpdateTextBox("The Alien Lord attacks you!");
				attackEnemy(_strength + 5, _dexterity);
				EndTurn();
			}
		}
		else if (behaviour == 1) //Defensive
		{
			if (((currentHealth >= (_maxHealth * 0.8)) && enemyAI == 0) //For every 20% of missing HP, the monster is 20% more likely to heal
			|| ((currentHealth >= (_maxHealth * 0.6)) && ((enemyAI == 0 || enemyAI == 1)))
			|| ((currentHealth >= (_maxHealth * 0.4)) && ((enemyAI == 0 || enemyAI == 1 || enemyAI == 2)))
			|| ((currentHealth >= (_maxHealth * 0.2)) && ((enemyAI == 0 || enemyAI == 1 || enemyAI == 3))))
			{
				std::cout << "The enemy grows stronger, regaining lost health! \n";
				gameScene.UpdateTextBox("The Alien Lord absorbs power from the air around it!");
				currentHealth += (_maxHealth * 0.1);
				EndTurn();
			}
			else if ((_dexterity > currentEnemy->getDexterity()) || (_strength > currentEnemy->getStrength())) //If the PC has better stats, it buffs itself
			{
				std::cout << "The enemy is gaining more power to match your skill!";
				gameScene.UpdateTextBox("The Alien Lord is evolving to match your skill!");
				_strength += 4;
				_dexterity += 4;
			}
			else if ((currentHealth < currentEnemy->getCurrentHealth()) || (enemyAI == 0 || enemyAI == 1 || enemyAI == 2)) //If the PC has more HP, it'll Life Drain. Otherwise, a 60% chance.
			{
				std::cout << "The enemy makes a drains your life! \n";
				gameScene.UpdateTextBox("The Alien Lord absorbs your health!");
				if (attackEnemy(_strength, _dexterity))
				{
					currentHealth += _strength;
				}
				EndTurn();
			}
			else //Otherwise, it slurps your AP
			{
				std::cout << "The enemy saps your will to fight! \n";
				gameScene.UpdateTextBox("The Alien Lord drains your will to fight!");
				currentEnemy->SpendAP(3);
				EndTurn();
			}
		}
		else if (behaviour == 2) //Passive
		{
			int enemyAI = rand() % 6;
			if ((turnCounter % 3 == 1) || enemyAI == 5) //Every 3 turns, starting from turn 1 (1, 4, 7, 10 etc), or a 1/6 chance, it passes its turn
			{
				std::cout << "The enemy sneers at you! \n";
				gameScene.UpdateTextBox("The Alien Lord sneers passively at you.");
				EndTurn();
			}
			else if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2 || (_dexterity < currentEnemy->getDexterity() && enemyAI == 4)) //3/6 chance of attack. 4/6 if the player has higher dexterity
			{
				if (attackEnemy(0, _dexterity + 1))
				{
					std::cout << "The enemy produces a viscous fluid, flinging it over you!";
					gameScene.UpdateTextBox("The Alien Lord spits a viscious fluid, showering you!");
					slimed = true;
				}
				else
				{
					std::cout << "The enemy throws slime at you, but you sidestep it!";
					gameScene.UpdateTextBox("The Alien Lord attacks you with goo, but you sidestep it.");
				}
				EndTurn();
			}
			else if ((currentHealth >= (_maxHealth * 0.65)) && enemyAI == 6) //Otherwise, if it has below 65%HP, there's a 1/6 chance it heals
			{
				std::cout << "The enemy grows stronger, gathering energy! \n";
				gameScene.UpdateTextBox("The Alien Lord grows stronger!");
				currentHealth += (_maxHealth * 0.1);
				EndTurn();
			}
			else //Otherwise, normal attack
			{
				std::cout << "The enemy makes a medium attack! \n";
				gameScene.UpdateTextBox("The Alien Lords attacks you.");
				attackEnemy(_strength + 5, _dexterity);
				EndTurn();
			}
		}
		else if (behaviour == 3) //Desperate
		{
			if (turnCounter % 4 == 0) //Turns in the 4 times table provoke a massive buff to stats
			{
				std::cout << "The enemy is harnessing a massive amount of energy!";
				gameScene.UpdateTextBox("The Alien Lord is absorbing massive amounts of energy!");
				_strength += 8;
				_dexterity += 8;
			}
		else //Otherwise, BIG ATTACKS FOREVER BABYYYYY
			{
				std::cout << "The enemy attacks twice with a relentless determination! \n";
				gameScene.UpdateTextBox("The Alien Lord swings wildly out of desperation!");
				attackEnemy(_strength * 1.5, _dexterity - 20);
				attackEnemy(_strength * 1.5, _dexterity - 20);
				EndTurn();
			}
		}
	}
}

void BossEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>();
	spriteManager = sm[0];

	currentEnemy->setRunChance(0); //No escape. This is it. Battle to the death.

}