#include "cmp_inventory.h"

Inventory::Inventory(Entity* p, float inventorySize)
	: inventorySize{ inventorySize }, Component(p) {}

bool Inventory::add(std::shared_ptr<Item> item)
{
	if (checkEmptySlot())
	{
		std::cout << "Adding item to inventory! \n";
		item->Equip(*_parent);
		item->getSprite().setPosition(positions[items.size()]);
		items.push_back(item);
		return true;
	}
	else
	{
		return false;
	}
}

void Inventory::remove(int position)
{
	items[position]->Unequip();
	items.erase(items.begin() + position);
}

bool Inventory::checkEmptySlot()
{
	if (items.size() < inventorySize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Inventory::Load()
{
	positions[0] = sf::Vector2f(100.0f, 600.0f);
	positions[1] = sf::Vector2f(200.0f, 600.0f);
	positions[2] = sf::Vector2f(300.0f, 600.0f);
	positions[3] = sf::Vector2f(100.0f, 650.0f);
	positions[4] = sf::Vector2f(200.0f, 650.0f);
	positions[5] = sf::Vector2f(300.0f, 650.0f);
	positions[6] = sf::Vector2f(100.0f, 700.0f);
	positions[7] = sf::Vector2f(200.0f, 700.0f);
	positions[8] = sf::Vector2f(300.0f, 700.0f);
}

void Inventory::update(double dt) {}