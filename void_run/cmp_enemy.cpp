#include "cmp_enemy.h"
#include "cmp_player.h"
#include "VoidRun.h"
#include "ecm.h"
#include <string>
#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;

int animDelay = 1.0f;

BaseEnemyComponent::BaseEnemyComponent(Entity* p, float health, float strength, float dex, float expReward, int specialMove)
	: enemyDamage(3.0f), _maxHealth{ health }, currentHealth{ health }, _strength{ strength }, _dexterity{ dex }, expReward{ expReward }, specialMove{ specialMove }, Component(p) {}

void BaseEnemyComponent::update(double dt) 
{
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));
}

void BaseEnemyComponent::load()
{
	barheight = 0;
	while (std::ceil(currentHealth / 150) > hpbars.size())
	{
		std::cout << "current hp / 150 " << std::to_string(currentHealth / 150) << "\n";
		std::cout << "making bar, ceiling value = " << std::ceil(currentHealth / 150) << "\n";
		makeHPBar();
	}
	healthText.setFont(gameScene.tm.getFont());
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));
	healthText.setCharacterSize(30);
	healthText.setPosition(1120.0f, 40.0f);
	healthText.setFillColor(sf::Color(220, 20, 60, 255));

	turnCounter = 1;
}

void BaseEnemyComponent::makeHPBar()
{
	sf::RectangleShape healthBar;
	healthBar.setPosition(1100.0f, 50.0f + barheight);
	if (hpbars.size() != 0)
	{
		int barvalue = currentHealth - (150 * hpbars.size());
		barvalue = std::abs(barvalue);
		healthBar.setSize(sf::Vector2f(-barvalue * 1.5, 20.0f));
		healthBar.setFillColor(sf::Color(220, 20, 60, 255));
		hpbars.push_back(healthBar);
	}
	else
	{
		if (currentHealth > 150)
		{
			healthBar.setSize(sf::Vector2f(-(150) * 1.5, 20.0f));
			healthBar.setFillColor(sf::Color(220, 20, 60, 255));
			hpbars.push_back(healthBar);
		}
		else
		{
			healthBar.setSize(sf::Vector2f(-currentHealth * 1.5, 20.0f));
			healthBar.setFillColor(sf::Color(220, 20, 60, 255));
			hpbars.push_back(healthBar);
		}
	}
	barheight += -30.0f;
}

void BaseEnemyComponent::render()
{
	for (auto &b : hpbars)
	{
		Renderer::queue(&b);
	}
	Renderer::queue(&healthText);
}

void BaseEnemyComponent::updateEnemy(std::shared_ptr<BasePlayerComponent> player)
{
	currentEnemy = player;
}

bool BaseEnemyComponent::attackEnemy(float str, float dex)
{
	if (calculateHit(dex))
	{
		animClock.restart();
		spriteManager->playAttack();
		currentEnemy->takeDamage(str);
		return true;
	}
	else {
		gameScene.UpdateTextBox("The stupid dumb idiot enemy missed!");
		return false;
	}
}

void BaseEnemyComponent::heal(float healamount)
{
	cout << "Enemy Heals!\n";
	int tempHealth = currentHealth + healamount;
	if (tempHealth > _maxHealth)
	{
		currentHealth = _maxHealth;
	}
	else
	{
		currentHealth += healamount;
	}

	if (std::ceil(currentHealth / 150) > hpbars.size())
	{
		makeHPBar();
	}
	int minusvalue = currentHealth - (150 * hpbars.size());
	int barvalue = 150 - (abs(minusvalue));
	hpbars.back().setSize(sf::Vector2f(-barvalue * 1.5, 20.0f));

}

bool BaseEnemyComponent::calculateHit(float dex)
{
	int chanceToHit = (80 + (dex - (currentEnemy->getDexterity()))); //Calculates if the enemy can hit
	int willTheyHitOhNo = rand() % 100;
	if (willTheyHitOhNo <= chanceToHit)
	{
		return true;
	}
	else {
		return false;
	}
}

void BaseEnemyComponent::EndTurn()
{
	cout << "Enemy Turn Ends!";
	isFinishedTurn = true;
	turnCounter++;
}

void BaseEnemyComponent::TakeDamage(float damage)
{
	currentHealth -= damage;
	if (currentHealth <= 0)
	{
		currentHealth = 0;
	//	_parent->setForDelete();
		spriteManager->playDie();
		hpbars.clear();
		EndTurn();
	}
	else
	{
		spriteManager->playHit();
		if (std::ceil(currentHealth / 150) < hpbars.size())
		{
			hpbars.pop_back();
			barheight += 30.0f;
		}
		int minusvalue = currentHealth - (150 * hpbars.size());
		int barvalue = 150 - (abs(minusvalue));
		hpbars.back().setSize(sf::Vector2f(-barvalue * 1.5, 20.0f));
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