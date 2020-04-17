#include "SpecialItem.h"

LaserBurst::LaserBurst(Entity* p)
	: SpecialItem{ p } {}

void LaserBurst::update(double dt)
{
	SpecialItem::update(dt);
}

void LaserBurst::load()
{
	SpecialItem::load();
}

void LaserBurst::doEffect()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		std::cout << "LASER BURST!\n";
		gameScene.UpdateTextBox("LASER BURST!");
		player->attack(100);
		player->EndTurn();
	}
}