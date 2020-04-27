#include "cmp_enemy.h"
#include "cmp_player.h"
#include "VoidRun.h"
#include "ecm.h"
#include <string>
#include <iostream>
#include "Game.h"

using namespace sf; //Using namespaces
using namespace std;

int animDelay = 1.0f; //Delay for animations

BaseEnemyComponent::BaseEnemyComponent(Entity* p, float health, float strength, float dex, float expReward, int specialMove)
	: enemyDamage(3.0f), _maxHealth{ health }, currentHealth{ health }, _strength{ strength }, _dexterity{ dex }, expReward{ expReward }, specialMove{ specialMove }, Component(p) {}

void BaseEnemyComponent::update(double dt) //Always update their HP text 
{
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));
}

void BaseEnemyComponent::load()
{
	barheight = 0; //Bar height defaults to 0
	while (std::ceil(currentHealth / 150) > hpbars.size()) //Multiple bars if over 150
	{
		std::cout << "current hp / 150 " << std::to_string(currentHealth / 150) << "\n";
		std::cout << "making bar, ceiling value = " << std::ceil(currentHealth / 150) << "\n";
		makeHPBar();
	}
	healthText.setFont(Engine::tm.getFont()); //Display the health text
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));
	healthText.setCharacterSize(30);
	healthText.setPosition(1600.0f, 120.0f);
	healthText.setFillColor(sf::Color(220, 20, 60, 255));

	turnCounter = 1; //Turn counter for certain unique abiltiies
}

void BaseEnemyComponent::makeHPBar() //Make the health bar
{
	sf::RectangleShape healthBar;
	healthBar.setPosition(1550.0f, 130.0f + barheight);
	if (hpbars.size() != 0)
	{
		int barvalue = currentHealth - (150 * hpbars.size());
		if (barvalue > 150) //If a bar has more than 150, cap it at 150
		{
			barvalue = 150;
		}
		barvalue = std::abs(barvalue);
		healthBar.setSize(sf::Vector2f(-barvalue * 1.5, 20.0f));
		healthBar.setFillColor(sf::Color(220, 20, 60, 255));
		hpbars.push_back(healthBar);
	}
	else
	{
		if (currentHealth > 150) //If they have more than 150 HP, multiple bars
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
	for (auto &b : hpbars) //Render all the health bars
	{
		Renderer::queue(&b);
	}
	Renderer::queue(&healthText);
}

void BaseEnemyComponent::updateEnemy(std::shared_ptr<BasePlayerComponent> player) //Update the player for the enemy
{
	currentEnemy = player;
}

bool BaseEnemyComponent::attackEnemy(float str, float dex, std::string soundName) // attack function
{
	if (calculateHit(dex)) //Run a hit calculation
	{
		if (soundName != "")
		{
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.setBuffer(Engine::tm.getSound(soundName));
			sound.play();
		}
		animClock.restart();
		spriteManager->playAttack();
		currentEnemy->takeDamage(str);
		return true;
	}
	else {
		gameScene.UpdateTextBox("The enemy misses!");
		return false;
	}
}

void BaseEnemyComponent::heal(float healamount) //Heal calculation
{
	cout << "Enemy Heals!\n";
	int tempHealth = currentHealth + healamount; //Increase HP
	if (tempHealth > _maxHealth)
	{
		currentHealth = _maxHealth; //If they overheal, then don't let them
	}
	else
	{
		currentHealth += healamount; //Otherwise just increase it normally
	}

	if (std::ceil(currentHealth / 150) > hpbars.size()) //Make the HP bars different sizes
	{
		makeHPBar();
	}
	int minusvalue = currentHealth - (150 * hpbars.size()); //Health bars are 150HP long
	int barvalue = 150 - (abs(minusvalue));
	hpbars.back().setSize(sf::Vector2f(-barvalue * 1.5, 20.0f));

}

bool BaseEnemyComponent::calculateHit(float dex) //Calculate hit chance
{
	int chanceToHit = (80 + (dex - (currentEnemy->getDexterity()))); //Base chance of 80% + Dex - Player Dex
	int willTheyHitOhNo = rand() % 100; //Random number to determine if they hit
	if (willTheyHitOhNo <= chanceToHit)
	{
		return true; //If they do, return true
	}
	else {
		return false; //Otherwise, return false
	}
}

void BaseEnemyComponent::EndTurn() //End Turn function
{
	cout << "Enemy Turn Ends!";
	isFinishedTurn = true; //End their turn
	turnCounter++; //Increase turn counter
}

void BaseEnemyComponent::TakeDamage(float damage) //Enemies can take damage
{
	currentHealth -= damage; //Lower HP
	if (currentHealth <= 0) //If their HP goes to or below 0
	{
		currentHealth = 0; //Set their HP to 0 so it isn't at -3 or whatever
		spriteManager->playDie(); //Kill them
		hpbars.clear(); //Remove their HP
		EndTurn();
	}
	else //If they live...
	{
		spriteManager->playHit(); //Play hurt animation
		if (std::ceil(currentHealth / 150) < hpbars.size()) //Reset their healthbar
		{
			hpbars.pop_back();
			barheight += 30.0f;
		}
		int minusvalue = currentHealth - (150 * hpbars.size());
		int barvalue = 150 - (abs(minusvalue));
		hpbars.back().setSize(sf::Vector2f(-barvalue * 1.5, 20.0f));
	}
}

std::shared_ptr<SpriteComponent> BaseEnemyComponent::getSprite() //Getter for sprite
{
	return spriteManager;
}

int BaseEnemyComponent::getStrength() { //Getter for strength
	return _strength;
}

int BaseEnemyComponent::getMaxHealth() { //Getter for max HP
	return _maxHealth;
}

int BaseEnemyComponent::getCurrentHealth() { //getter for Current Health
	return currentHealth;
}

int BaseEnemyComponent::getDexterity() { //Getter for Dexterity
	return _dexterity;
}

void BaseEnemyComponent::setStrength(int strength) { //Setter for Strength
	_strength = strength;
}

void BaseEnemyComponent::setMaxHealth(int maxHealth) { //Setter for Max HP
	_maxHealth = maxHealth;
}

void BaseEnemyComponent::setCurrentHealth(int health) { //Setter for current HP
	currentHealth = health;
}

void BaseEnemyComponent::setDexterity(int dexterity) //Setter for Dexterity
{
	_dexterity = dexterity;
}

void BaseEnemyComponent::addStats(int strength, int maxhealth, int dexterity) //Add stats to enemy
{
	_strength += strength; //Increase Strength...
	_maxHealth += maxhealth; //...maxHP
	currentHealth += maxhealth; //(Increase current HP when this happens)
	_dexterity += dexterity; //...or dex.
}