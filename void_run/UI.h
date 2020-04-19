#pragma once
#include "engine.h"
#include "system_renderer.h"
#include "cmp_player.h"

class BasePlayerComponent;

class CombatUI : UIManager {
protected:
	sf::Sprite attackSprite;
	sf::Sprite specialSprite;
	sf::Sprite healSprite;
	sf::Sprite rechargeSprite;
	sf::Sprite runSprite;
	sf::Texture attackTex;
	sf::Texture specialTex;
	sf::Texture healTex;
	sf::Texture rechargeTex;
	sf::Texture runTex;
	sf::FloatRect attackBox;
	sf::FloatRect specialBox;
	sf::FloatRect healBox;
	sf::FloatRect rechargeBox;
	sf::FloatRect runBox;
public:

	void Update(double dt);
	void turnUpdate();
	sf::FloatRect& getAttackBox();
	sf::FloatRect& getHealBox();
	sf::FloatRect& getRechargeBox();
	sf::FloatRect& getRunBox();
	bool CheckBoxes(sf::Vector2f curspos);
	void Render();
	void Load();

	void addSpecial(std::string texName);
	void resetSpecial();
};

class GameUI : UIManager {
protected:
	int APAmount;
	int MaxAP;
	int height;
	//sf::Sprite APContainer;
	//sf::Texture APContainerTex;
	sf::Texture CellTex;
	std::vector<sf::Sprite> cells;

	sf::Texture statUPTex;
	sf::Sprite stat1;
	sf::Sprite stat2;
	sf::Sprite stat3;
	sf::Font font;

	sf::Text RewardsText;
	sf::Text StrengthText;
	sf::Text HealthText;
	sf::Text DexterityText;
	sf::FloatRect stat1Box;
	sf::FloatRect stat2Box;
	sf::FloatRect stat3Box;
	std::shared_ptr<BasePlayerComponent> player;

	bool inStatUp;
public:
	GameUI() = default;
	~GameUI() = default;

	sf::Text descText;
	void Update(double dt);
	void Render();
	void Load(int maxAP, std::shared_ptr<BasePlayerComponent> p);

	sf::Sprite getNewCell();

	int getAPAmount();
	void useAP(int amount);
	void gainAP(int amount);

	void UpdateDesc(std::string string);
	void UpdateDescPos(sf::Vector2f pos);

	void statUp();
	bool updateStatOptions();
};