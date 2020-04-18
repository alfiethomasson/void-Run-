#pragma once
#include "ecm.h"
#include "cmp_enemy.h"
#include "cmp_abilitymanager.h"
#include "UI.h"

class BaseEnemyComponent;
class SpecialItem;
class AbilityManager;

class BasePlayerComponent : public Component {
protected:
	float playerDamage;
	float _strength;
	float _dexterity;
	float _maxHealth;
	float currentHealth;
	float playerHealQuantity;
	float _experience;
	std::shared_ptr<BaseEnemyComponent> currentEnemy;
	std::shared_ptr<AbilityManager> abilityManager;
//	std::vector<SpecialAbility> specialMoves;
	CombatUI combatUI;

public:
	bool isTurn;
	bool isFinishedTurn;
	bool expGained;
	explicit BasePlayerComponent(Entity* p, float health, float strength, float dex, float experience, CombatUI ui);
	BasePlayerComponent() = delete;

	void render() override {}
	void update(double dt) override;
	void load();

	void updateEnemy(std::shared_ptr<BaseEnemyComponent> e);
	bool checkEnemyStatus();

	void attack(float damage);
	void heal(float healBy);
	void expGet();
	void EndTurn();

	int getStrength();
	int getMaxHealth();
	int getDexterity();
	float getCurrentHealth();
	int getExperience();

	void setStrength(int strength);
	void setMaxHealth(int maxHealth);
	void setDexterity(int dexterity);
	void setCurrentHealth(int health);
	void setExperience(int experience);

	void addStats(int strength, int health, int dex);

	void takeDamage(float dmgRecieved);
};