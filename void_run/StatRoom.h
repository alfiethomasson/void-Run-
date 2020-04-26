#pragma once
#include "Room.h"

class StatRoom : public Room {
protected:
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

public:
	StatRoom(std::shared_ptr<Entity> p);
	~StatRoom() override = default;

	void Update(const double& dt, sf::Vector2f cursPos) override;
	void Render() override;
	void Load() override;
	void UnLoad();

};