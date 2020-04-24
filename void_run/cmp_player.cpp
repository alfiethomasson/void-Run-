#include "Game.h"
#include "cmp_player.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
std::shared_ptr<BaseEnemyComponent> enemyInfo;
std::vector<std::shared_ptr<BasePlayerComponent>> playerInfo;

#define GAMEX 1280
#define GAMEY 720

int level;

//Clock clock;

BasePlayerComponent::BasePlayerComponent(Entity* p, int health, float strength, float dex,
	float experience, int actionPoints, CombatUI *ui, GameUI *gui)
	: _maxHealth{ health }, currentHealth{ health }, _strength{ strength }, _dexterity{ dex }, 
	_experience{ experience }, _actionPointsMax{ actionPoints }, combatUI{ *ui }, gameUI{ *gui }, Component(p) {}

void BasePlayerComponent::render()
{
	Renderer::queue(&healthBar);
	Renderer::queue(&healthText);
}

void BasePlayerComponent::update(double dt) {

	healthSize = currentHealth;
	healthBar.setSize(sf::Vector2f(healthSize * 1.5, 20.0f));
	healthText.setString(std::to_string(currentHealth) + " / " + std::to_string(_maxHealth));

	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);

	if (isTurn && !isPaused)
	{
		if (checkEnemyStatus() && getCurrentHealth() != 0)
		{
			if (isFinishedTurn != true)
			{
				if (Keyboard::isKeyPressed(attackKey) && CheckAP(baseAttackCost))
				{
					attack(_strength, _dexterity);
				}
				if (Keyboard::isKeyPressed(healKey) && CheckAP(healCost))
				{
					heal(30);
				}
				if (Keyboard::isKeyPressed(rechargeKey) && CheckAP(rechargeCost))
				{
					recharge(6);
				}
				if (Keyboard::isKeyPressed(runKey) && CheckAP(runCost))
				{
					run();
				}

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (combatUI.getAttackBox().contains(cursPos) && CheckAP(baseAttackCost))
					{
						attack(_strength, _dexterity);
					}
					if (combatUI.getHealBox().contains(cursPos) && CheckAP(healCost))
					{
						heal(30);
					}
					if (combatUI.getRechargeBox().contains(cursPos) && CheckAP(rechargeCost))
					{
						recharge(6);
					}
					if (combatUI.getRunBox().contains(cursPos) && CheckAP(runCost))
					{
						run();
					}
				}

				abilityManager->combatCheck();
				//	gameScene.combatUI.turnUpdate();
			}
		}
	}

	if (combatUI.CheckBoxes(cursPos))
	{
		if (combatUI.getAttackBox().contains(cursPos))
		{
			gameScene.UpdateDesctext("ATTACK ENEMY\nDamage = " + std::to_string((int)_strength), sf::Vector2f(combatUI.getAttackBox().getPosition().x,
				combatUI.getAttackBox().getPosition().y - 75.0f));
		}
		if (combatUI.getHealBox().contains(cursPos))
		{
			gameScene.UpdateDesctext("HEAL\nAmount = " + std::to_string(30), sf::Vector2f(combatUI.getHealBox().getPosition().x,
				combatUI.getHealBox().getPosition().y - 75.0f));
		}
		if (combatUI.getRechargeBox().contains(cursPos))
		{
			gameScene.UpdateDesctext("RECHARGE ENERGY\nAmount = " + std::to_string(6), sf::Vector2f(combatUI.getRechargeBox().getPosition().x,
				combatUI.getRechargeBox().getPosition().y - 75.0f));

		}
		if (combatUI.getRunBox().contains(cursPos))
		{
			gameScene.UpdateDesctext("RUN FROM ENEMY\nChance = " + std::to_string(runChance), sf::Vector2f(combatUI.getRunBox().getPosition().x,
				combatUI.getRunBox().getPosition().y - 75.0f));
		}
	}
	else
	{
		gameScene.ResetDescText();
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
	std::cout << "Currenet AP AMOUNT " << actionPoints << "\n";
	std::cout << "Should gain AP Amount: " << amount << "\n";
	int temp = actionPoints + amount;
	if (temp > _actionPointsMax)
	{
	//	actionPoints = _actionPointsMax;
		gameUI.gainAP(_actionPointsMax - actionPoints);
		actionPoints = _actionPointsMax;
	}
	else
	{
		actionPoints = temp;
		gameUI.gainAP(amount);
	}
}

void BasePlayerComponent::load()
{
	level = 1;

	auto am = _parent->GetCompatibleComponent<AbilityManager>();
	abilityManager = am[0];
	auto sm = _parent->GetCompatibleComponent <SpriteComponent>();
	spriteManager = sm[0];
	actionPoints = _actionPointsMax;
	baseAttackCost = 1;
	mediumAttackCost = 3;
	heavyAttackCost = 5;
	healCost = 3;
	rechargeCost = 0;
	runCost = 5;

	healthBar.setPosition(300.0f, 50.0f);
	healthSize = _maxHealth;
	healthBar.setSize(sf::Vector2f(healthSize * 1.5, 20.0f));
	healthBar.setFillColor(sf::Color(220, 20, 60, 255));

	healthText.setFont(gameScene.tm.getFont());
	healthText.setCharacterSize(30);
	healthText.setString(currentHealth + " / " + _maxHealth);
	healthText.setPosition(200.0f, 40.0f);
	healthText.setFillColor(sf::Color(220, 20, 60, 255));
}

void BasePlayerComponent::updateEnemy(std::shared_ptr<BaseEnemyComponent> e)
{
	currentEnemy = e;
	runChance = calcRunChance();
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

bool BasePlayerComponent::checkLevelUp () {
	if (_experience >= 30 && level < 5) {
		_experience -= 30;
		level++;
		return true;
	}
	else {
		return false;
	}
}

void BasePlayerComponent::attack(float str, float dex)
{
	SpendAP(baseAttackCost);
	cout << "Player Attacks!";
	if (calculateHit(dex))
	{
		currentEnemy->TakeDamage(str);
		spriteManager->playAttack();
	}
	else {
		gameScene.UpdateTextBox("You missed!");
	}
	EndTurn();
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
	SpendAP(healCost);
	cout << "Player Heals!";
	int tempHealth = currentHealth + healBy;
	if (tempHealth > _maxHealth)
	{
		currentHealth = _maxHealth;
	}
	else
	{
		currentHealth += healBy;
	}
	EndTurn();
}

void BasePlayerComponent::recharge(int amount)
{
	cout << "Player Recharges!";
	SpendAP(rechargeCost);
	gainAP(amount);
	EndTurn();
}

void BasePlayerComponent::run()
{
	SpendAP(runCost);
	srand(time(0));
	int random = rand() % 100;
	if (random < runChance)
	{
		cout << "Player runs! SUCCESS  NEED TO IMPLEMENT STUFF PROPERLY HELLO DEVS!\n";
		currentEnemy->setfordeletion();
	}
	else
	{
		cout << "Player runs! FAILURE\n";
	}
	EndTurn();
}

int BasePlayerComponent::calcRunChance()
{
	srand(time(0));
	int random = rand() % 100;
	random = random + _dexterity - currentEnemy->getDexterity();
	if (random < 0)
	{
		random = 0;
	}
	if (random > 100)
	{
		random = 100;
	}
	return random;
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
		gameScene.UpdateTextBox("You fucking idiot, you're dead.");
		spriteManager->playDie();
	}
	else
	{
		spriteManager->playHit();
	}
}

void BasePlayerComponent::setRunChance(int run)
{
	runChance = run;
}