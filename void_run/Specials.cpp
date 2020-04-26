#include "Specials.h"
#include "Game.h"

void LaserBurst::update(double dt)
{
	SpecialAbility::update(dt);
}

void LaserBurst::load()
{
	texName = "LaserBurst";
	description = "A burst of energy that hits\nthe enemy for 2 x strength";
	APCost = 3;
}

void LaserBurst::doEffect()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			std::cout << "LASER BURST!\n";
			gameScene.UpdateTextBox("LASER BURST!");
			player->attack(player->getStrength() * 2, 0);
			player->EndTurn();
		}
	}
}

void OverloadWeapon::update(double dt)
{
	SpecialAbility::update(dt);
}

void OverloadWeapon::load()
{
	texName = "OverloadWeapon";
	description = "Overload your weapons energy cells\n to give you +50 strength for \nthis combat";
	APCost = 6;
}

void OverloadWeapon::doEffect()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			player->addStats(50, 0, 0);
			gameScene.UpdateTextBox("WEAPON OVERLOADED");
			player->EndTurn();
		}
	}
}

void UncannySpeed::update(double dt)
{
	SpecialAbility::update(dt);
}

void UncannySpeed::load()
{
	texName = "UncannySpeed";
	description = "Activate your suits matrix function\nimproving your dexterity by 50 this combat";
	APCost = 5;
}

void UncannySpeed::doEffect()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			player->addStats(0, 0, 50);
			gameScene.UpdateTextBox("UNCANNY SPEED ACTIVATED");
			player->EndTurn();
		}
	}
}

void PrimalInstincts::update(double dt)
{
	SpecialAbility::update(dt);
}

void PrimalInstincts::load()
{
	texName = "PrimalInstincts";
	description = "Temporarily tap into your primal\ninstincts, increasing all your stats\n for this combat";
	APCost = 5;
}

void PrimalInstincts::doEffect()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			player->addStats(20, 50, 20);
			gameScene.UpdateTextBox("PRIMAL INSTICTS ACTIVATED");
			player->EndTurn();
		}
	}
}

void DeadlyFumes::update(double dt)
{
	SpecialAbility::update(dt);
}

void DeadlyFumes::load()
{
	texName = "PrimalInstincts";
	description = "Spray the enemy with fumes\n that deal small damage over time\n and lowers their dexterity by 15";
	APCost = 4;
}

void DeadlyFumes::doEffect()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			player->getEnemy()->addStats(0, 0, -20);
			gameScene.UpdateTextBox("PRIMAL INSTICTS ACTIVATED");
			player->EndTurn();
		}
	}
}