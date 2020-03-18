#include "cmp_player.h"
#include "VoidRun.h"
#include "Scene.h"
#include "ecm.h"
#include <iostream>

using namespace sf;

BasePlayerComponent::BasePlayerComponent(Entity* p)
	: playerDamage(100.0f), Component(p) {}

void BasePlayerComponent::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		std::cout << "Attacked!" << "\n";
		attack(playerDamage);
	}
}

void BasePlayerComponent::updateEnemy(std::shared_ptr<Entity> e)
{
	currentEnemy = e;
}

void BasePlayerComponent::attack(float damage)
{
	currentEnemy->setForDelete();
}