#include "cmp_player.h"
#include "cmp_entityinfo.h"
#include "VoidRun.h"
#include "Scene.h"	
#include "ecm.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
std::vector<std::shared_ptr<EntityInfo>> enemyInfo;
std::vector<std::shared_ptr<EntityInfo>> playerInfo;

//Clock clock;

BasePlayerComponent::BasePlayerComponent(Entity* p)
	: playerDamage(5.0f), playerHealQuantity(10.0f), Component(p) {}

void BasePlayerComponent::update(double dt) {
	//float Time = Clock.GetElapsedTime();
	//Clock.Reset();

	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		cout << "Player Attacks!";
		attack(playerDamage);
	}
	else if (Keyboard::isKeyPressed(Keyboard::W))
	{	
		cout << "Player Heals!";
		heal(playerHealQuantity);
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
}
void BasePlayerComponent::heal(float healBy)
{
	playerInfo[0]->healDamage(healBy);
}