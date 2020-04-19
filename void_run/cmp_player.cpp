#include "Game.h"
#include "cmp_player.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
std::shared_ptr<BaseEnemyComponent> enemyInfo;
std::vector<std::shared_ptr<BasePlayerComponent>> playerInfo;

//Clock clock;

BasePlayerComponent::BasePlayerComponent(Entity* p, int health, float strength, float dex,
	float experience, int actionPoints, CombatUI ui, GameUI *gui)
	: _maxHealth{ health }, currentHealth{ health }, _strength{ strength }, _dexterity{ dex }, 
	_experience{ experience }, _actionPointsMax{ actionPoints }, combatUI{ ui }, gameUI{ *gui }, Component(p) {}

void BasePlayerComponent::update(double dt) {
	//float Time = Clock.GetElapsedTime();
	//Clock.Reset();

	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);

	if (isTurn && !isPaused)
	{
		if (checkEnemyStatus())
		{
			if (isFinishedTurn != true)
			{
				if (Keyboard::isKeyPressed(Keyboard::Q) && CheckAP(baseAttackCost))
				{
					actionPoints -= 1;
					gameUI.useAP(1);
					cout << "Player Attacks!";
					attack(_strength, _dexterity);
					EndTurn();
				}
				if (Keyboard::isKeyPressed(Keyboard::W) && CheckAP(healCost))
				{
					actionPoints -= 2;
					gameUI.useAP(2);
					cout << "Player Heals!";
					heal(5);
					EndTurn();
				}

				if (Mouse::isButtonPressed(Mouse::Left) && combatUI.getAttackBox().contains(cursPos) && CheckAP(baseAttackCost))
				{
					actionPoints -= 1;
					gameUI.useAP(1);
					cout << "Player Attacks!";
					attack(_strength, _dexterity);
					EndTurn();
				}

				abilityManager->combatCheck();
			//	gameScene.combatUI.turnUpdate();
			}
		}
		else {
			expGet();
		}
	}

	if (combatUI.getAttackBox().contains(cursPos))
	{
		gameUI.descText.setString("ATTACK ENEMY\nDamage = " + std::to_string(_strength));
		gameUI.descText.setPosition(sf::Vector2f(combatUI.getAttackBox().getPosition().x,
			combatUI.getAttackBox().getPosition().y - 75.0f));
	}
	else
	{
		gameUI.descText.setString("");
	}
}

bool BasePlayerComponent::CheckAP(int ap)
{
	if (actionPoints >= ap)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BasePlayerComponent::SpendAP(int ap)
{
	actionPoints -= ap;
	gameUI.useAP(ap);
}

void BasePlayerComponent::gainAP(int amount)
{
	int temp = actionPoints += amount;
	if (temp > _actionPointsMax)
	{
		actionPoints = _actionPointsMax;
	}
	else
	{
		actionPoints = temp;
	}
	gameUI.gainAP(amount);
}

void BasePlayerComponent::load()
{
	auto am = _parent->GetCompatibleComponent<AbilityManager>();
	abilityManager = am[0];
	actionPoints = _actionPointsMax;
	baseAttackCost = 1;
	mediumAttackCost = 3;
	heavyAttackCost = 5;
	healCost = 3;
	meditateCost = 0;
	fleeCost = 1;
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

void BasePlayerComponent::attack(float str, float dex)
{
	if (calculateHit(dex))
	{
		currentEnemy->TakeDamage(str);
	}
	else {
		gameScene.UpdateTextBox("You missed!");
	}
}

bool BasePlayerComponent::calculateHit(float dex)
{
	int chanceToHit = (80 + (dex - (currentEnemy->getDexterity()))); //Calculates if the player can hit
	int willTheyHitOhNo = rand() % 100;
	if (willTheyHitOhNo <= chanceToHit)
	{
		return true;
	}
	else {
		return false;
	}
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