#include "ItemDB.h"

void ItemDB::PopulateDB()
{
	//Common Items
	auto newItem = Item(5, 5, 0, "Blaster Upgrade");
	commonItems.push_back(newItem);
	newItem = Item(0, 10, 0, "Extra Padding");
	commonItems.push_back(newItem);
	newItem = Item(0, 5, 5, "Stimulant");
	commonItems.push_back(newItem);

	//Rare Items
	newItem = Item(15, 0, 0, "Precision Scope");
	rareItems.push_back(newItem);
	newItem = Item(0, 30, 0, "Reinforced Armour");
	rareItems.push_back(newItem);
	newItem = Item(0, 0, 15, "Rocket Boots");
	rareItems.push_back(newItem);
}

std::shared_ptr<Item> ItemDB::randomCommonItem()
{
	srand(time(0));
	int randValue = rand() % commonItems.size() ;
	std::cout << "Random Item is: " << commonItems[randValue].description << "\n";
	std::shared_ptr<Item> randItem = std::make_shared<Item>(commonItems[randValue]);
	return randItem;
}
std::shared_ptr<Item> ItemDB::randomRareItem()
{
	srand(time(0));
	int randValue = rand() % rareItems.size();
	std::cout << "Random Item is: " << rareItems[randValue].description << "\n";
	std::shared_ptr<Item> randItem = std::make_shared<Item>(rareItems[randValue]);
	return randItem;
}