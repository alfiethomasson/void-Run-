#pragma once
#include <iostream>
#include "Room.h"
#include "cmp_player.h"
#include "engine.h"

class LevelUpRoom : public Room {
protected:
	sf::Font font;
	sf::Texture statUPTex;

	//sf::Text playerHP;
	//sf::Text experienceCounter;

	sf::Sprite ability1;
	sf::Sprite ability2;
	sf::Sprite statIncrease1;
	sf::Sprite statIncrease2;
	sf::Sprite statIncrease3;

	sf::Text ability1Text;
	sf::Text ability2Text;
	sf::Text statIncrease1Text;
	sf::Text statIncrease2Text;
	sf::Text statIncrease3Text;

	sf::FloatRect ability1Box;
	sf::FloatRect ability2Box;
	sf::FloatRect statIncrease1Box;
	sf::FloatRect statIncrease2Box;
	sf::FloatRect statIncrease3Box;
public:

	LevelUpRoom(std::shared_ptr<Entity> p);
	~LevelUpRoom() override = default;
	//explicit CombatRoom(Entity* p);
	void Update(const double& dt, sf::Vector2f cursPos) override;
	void Render() override;
	void Load() override;
};