#include "cmp_inventory.h"

Inventory::Inventory(Entity* p, float inventorySize)
	: inventorySize{ inventorySize }, Component(p) {}

void Inventory::add(std::shared_ptr<Item> item)
{
	if (checkEmptySlot())
	{
		std::cout << "Adding item to inventory! \n";
		item->Equip(*_parent);
		items.push_back(item);
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

void Inventory::update(double dt) {}