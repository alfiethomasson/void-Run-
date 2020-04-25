#pragma once
#include <iostream>
#include "Room.h"
#include "cmp_inventory.h"
#include "ItemDB.h"

class TreasureRoom : public Room {
private:
	std::shared_ptr<Inventory> inv;
	ItemDB itemDB;
	sf::Sprite chestSprite;
	sf::Sprite iconSprite;
	sf::Text PressText;

	sf::FloatRect iconBox;

	sf::Sound sound;

	bool chestOpened;

	sf::Clock delayClock;
	float delayTime;
	const float delayAmount;
public:
	TreasureRoom(std::shared_ptr<Entity> p, ItemDB &iDB);
	~TreasureRoom() override = default;

	void Update(const double& dt, sf::Vector2f cursPos) override;
	void Render() override;
	void Load() override;

	void OpenChest();

};