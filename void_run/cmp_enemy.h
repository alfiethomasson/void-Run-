#pragma once
#include "ecm.h"
#include "cmp_player.h"

class BasePlayerComponent;

class BaseEnemyComponent : public Component {
protected:
	float enemyDamage;
	std::shared_ptr<BasePlayerComponent> currentEnemy;
	float _strength;
	float _dexterity;
	float _maxHealth;
	float currentHealth;
public:
	bool isTurn;
	bool isFinishedTurn;
	float expReward;

	BaseEnemyComponent(Entity* p, float health, float strength, float dex, float expReward);
	BaseEnemyComponent() = delete;

	void render() override {}
	void update(double dt) override;
	void updateEnemy(std::shared_ptr<BasePlayerComponent> player);

	void TakeDamage(float damage);

	void attackEnemy(float damage);
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