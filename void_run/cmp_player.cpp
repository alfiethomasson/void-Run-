#include "cmp_player.h"
//#include "cmp_BasePlayerComponent.h"
#include "VoidRun.h"
#include "ecm.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
std::vector<std::shared_ptr<BasePlayerComponent>> enemyInfo;
std::vector<std::shared_ptr<BasePlayerComponent>> playerInfo;

//Clock clock;

BasePlayerComponent::BasePlayerComponent(Entity* p)
	: playerDamage(5.0f), playerHealQuantity(10.0f), Component(p) {}

void BasePlayerComponent::update(double dt) {
	//float Time = Clock.GetElapsedTime();
	//Clock.Reset();
	if (isTurn && isFinishedTurn != true)
	{
		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			cout << "Player Attacks!";
			attack(playerDamage);
			EndTurn();
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			cout << "Player Heals!";
			heal(playerHealQuantity);
			EndTurn();
		}
	}
}

void BasePlayerComponent::updateEnemy(std::shared_ptr<Entity> e)
{
	currentEnemy = e;
	enemyInfo = e->get_components<BasePlayerComponent>();
}

void BasePlayerComponent::attack(float damage)
{
	enemyInfo[0]->takeDamage(damage);
}
void BasePlayerComponent::heal(float healBy)
{
	int tempHealth = currentHealth + healBy;
	if (tempHealth > _maxHealth)
	{
		currentHealth = _maxHealth;
	}
	else
	{
		currentHealth += healBy;
	}
}

void BasePlayerComponent::EndTurn()
{
	cout << "Player Turn Ends!";
	isFinishedTurn = true;
}

int BasePlayerComponent::getStrength() {
	return _strength;
}

int BasePlayerComponent::getMaxHealth() {
	return _maxHealth;
}

int BasePlayerComponent::getCurrentHealth() {
	return currentHealth;
}

int BasePlayerComponent::getDexterity() {
	return _dexterity;
}

void BasePlayerComponent::setStrength(int strength) {
	_strength = strength;
}

void BasePlayerComponent::setMaxHealth(int maxHealth) {
	_maxHealth = maxHealth;
}

void BasePlayerComponent::setCurrentHealth(int health) {
	currentHealth = health;
}

void BasePlayerComponent::setDexterity(int dexterity)
{
	_dexterity = dexterity;
}

void BasePlayerComponent::takeDamage(int dmgRecieved)
{
	currentHealth -= dmgRecieved;
	if (currentHealth <= 0)
	{
		currentHealth = 0;
		_parent->setAlive(false);
	}
}