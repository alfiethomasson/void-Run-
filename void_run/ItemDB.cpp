#include "ItemDB.h"

//Function that adds items to a common, and rare vector
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

//Gets a random common item from list
std::shared_ptr<Item> ItemDB::randomCommonItem()
{
	srand(time(0));
	int randValue = rand() % commonItems.size() ;
	std::cout << "Random Item is: " << commonItems[randValue].description << "\n";
	std::shared_ptr<Item> randItem = std::make_shared<Item>(commonItems[randValue]);
	return randItem;
}
//Gets a random item from list
std::shared_ptr<Item> ItemDB::randomRareItem()
{
	//resets random stuff
	srand(time(0));
	//gets random value from 0 to vector size
	int randValue = rand() % rareItems.size();
	//what item is
	std::cout << "Random Item is: " << rareItems[randValue].description << "\n";
	//makes a shared pointer
	std::shared_ptr<Item> randItem = std::make_shared<Item>(rareItems[randValue]);
	//returns item
	return randItem;
}