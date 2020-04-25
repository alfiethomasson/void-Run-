#pragma once
#include <iostream>
#include "ecm.h"
#include "Item.h"
#include "UI.h"

class Inventory : public Component {
protected:
	float inventorySize;
	std::vector<std::shared_ptr<Item>> items;
	std::vector<sf::FloatRect> boxes;
	sf::Vector2f positions[9];
	GameUI& gameUI;
public: 

	Inventory() = delete;
	explicit Inventory(Entity* p, float inventorySize, GameUI *gameUI);
	void update(double dt) override;
	void render() override;
	void Load();

	bool add(std::shared_ptr<Item> item, bool addStat);
	void remove(int position);

	std::vector<std::shared_ptr<Item>> getItems();

	bool checkEmptySlot();
};