#pragma once
#include "ecm.h"
#include "cmp_player.h"
#include "AlienSprites.h"
#include <SFML/Audio.hpp>

class BasePlayerComponent;

class BaseEnemyComponent : public Component {
protected:
	float enemyDamage;
	std::shared_ptr<BasePlayerComponent> currentEnemy;
	std::shared_ptr<SpriteComponent> spriteManager;
	float _strength;
	float _dexterity;
	float _maxHealth;
	float currentHealth;
	bool inAttack;
	int turnCounter;

	sf::Clock animClock;

	int healthSize;
	//sf::RectangleShape healthBar;
	std::vector<sf::RectangleShape> hpbars;
	int barheight;
	sf::Text healthText;

	sf::Sound sound;

public:
	bool isTurn;
	bool isFinishedTurn;
	float expReward;
	int specialMove;

	BaseEnemyComponent(Entity* p, float health, float strength, float dex, float expReward, int specialMove);
	BaseEnemyComponent() = delete;

	void render() override;
	void update(double dt) override;
	void updateEnemy(std::shared_ptr<BasePlayerComponent> player);
	virtual void load();

	void TakeDamage(float damage);
	bool calculateHit(float dex);
	void makeHPBar();

	bool attackEnemy(float str, float dex, std::string soundName);
	void heal(float healamount);
	void EndTurn();

	int getStrength();
	int getMaxHealth();
	int getDexterity();
	int getCurrentHealth();
	std::shared_ptr<SpriteComponent> getSprite();

	void setStrength(int strength);
	void setMaxHealth(int maxHealth);
	void setDexterity(int dexterity);
	void setCurrentHealth(int health);

	void addStats(int strength, int maxhealth, int dexterity);
};