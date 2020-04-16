#pragma once
#include <iostream>
#include "ecm.h"
#include "Item.h"

class Inventory : public Component {
protected:
	float inventorySize;
	std::vector<std::shared_ptr<Item>> items;
	sf::Vector2f positions[9];
public: 

	Inventory() = delete;
	explicit Inventory(Entity* p, float inventorySize);

	void update(double dt) override;
	void render() override {};
	void Load();

	bool add(std::shared_ptr<Item> item);
	void remove(int position);

	bool checkEmptySlot();
};