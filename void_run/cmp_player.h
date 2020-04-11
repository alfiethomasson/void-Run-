#pragma once
#include "ecm.h"

class BasePlayerComponent : public Component {
protected:
	float playerDamage;
	float _strength;
	float _dexterity;
	float _maxHealth;
	float currentHealth;
	float playerHealQuantity;
	std::shared_ptr<Entity> currentEnemy;
public:
	bool isTurn;
	bool isFinishedTurn;
	explicit BasePlayerComponent(Entity* p);
	BasePlayerComponent() = delete;

	void render() override {}
	void update(double dt) override;

	void updateEnemy(std::shared_ptr<Entity> e);

	void attack(float damage);
	void heal(float healBy);
	void EndTurn();

	int getStrength();
	int getMaxHealth();
	int getDexterity();
	int getCurrentHealth();

	void setStrength(int strength);
	void setMaxHealth(int maxHealth);
	void setDexterity(int dexterity);
	void setCurrentHealth(int health);

	void takeDamage(int dmgRecieved);
};