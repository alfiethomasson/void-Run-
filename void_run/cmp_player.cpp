#include "cmp_player.h"
#include "cmp_enemy.h"
//#include "cmp_BasePlayerComponent.h"
#include "VoidRun.h"
#include "ecm.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
std::shared_ptr<BaseEnemyComponent> enemyInfo;
std::vector<std::shared_ptr<BasePlayerComponent>> playerInfo;

//Clock clock;

BasePlayerComponent::BasePlayerComponent(Entity* p, float health, float strength, float dex, float experience)
	: _maxHealth{ health }, currentHealth{ health }, _strength{ strength }, _dexterity{ dex }, _experience{ experience }, Component(p) {}

void BasePlayerComponent::update(double dt) {
	//float Time = Clock.GetElapsedTime();
	//Clock.Reset();

	if (isTurn)
	{
		if (checkEnemyStatus())
		{
			if (isFinishedTurn != true)
			{
				if (Keyboard::isKeyPressed(Keyboard::Q))
				{
					cout << "Player Attacks!";
					attack(_strength);
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
		else {
			expGet();
		}
	}
}

void BasePlayerComponent::updateEnemy(std::shared_ptr<BaseEnemyComponent> e)
{
	currentEnemy = e;
}

bool BasePlayerComponent::checkEnemyStatus(){
	if (currentEnemy->getParent().is_forDeletion()) {
		return false;
	}
	else {
		return true;
	}
}

void BasePlayerComponent::expGet() {
	if (expGained == false) {
		cout << "The enemy has become die.";
		_experience += currentEnemy->expReward;
		expGained = true;
	}
}

void BasePlayerComponent::attack(float damage)
{
	currentEnemy->TakeDamage(damage);
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

float BasePlayerComponent::getCurrentHealth() {
	return currentHealth;
}

int BasePlayerComponent::getDexterity() {
	return _dexterity;
}

int BasePlayerComponent::getExperience() {
	return _experience;
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

void BasePlayerComponent::addStats(int strength, int health, int dex)
{
	_strength += strength;
	_maxHealth += health;
	if (currentHealth + health >= _maxHealth)
	{
		currentHealth = _maxHealth;
	}
	else
	{
		currentHealth += health;
	}
	_dexterity += dex;
}

void BasePlayerComponent::setExperience(int experience)
{
	_experience = experience;
}

void BasePlayerComponent::takeDamage(float dmgRecieved)
{
	currentHealth -= dmgRecieved;
	if (currentHealth <= 0)
	{
		currentHealth = 0;
		_parent->setAlive(false);
	}
}