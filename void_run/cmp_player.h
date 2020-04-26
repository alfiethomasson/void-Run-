#pragma once
#include "ecm.h"
#include "cmp_enemy.h"
#include "cmp_abilitymanager.h"
#include "cmp_sprites.h"
#include "UI.h"
#include "system_renderer.h"

class BaseEnemyComponent;
class SpecialItem;
class AbilityManager;
class CombatUI;
class GameUI;

class BasePlayerComponent : public Component {
private:
	float playerDamage;
	float _strength;
	float _dexterity;
	float _maxHealth;
	float currentHealth;
	float playerHealQuantity;
	float _experience;
	int actionPoints;
	int _actionPointsMax;
	int runChance;

	std::shared_ptr<BaseEnemyComponent> currentEnemy;
	std::shared_ptr<AbilityManager> abilityManager;
	std::shared_ptr<SpriteComponent> spriteManager;
//	std::vector<SpecialAbility> specialMoves;
	CombatUI& combatUI;
	GameUI& gameUI;

private:
	sf::Font font;
	sf::Text GameOverButton;
	sf::FloatRect GameOverButtonBox;
	int healthSize;
	std::vector<sf::RectangleShape> hpbars;
	int barheight;
	sf::Text healthText;

	sf::Text StrengthText;
	sf::Text HPText;
	sf::Text DexterityText;

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
	int level;

	int _level;

	explicit BasePlayerComponent(Entity* p, float maxhealth, float currenthealth, float strength, float dex,
		float experience, int actionPoints, CombatUI *ui, GameUI *gameUI);
	BasePlayerComponent() = delete;

	void render() override;
	void update(double dt) override;
	void load();

	void updateEnemy(std::shared_ptr<BaseEnemyComponent> e);
	bool checkEnemyStatus();
	bool checkLevelUp();

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
	int getRunChance();
	std::shared_ptr<BaseEnemyComponent> getEnemy();

	void setMaxAP(int maxAP);
	void setStrength(int strength);
	void setMaxHealth(int maxHealth);
	void setDexterity(int dexterity);
	void setCurrentHealth(int health);
	void setExperience(int experience);
	void setRunChance(int run);

	void addStats(int strength, int health, int dex);
	void UpdateStats();

	void makeHPBar();

	void takeDamage(float dmgRecieved);
	bool calculateHit(float enemyDex);
	int calcRunChance();
};