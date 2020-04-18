#include "Specials.h"
#include "Game.h"

//LaserBurst::LaserBurst(Entity* p)
//	: SpecialAbility{ p } {}

void LaserBurst::update(double dt)
{
	SpecialAbility::update(dt);
}

void LaserBurst::load()
{
	texName = "LaserBurst";
	//SpecialAbility::load();
}

void LaserBurst::doEffect()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		std::cout << "LASER BURST!\n";
		gameScene.UpdateTextBox("LASER BURST!");
		player->attack(100, 0);
		player->EndTurn();
	}
}

//OverloadWeapon::OverloadWeapon(Entity* p)
//	: SpecialAbility{ p } {}

void OverloadWeapon::update(double dt)
{
	SpecialAbility::update(dt);
}

void OverloadWeapon::load()
{
	texName = "OverloadWeapon";
}

void OverloadWeapon::doEffect()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		player->addStats(50, 0, 0);
		gameScene.UpdateTextBox("WEAPON OVERLOADED");
		player->EndTurn();
	}
}