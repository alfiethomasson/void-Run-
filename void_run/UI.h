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