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
public:
	CombatRoom(std::shared_ptr<Entity> p);
	~CombatRoom() override = default;
	//explicit CombatRoom(Entity* p);
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad();
}; 