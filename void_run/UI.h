#pragma once
#include "engine.h"
#include "system_renderer.h"

class CombatUI : UIManager {
protected:
	sf::Sprite attackSprite;
	sf::Sprite specialSprite;
	sf::Texture attackTex;
	sf::Texture specialTex;
	sf::FloatRect attackBox;
	sf::FloatRect specialBox;
public:

	void Update(double dt);
	void turnUpdate();
	sf::FloatRect& getAttackBox();
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

	sf::Font font;
public:
	sf::Text descText;
	void Update(double dt);
	void Render();
	void Load(int maxAP);

	sf::Sprite getNewCell();

	int getAPAmount();
	void useAP(int amount);
	void gainAP(int amount);

	void UpdateDesc(std::string string);
	void UpdateDescPos(sf::Vector2f pos);
};