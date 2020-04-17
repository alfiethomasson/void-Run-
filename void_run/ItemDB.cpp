#include "ItemDB.h"

//Function that adds items to a common, and rare vector
void ItemDB::PopulateDB()
{
	//Common Items
	auto newItem = Item(5, 5, 0, "Blaster Upgrade", "Pointy");
	commonItems.push_back(newItem);
	newItem = Item(0, 10, 0, "Extra Padding", "ExtraPadding");
	commonItems.push_back(newItem);
	newItem = Item(0, 5, 5, "Stimulant", "Stimulant");
	commonItems.push_back(newItem);

	//Rare Items
	newItem = Item(15, 0, 0, "Precision Watch", "SpaceWatch");
	rareItems.push_back(newItem);
	newItem = Item(0, 30, 0, "Wrist Guard", "WristGuard");
	rareItems.push_back(newItem);
	newItem = Item(0, 0, 15, "Mask", "FaceMask");
	rareItems.push_back(newItem);

	auto lb = std::make_shared<LaserBurst>();
	lb->load();
	auto newSpecial = SpecialItem(5, 50, 5, "Targeting Device", "SpaceWatch", lb);
	specialItems.push_back(newSpecial);
}

//Gets a random common item from list
std::shared_ptr<Item> ItemDB::randomCommonItem()
{
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger(0, commonItems.size() - 1); 

	int randValue = distributionInteger(generator);
	std::cout << "Random Item is: " << commonItems[randValue].description << "\n";
	std::shared_ptr<Item> randItem = std::make_shared<Item>(commonItems[randValue]);
	return randItem;
}
//Gets a random item from list
std::shared_ptr<Item> ItemDB::randomRareItem()
{
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger(0, rareItems.size() - 1);
	//gets random value from 0 to vector size
	int randValue = distributionInteger(generator);
	//what item is
	std::cout << "Random Item is: " << rareItems[randValue].description << "\n";
	//makes a shared pointer
	std::shared_ptr<Item> randItem = std::make_shared<Item>(rareItems[randValue]);
	//returns item
	return randItem;
}

std::shared_ptr<SpecialItem> ItemDB::randomSpecialItem()
{
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger(0, specialItems.size() - 1);
	//gets random value from 0 to vector size
	int randValue = distributionInteger(generator);
	//what item is
	std::cout << "Random Item is: " << specialItems[randValue].description << "\n";
	//makes a shared pointer
	std::shared_ptr<SpecialItem> randItem = std::make_shared<SpecialItem>(specialItems[randValue]);
	//returns item
	return randItem;
}