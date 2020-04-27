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

BasePlayerComponent::BasePlayerComponent(Entity* p, float maxhealth, float currenthealth, float strength, float dex,
	float experience, int level, int actionPoints, CombatUI *ui, GameUI *gui)
	: _maxHealth{ maxhealth }, currentHealth{ currenthealth }, _strength{ strength }, _dexterity{ dex }, 
	_experience{ experience }, level{ level }, _actionPointsMax{ actionPoints }, combatUI{ *ui }, gameUI{ *gui }, Component(p) {}

void BasePlayerComponent::render() //Renderer function
{
	Renderer::queue(&healthText); //Queue all their stats to be displayed
	Renderer::queue(&StrengthText);
	Renderer::queue(&HPText);
	Renderer::queue(&DexterityText);
	Renderer::queue(&EXPText);
	Renderer::queue(&LevelText);
	for (auto& b : hpbars) //Loop in case they have lots of health, to display multiple health bars
	{
		Renderer::queue(&b);
	}
}

void BasePlayerComponent::update(double dt) {

	healthSize = currentHealth; //Health bars based on current health
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));

	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow()); //Get the mouse's position
	sf::Vector2f cursPos = sf::Vector2f(tempPos);
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	if (isTurn && !isPaused) //If it's the player's turn...
	{
		if (checkEnemyStatus() && getCurrentHealth() != 0) //...and both people are alive...
		{
			if (isFinishedTurn != true) //...and they haven't finished their turn...
			{
				if (Keyboard::isKeyPressed(attackKey) && CheckAP(baseAttackCost)) //They can attack!
				{
					attack(_strength, _dexterity, "Attack");
				}
				if (Keyboard::isKeyPressed(healKey) && CheckAP(healCost)) //They can heal!
				{
					heal(_dexterity, true);
				}
				if (Keyboard::isKeyPressed(rechargeKey) && CheckAP(rechargeCost)) //They can charge AP!
				{
					recharge(6);
				}
				if (Keyboard::isKeyPressed(runKey) && CheckAP(runCost)) //They can try to run!
				{
					run();
				}

				if (Mouse::isButtonPressed(Mouse::Left)) //They can do the same as above, but by clicking the buttons
				{
					if (combatUI.getAttackBox().contains(cursPos) && CheckAP(baseAttackCost))
					{
						attack(_strength, _dexterity, "Attack");
					}
					if (combatUI.getHealBox().contains(cursPos) && CheckAP(healCost))
					{
						heal(_dexterity, true);
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

				abilityManager->combatCheck(cursPos);
			}
		}
	}
}

void BasePlayerComponent::StartTurn() //Start their turn
{
	isTurn = true; //Note their turn
	gainAP(1); //Gain 1AP per turn
	abilityManager->StartTurnCheck();
}

void BasePlayerComponent::makeHPBar() //HP Bar creation
{
	sf::RectangleShape healthBar; //Initialise the healthbar
	healthBar.setPosition(300.0f, 130.0f + barheight);
	if (hpbars.size() != 0) //If they have a lot of health..
	{
		int barvalue = currentHealth - (150 * hpbars.size()); //..split it into multiple bars of 150
		if (barvalue > 150)
		{
			barvalue = 150;
		}
		barvalue = std::abs(barvalue);
		healthBar.setSize(sf::Vector2f(barvalue * 1.5, 20.0f));
		healthBar.setFillColor(sf::Color(220, 20, 60, 255));
		hpbars.push_back(healthBar);
	}
	else //Bars of 150HP, layered on top of each other
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
	barheight += -30.0f; //Each both is 30 higher than the last
}

bool BasePlayerComponent::CheckAP(int ap) //Function to get AP, to test if they can use an ability
{
	if (actionPoints >= ap)
	{
		return true;
	}
	else //If their action points don't beat the number input, they can't afford the ability in question
	{
		return false;
	}
}

void BasePlayerComponent::SpendAP(int ap) //Function to use AP
{
	actionPoints -= ap;
	gameUI.useAP(ap);
}

void BasePlayerComponent::gainAP(int amount) //Function to regain AP
{
	std::cout << "Currenet AP AMOUNT " << actionPoints << "\n";
	std::cout << "Should gain AP Amount: " << amount << "\n";
	int temp = actionPoints + amount;
	if (temp > _actionPointsMax) //Don't go above their max AP
	{
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
	auto am = _parent->GetCompatibleComponent<AbilityManager>(); //Ability Manager
	abilityManager = am[0];
	auto sm = _parent->GetCompatibleComponent <SpriteComponent>(); //Sprite Component for player
	spriteManager = sm[0];
	actionPoints = _actionPointsMax; //Initialise costs of different attacks
	baseAttackCost = 1;
	healCost = 3;
	rechargeCost = 0;
	runCost = 5;

	barheight = 0;
	std::cout << "making bar, ceiling value = " << std::ceil(currentHealth / 150) << "\n"; 
	while (std::ceil(currentHealth / 150) > hpbars.size()) //Multiple bars if HP is high
	{
		makeHPBar(); //Create the health bar
	}

	healthText.setFont(Engine::tm.getFont()); //Create, position, and colour the text to display player's Health above them
	healthText.setCharacterSize(25);
	healthText.setString(std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth));
	healthText.setPosition(70.0f, 120.0f);
	healthText.setFillColor(sf::Color(220, 20, 60, 255));

	HPText.setFont(Engine::tm.getFont()); //Create, position, and colour the text to display the player's Health in the bottom left
	HPText.setCharacterSize(30);
	HPText.setFillColor(sf::Color(220, 20, 60, 255));
	HPText.setPosition(sf::Vector2f(300.0f, 800.0f));

	StrengthText.setFont(Engine::tm.getFont()); //Create, position, and colour the text to display the player's Strength stat
	StrengthText.setCharacterSize(30);
	StrengthText.setFillColor(sf::Color(0, 0, 205, 255));
	StrengthText.setPosition(sf::Vector2f(300.0f, 850.0f));

	DexterityText.setFont(Engine::tm.getFont()); //Create, position, and colour the text to display the player's Dexterity stat
	DexterityText.setCharacterSize(30);
	DexterityText.setFillColor(sf::Color(0, 255, 127, 255));
	DexterityText.setPosition(sf::Vector2f(300.0f, 900.0f));

	EXPText.setFont(Engine::tm.getFont()); //Create, position, and colour the text to display the player's Exp
	EXPText.setCharacterSize(30);
	EXPText.setFillColor(sf::Color(204, 204, 0, 255));
	EXPText.setPosition(sf::Vector2f(300.0f, 950.0f));

	LevelText.setFont(Engine::tm.getFont()); //Create, position, and colour the text to display the player's level
	LevelText.setCharacterSize(30);
	LevelText.setFillColor(sf::Color(255, 255, 0, 255));
	LevelText.setPosition(sf::Vector2f(300.0f, 1000.0f));

	UpdateStats(); //Update their stats at the end
}

void BasePlayerComponent::updateEnemy(std::shared_ptr<BaseEnemyComponent> e) //Get the new enemy when they enter a combat room
{
	currentEnemy = e;
	runChance = calcRunChance();
	abilityManager->resetAbility();
	spriteManager->RemoveAllIcons();
}

bool BasePlayerComponent::checkEnemyStatus(){ //Check if the enemy is about to be deleted
	if (currentEnemy->getParent().is_forDeletion()) {
		return false;
	}
	else {
		return true;
	}
}

void BasePlayerComponent::expGet() { //Add experience to the player, based on the enemy's exp worth
	if (expGained == false) {
		cout << "The enemy has died.";
		_experience += currentEnemy->expReward; //Add exp to the player
		expGained = true; //Note it's been added so it doesn't happen multiple times
	}
}

bool BasePlayerComponent::checkLevelUp () { //Level up function
	if (_experience >= 30 && level < 5) { //Levels up on 30exp, cannot level up past 5
		_experience -= 30;
		level++;
		return true;
	}
	else {
		return false;
	}
}

<<<<<<< Updated upstream
void BasePlayerComponent::attack(float str, float dex, std::string soundName)
=======
void BasePlayerComponent::attack(float str, float dex) //Attack function!
>>>>>>> Stashed changes
{
	SpendAP(baseAttackCost); //Attack costs AP
	cout << "Player Attacks!";
	if (calculateHit(dex)) //If they hit
	{
<<<<<<< Updated upstream
		currentEnemy->TakeDamage(str);
		gameUI.playSound("Attack", 100);
		spriteManager->playAttack();
		gameScene.UpdateTextBox("You shoot the enemy!");
=======
		currentEnemy->TakeDamage(str); //Damage enemy
		gameUI.playSound("Attack", 30); //Play the sound
		spriteManager->playAttack(); //Play the animation
		gameScene.UpdateTextBox("You shoot the enemy!"); //Show a pop up
>>>>>>> Stashed changes
	}
	else {
		gameScene.UpdateTextBox("You missed!"); //If they don't hit, tell them
	}
	EndTurn(); //End Turn function
}

bool BasePlayerComponent::calculateHit(float dex)
{
	int chanceToHit = (80 + (dex - (currentEnemy->getDexterity()))); //The chance they hit, 80 + their Dex - Enemy Dex
	int willTheyHitOhNo = rand() % 100; //Random number from 0-99
	if (willTheyHitOhNo <= chanceToHit) //If the random number beats the % to hit, they're good
	{
		return true;
	}
	else { //Otherwise, it misses
		return false;
	}
}

void BasePlayerComponent::heal(float healBy, bool endturn) //Heal function
{
	if (endturn)
	{
		SpendAP(healCost); //Healing costs AP
		gameUI.playSound("Heal", 30); //Play sound
	}
	cout << "Player Heals!";
	int tempHealth = currentHealth + healBy; //Increase their health
	gameUI.playSound("Heal", 30);
	gameScene.UpdateTextBox("You heal.");
	if (tempHealth > _maxHealth) //If they would overheal, set it to their max HP
	{
		currentHealth = _maxHealth;
	}
	else
	{
		currentHealth += healBy; //Otherwise, just heal normally
	}
	if (std::ceil(currentHealth / 150) > hpbars.size()) //Recreate health bar
	{
		makeHPBar();
	}
	int minusvalue = currentHealth - (150 * hpbars.size()); //If there's been a change of a factor of 150, remake the bars too
	int barvalue = 150 - (abs(minusvalue));
	hpbars.back().setSize(sf::Vector2f(barvalue * 1.5, 20.0f));
	if (endturn)
	{
		EndTurn();
	}
}

void BasePlayerComponent::recharge(int amount) //Recharge AP
{
	cout << "Player Recharges!";
	gameUI.playSound("Recharge", 30); //Play sound
	SpendAP(rechargeCost); //Recharge costs AP for consistency
	gameScene.UpdateTextBox("You recharge your equipment.");
	gainAP(amount); //Give the player AP equal to the number taken in
	EndTurn();
}

void BasePlayerComponent::run() //Run from combat
{
	SpendAP(runCost); //Running costs AP
	srand(time(0));
	int random = rand() % 100; //% chance to run
	if (random < runChance)
	{
		currentEnemy->setfordeletion(); //If they roll below the random chance, the enemy is gone...
		gameUI.playSound("Run", 30);
		spriteManager->playRun(); //...And they escape
		gameScene.UpdateTextBox("You flee!");
	}
	else
	{
		cout << "Player runs! FAILURE\n"; //Otherwise, they fail to escape
		gameScene.UpdateTextBox("You fail to flee.");
	}
	EndTurn(); //Either way their turn ends
}

int BasePlayerComponent::calcRunChance() //Run chance calculation
{
	srand(time(0));
	int random = rand() % 100; //Random number from 0-99
	random = random + _dexterity - currentEnemy->getDexterity(); //Calculate dexterities in
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

void BasePlayerComponent::EndTurn() //End turn function
{
	cout << "Player Turn Ends!";
	isFinishedTurn = true; //The turn is over!
}

std::shared_ptr<BaseEnemyComponent> BasePlayerComponent::getEnemy() //Getter for enemy
{
	return currentEnemy;
}

std::shared_ptr<AbilityManager> BasePlayerComponent::getAbilityManager() //Getter for abilityManager
{
	return abilityManager;
}

std::shared_ptr<SpriteComponent> BasePlayerComponent::getSpriteComponent() //Getter for spriteComponent
{
	return spriteManager;
}

int BasePlayerComponent::getRunChance() //Getter for run chance
{
	return runChance;
}

int BasePlayerComponent::getStrength() { //Getter for strength
	return _strength;
}

int BasePlayerComponent::getMaxHealth() { //Getter for max HP
	return _maxHealth;
}

int BasePlayerComponent::getCurrentHealth() { //Getter for current HP
	return currentHealth;
}

int BasePlayerComponent::getDexterity() { //Getter for dexterity
	return _dexterity;
}

int BasePlayerComponent::getExperience() { //Getter for exp
	return _experience;
}

void BasePlayerComponent::setStrength(int strength) { //Setter for strength
	_strength = strength;
}

void BasePlayerComponent::setMaxHealth(int maxHealth) { //Setter for max HP
	_maxHealth = maxHealth;
}

void BasePlayerComponent::setCurrentHealth(int health) { //Setter for current HP
	currentHealth = health;
}

void BasePlayerComponent::setDexterity(int dexterity) //Setter for dexterity
{
	_dexterity = dexterity;
}

void BasePlayerComponent::addAbility(std::shared_ptr<SpecialAbility> sp) //Add an ability
{
	abilityManager->addAbility(sp); //Add the ability from the abilityManager
	combatUI.addSpecial(sp->getTexName(), sp); //Add it to the UI
}

void BasePlayerComponent::addStats(int strength, int health, int dex) //Stat improvement function
{
	_strength += strength; //Strength increases by first number taken in
	_maxHealth += health; //Health increases by second number taken in
	if (currentHealth + health >= _maxHealth) //Increase both normal HP and max HP
	{
		currentHealth = _maxHealth;
	}
	else
	{
		currentHealth += health;
	}
	_dexterity += dex; //Dexterity increases by third number taken in
	UpdateStats(); //Update the stats appearances
}

void BasePlayerComponent::UpdateStats() //Stat update
{
	HPText.setString("HP: " + std::to_string((int)currentHealth) + " / " + std::to_string((int)_maxHealth)); //Update all of the visible stat indicators
	StrengthText.setString("Strength:  " + std::to_string((int)_strength));
	DexterityText.setString("Dexterity:  " + std::to_string((int)_dexterity));
	EXPText.setString("XP: " + std::to_string((int)_experience) + " / " + std::to_string(30));
	LevelText.setString("Level: " + std::to_string(level));
}

void BasePlayerComponent::setExperience(int experience) //Setter for exp
{
	_experience = experience;
}

void BasePlayerComponent::takeDamage(float dmgRecieved) //Player takes damage
{
	currentHealth -= dmgRecieved; //Lower current  HP
	gameUI.playSound("PlayerHit", 60); //Play sound
	if (currentHealth <= 0) //If their HP goes to 0 or lower
	{
		currentHealth = 0; //Set HP to 0
		hpbars.clear(); //Wipe their HP
		_parent->setAlive(false); //Set them to dead
		gameScene.UpdateTextBox("GAME OVER."); //Display a game over
		spriteManager->playDie(); //Death animation
	}
	else 
	{
		spriteManager->playHit(); //If they don't die, show a hurt animation
		if (std::ceil(currentHealth / 150) < hpbars.size()) //Then recreate their HP
		{
			hpbars.pop_back();
			barheight += 30.0f;
		}
		int minusvalue = currentHealth - (150 * hpbars.size()); //Remake the healthbars
		int barvalue = 150 - (abs(minusvalue));
		hpbars.back().setSize(sf::Vector2f(barvalue * 1.5, 20.0f));
	}
}

void BasePlayerComponent::setRunChance(int run) //Setter for runChance
{
	runChance = run;
}