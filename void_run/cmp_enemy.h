#pragma once
#include "ecm.h"
#include "cmp_player.h"
#include "AlienSprites.h"

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

	sf::Clock animClock;
public:
	bool isTurn;
	bool isFinishedTurn;
	float expReward;
	int specialMove;

	BaseEnemyComponent(Entity* p, float health, float strength, float dex, float expReward, int specialMove);
	BaseEnemyComponent() = delete;

	void render() override {}
	void update(double dt) override;
	void updateEnemy(std::shared_ptr<BasePlayerComponent> player);

	void TakeDamage(float damage);
	bool calculateHit(float dex);

	void attackEnemy(float str, float dex);
	void EndTurn();

	int getStrength();
	int getMaxHealth();
	int getDexterity();
	int getCurrentHealth();

	void setStrength(int strength);
	void setMaxHealth(int maxHealth);
	void setDexterity(int dexterity);
	void setCurrentHealth(int health);
};