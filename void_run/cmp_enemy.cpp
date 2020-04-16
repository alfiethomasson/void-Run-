#include "cmp_enemy.h"
#include "cmp_player.h"
#include "VoidRun.h"
#include "ecm.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
//std::vector<std::shared_ptr<EntityInfo>> enemyInfo;
//std::vector<std::shared_ptr<EntityInfo>> playerInfo;

//bool playerTurn = true;
//Clock clock;

//BasePlayerComponent::BasePlayerComponent(Entity* p, float health, float strength, float dex, float experience)
//	: _maxHealth{ health }, currentHealth{ health }, _strength{ strength }, _dexterity{ dex }, _experience{ experience }, Component(p) {}

BaseEnemyComponent::BaseEnemyComponent(Entity* p, float health, float strength, float dex, float expReward)
	: enemyDamage(3.0f), _maxHealth{ health }, currentHealth{ health }, _strength{ strength }, _dexterity{ dex }, expReward{ expReward }, Component(p) {}

void BaseEnemyComponent::update(double dt) {
	//float Time = Clock.GetElapsedTime();
	//Clock.Reset();
	//if (isTurn && isFinishedTurn != true)
	//{
	//	int enemyAI = rand() % 2; //Random number from 0-1. 0 is attack, 1 is pass.
	//	if (enemyAI == 0) {
	//		cout << "The enemy attacks!";
	//		attackEnemy(enemyDamage);
	//		EndTurn();
	//	}
	//	else if (enemyAI == 1) {
	//		cout << "The enemy passes its turn!";
	//		EndTurn();
	//	}
	//}
}

void BaseEnemyComponent::updateEnemy(std::shared_ptr<BasePlayerComponent> player)
{
	currentEnemy = player;
}

void BaseEnemyComponent::attackEnemy(float damage)
{
	std::cout << "Player assigned to enemy = " << "\n";
	currentEnemy->takeDamage(damage);
}

void BaseEnemyComponent::EndTurn()
{
	cout << "Enemy Turn Ends!";
	isFinishedTurn = true;
}

void BaseEnemyComponent::TakeDamage(float damage)
{
	currentHealth -= damage;
	if (currentHealth <= 0)
	{
		currentHealth = 0;
		_parent->setForDelete();
		EndTurn();
	}
}

int BaseEnemyComponent::getStrength() {
	return _strength;
}

int BaseEnemyComponent::getMaxHealth() {
	return _maxHealth;
}

int BaseEnemyComponent::getCurrentHealth() {
	return currentHealth;
}

int BaseEnemyComponent::getDexterity() {
	return _dexterity;
}

void BaseEnemyComponent::setStrength(int strength) {
	_strength = strength;
}

void BaseEnemyComponent::setMaxHealth(int maxHealth) {
	_maxHealth = maxHealth;
}

void BaseEnemyComponent::setCurrentHealth(int health) {
	currentHealth = health;
}

void BaseEnemyComponent::setDexterity(int dexterity)
{
	_dexterity = dexterity;
}