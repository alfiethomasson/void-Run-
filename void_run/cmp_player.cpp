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

BasePlayerComponent::BasePlayerComponent(Entity* p, float maxhealth, float currenthealth, float strength, float dex,
	float experience, int actionPoints, CombatUI *ui, GameUI *gui)
	: _maxHealth{ maxhealth }, currentHealth{ currenthealth }, _strength{ strength }, _dexterity{ dex }, 
	_experience{ experience }, _actionPointsMax{ actionPoints }, combatUI{ *ui }, gameUI{ *gui }, Component(p) {}

void BasePlayerComponent::render()
{
	Renderer::queue(&healthText);
	Renderer::queue(&StrengthText);
	Renderer::queue(&HPText);
	Renderer::queue(&DexterityText);
	for (auto& b : hpbars)
	{
		Renderer::queue(&b);
	}
}

void BasePlayerComponent::update(double dt) {

	healthSize = currentHealth;
	//healthBar.setSize(sf::Vector2f(healthSize * 1.5, 20.0f));
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));

	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);

	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

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
			//std::cout << "HEY";
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

void BasePlayerComponent::makeHPBar()
{
	sf::RectangleShape healthBar;
	healthBar.setPosition(300.0f, 130.0f + barheight);
	if (hpbars.size() != 0)
	{
		int barvalue = currentHealth - (150 * hpbars.size());
		if (barvalue > 150)
		{
			barvalue = 150;
		}
		barvalue = std::abs(barvalue);
		healthBar.setSize(sf::Vector2f(barvalue * 1.5, 20.0f));
		healthBar.setFillColor(sf::Color(220, 20, 60, 255));
		hpbars.push_back(healthBar);
	}
	else
	{
		if (currentHealth > 150)
		{
			healthBar.setSize(sf::Vector2f(150 * 1.5, 20.0f));
			healthBar.setFillColor(sf::Color(220, 20, 60, 255));
			hpbars.push_back(healthBar);
		}
		else
		{
			healthBar.setSize(sf::Vector2f(currentHealth * 1.5, 20.0f));
			healthBar.setFillColor(sf::Color(220, 20, 60, 255));
			hpbars.push_back(healthBar);
		}
	}
	barheight += -30.0f;
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

	barheight = 0;
	std::cout << "making bar, ceiling value = " << std::ceil(currentHealth / 150) << "\n"; 
	while (std::ceil(currentHealth / 150) > hpbars.size())
	{
	/*	std::cout << "current hp / 150 " << std::to_string(currentHealth / 150) << "\n";
		std::cout << "making bar, ceiling value = " << std::ceil(currentHealth / 150) << "\n";*/
		makeHPBar();
	}

	healthText.setFont(Engine::tm.getFont());
	healthText.setCharacterSize(25);
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));
	healthText.setPosition(70.0f, 120.0f);
	healthText.setFillColor(sf::Color(220, 20, 60, 255));

	HPText.setFont(Engine::tm.getFont());
	HPText.setCharacterSize(30);
	HPText.setFillColor(sf::Color(220, 20, 60, 255));
	HPText.setPosition(sf::Vector2f(300.0f, 850.0f));

	StrengthText.setFont(Engine::tm.getFont());
	StrengthText.setCharacterSize(30);
	StrengthText.setFillColor(sf::Color(0, 0, 205, 255));
	StrengthText.setPosition(sf::Vector2f(300.0f, 900.0f));

	DexterityText.setFont(Engine::tm.getFont());
	DexterityText.setCharacterSize(30);
	DexterityText.setFillColor(sf::Color(0, 255, 127, 255));
	DexterityText.setPosition(sf::Vector2f(300.0f, 950.0f));

	UpdateStats();
}

void BasePlayerComponent::updateEnemy(std::shared_ptr<BaseEnemyComponent> e)
{
	currentEnemy = e;
//runChance = calcRunChance();
	runChance = 100;
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
		gameUI.playSound("Attack", 30);
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
	gameUI.playSound("Heal", 30);
	if (tempHealth > _maxHealth)
	{
		currentHealth = _maxHealth;
	}
	else
	{
		currentHealth += healBy;
	}
	if (std::ceil(currentHealth / 150) > hpbars.size())
	{
		makeHPBar();
	}
	int minusvalue = currentHealth - (150 * hpbars.size());
	int barvalue = 150 - (abs(minusvalue));
	hpbars.back().setSize(sf::Vector2f(barvalue * 1.5, 20.0f));
	EndTurn();
}

void BasePlayerComponent::recharge(int amount)
{
	cout << "Player Recharges!";
	gameUI.playSound("Recharge", 30);
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
		currentEnemy->setfordeletion();
		gameUI.playSound("Run", 30);
		spriteManager->playRun();
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
	UpdateStats();
}

void BasePlayerComponent::UpdateStats()
{
	HPText.setString("HP: " + std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));
	StrengthText.setString("Strength:  " + std::to_string((int)_strength));
	DexterityText.setString("Dexterity:  " + std::to_string((int)_dexterity));
}

void BasePlayerComponent::setExperience(int experience)
{
	_experience = experience;
}

void BasePlayerComponent::takeDamage(float dmgRecieved)
{
	currentHealth -= dmgRecieved;
	gameUI.playSound("PlayerHit", 60);
	if (currentHealth <= 0)
	{
		currentHealth = 0;
		hpbars.clear();
		_parent->setAlive(false);
		gameScene.UpdateTextBox("You fucking idiot, you're dead.");
		spriteManager->playDie();
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
		hpbars.back().setSize(sf::Vector2f(barvalue * 1.5, 20.0f));
	}
}

void BasePlayerComponent::setRunChance(int run)
{
	runChance = run;
}