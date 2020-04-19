#pragma once
#include <iostream>
#include "Room.h"
#include "cmp_player.h"

class CombatRoom : public Room {
protected:
	sf::Font font;
	sf::Text playerHP;
	sf::Text enemyHP;
	sf::Text experienceCounter;

	sf::Texture statUPTex;
	sf::Sprite stat1;
	sf::Sprite stat2;
	sf::Sprite stat3;

	sf::Text RewardsText;
	sf::Text StrengthText;
	sf::Text HealthText;
	sf::Text DexterityText;
	sf::FloatRect stat1Box;
	sf::FloatRect stat2Box;
	sf::FloatRect stat3Box;
public:
	CombatRoom(std::shared_ptr<Entity> p);
	~CombatRoom() override = default;
	//explicit CombatRoom(Entity* p);
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad();

	bool checkStatus();
}; 