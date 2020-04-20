#pragma once
#include "ecm.h"
#include "cmp_enemy.h"
#include "cmp_abilitymanager.h"
#include "UI.h"

class BaseEnemyComponent;
class SpecialItem;
class AbilityManager;
class CombatUI;
class GameUI;

class BasePlayerComponent : public Component {
protected:
	float playerDamage;
	float _strength;
	float _dexterity;
	int _maxHealth;
	int currentHealth;
	float playerHealQuantity;
	float _experience;
	int actionPoints;
	int _actionPointsMax;
	int runChance;

	std::shared_ptr<BaseEnemyComponent> currentEnemy;
	std::shared_ptr<AbilityManager> abilityManager;
//	std::vector<SpecialAbility> specialMoves;
	CombatUI& combatUI;
	GameUI& gameUI;

public:
	bool isTurn;
	bool isFinishedTurn;
	bool expGained;
	int baseAttackCost;
	int mediumAttackCost;
	int heavyAttackCost;
	int healCost;
	int rechargeCost;
	int runCost;

	explicit BasePlayerComponent(Entity* p, int health, float strength, float dex,
		float experience, int actionPoints, CombatUI *ui, GameUI *gameUI);
	BasePlayerComponent() = delete;

	void render() override {}
	void update(double dt) override;
	void load();

	void updateEnemy(std::shared_ptr<BaseEnemyComponent> e);
	bool checkEnemyStatus();

	void attack(float damage, float dex);
	void heal(float healBy);
	void recharge(int amount);
	void run();
	void expGet();
	void EndTurn();

	bool CheckAP(int ap);
	void SpendAP(int ap);
	void gainAP(int amount);

	int getCurrentAP();
	int getStrength();
	int getMaxHealth();
	int getDexterity();
	int getCurrentHealth();
	int getExperience();

	void setMaxAP(int maxAP);
	void setStrength(int strength);
	void setMaxHealth(int maxHealth);
	void setDexterity(int dexterity);
	void setCurrentHealth(int health);
	void setExperience(int experience);

	void addStats(int strength, int health, int dex);

	void takeDamage(float dmgRecieved);
	bool calculateHit(float enemyDex);
	int calcRunChance();
};