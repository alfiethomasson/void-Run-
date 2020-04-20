#pragma once
#include <iostream>
#include "Room.h"
#include "cmp_player.h"

class LevelUpRoom : public Room {
protected:
	sf::Font font;
	sf::Text playerHP;
	sf::Text experienceCounter;

	sf::Texture statUPTex;
	sf::Sprite ability1;
	sf::Sprite ability2;

	sf::Text RewardsText;
	sf::Text StrengthText;
	sf::Text HealthText;
	sf::FloatRect ability1Box;
	sf::FloatRect ability2Box;
public:

	LevelUpRoom(std::shared_ptr<Entity> p);
	~LevelUpRoom() override = default;
	//explicit CombatRoom(Entity* p);
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
};