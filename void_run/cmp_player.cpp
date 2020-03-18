#include "cmp_player.h"
#include "cmp_entityinfo.h"
#include "VoidRun.h"
#include "Scene.h"
#include "ecm.h"
#include <iostream>

using namespace sf;
std::vector<std::shared_ptr<EntityInfo>> enemyInfo;

bool hasAttacked = false;
//Clock clock;

BasePlayerComponent::BasePlayerComponent(Entity* p)
	: playerDamage(1.0f), Component(p) {}

void BasePlayerComponent::update(double dt) {
	//float Time = Clock.GetElapsedTime();
	//Clock.Reset();

	if (Keyboard::isKeyPressed(Keyboard::Q) && hasAttacked == false)
	{
		//std::cout << "Attacked!" << "\n";
		attack(playerDamage);
	}
}

void BasePlayerComponent::updateEnemy(std::shared_ptr<Entity> e)
{
	currentEnemy = e;
	enemyInfo = e->get_components<EntityInfo>();
}

void BasePlayerComponent::attack(float damage)
{
	enemyInfo[0]->takeDamage(damage);
	hasAttacked = true;
}