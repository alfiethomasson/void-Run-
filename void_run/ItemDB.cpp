#include "ItemDB.h"
#include <iterator>

//Populates the database, adding all special abilities and items to respective maps to access in future
void ItemDB::PopulateDB()
{
	//Get all abilities and add to map
	auto lb = std::make_shared<LaserBurst>();
	lb->load();
	abilitys["LaserBurst"] = lb;
	auto ow = std::make_shared<OverloadWeapon>();
	ow->load();
	abilitys["OverloadWeapon"] = ow;
	auto us = std::make_shared<UncannySpeed>();
	us->load();
	abilitys["UncannySpeed"] = us;
	auto pi = std::make_shared<PrimalInstincts>();
	pi->load();
	abilitys["PrimalInstincts"] = pi;
	auto df = std::make_shared<DeadlyFumes>();
	df->load();
	abilitys["DeadlyFumes"] = df;
	auto mg = std::make_shared<MagmaGrenade>();
	mg->load();
	abilitys["MagmaGrenade"] = mg;
	auto nb = std::make_shared<NanoBots>();
	nb->load();
	abilitys["NanoBots"] = nb;
	auto hg = std::make_shared<HoloGamble>();
	hg->load();
	abilitys["HoloGamble"] = hg;


	//Common Items
	commonItems["BlasterUpgrade"] = Item(5, 5, 0, "BlasterUpgrade", "Blaster Upgrade", "Pointy");
	commonItems["ExtraPadding"] = Item(0, 10, 0, "ExtraPadding", "Extra Padding", "ExtraPadding");
	commonItems["Stimulant"] = Item(0, 5, 5, "Stimulant", "Stimulant", "Stimulant");

	//Rare Items
	rareItems["PrecisionWatch"] = Item(15, 0, 0, "PrecisionWatch", "Precision Watch", "SpaceWatch");
	rareItems["WristGuard"] = Item(0, 30, 0, "WristGuard", "Wrist Guard", "WristGuard");
	rareItems["Mask"] = Item(0, 0, 15, "Mask", "Mask", "FaceMask");

	//Special Items
	specialItems["*TargetingDevice"] =
		SpecialItem(5, 50, 5, "*TargetingDevice", "Targeting Device", "SpaceWatch", lb);
}

//Gets a random common item from list
std::shared_ptr<Item> ItemDB::randomCommonItem()
{
	// make new seed for random number generator from time, faster than time(0)
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//makes new generator with seed
	std::default_random_engine generator(seed);

	//Sets value for minimum and maximum random number
	std::uniform_int_distribution<int> distributionInteger(0, commonItems.size() - 1); 

	//Rolls random number
	int randValue = distributionInteger(generator);

	//Iterates through map to get the item at the random values point
	std::map<std::string, Item>::iterator it = commonItems.begin();
	std::advance(it, randValue);
	//makes item a shared pointer
	std::shared_ptr<Item> randItem = std::make_shared<Item>(it->second);
	return randItem;
}
//Gets a random item from list
std::shared_ptr<Item> ItemDB::randomRareItem()
{
	// make new seed for random number generator from time, faster than time(0)
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//makes new generator with seed
	std::default_random_engine generator(seed);

	//Sets value for minimum and maximum random number
	std::uniform_int_distribution<int> distributionInteger(0, rareItems.size() - 1);

	//Rolls random number
	int randValue = distributionInteger(generator);

	std::map<std::string, Item>::iterator it = rareItems.begin();
	std::advance(it, randValue);
	std::shared_ptr<Item> randItem = std::make_shared<Item>(it->second);
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
	//std::cout << "Random Item is: " << specialItems[randValue].description << "\n";
	//makes a shared pointer
	//std::shared_ptr<SpecialItem> randItem = std::make_shared<SpecialItem>(specialItems[randValue]);
	std::map<std::string, SpecialItem>::iterator it = specialItems.begin();
	std::advance(it, randValue);
	std::shared_ptr<SpecialItem> randItem = std::make_shared<SpecialItem>(it->second);
	return randItem;
}

std::shared_ptr<Item> ItemDB::getCommonItem(std::string& name)
{
	std::shared_ptr<Item> item = std::make_shared<Item>(commonItems[name]);
	return item;
}

std::shared_ptr<Item> ItemDB::getRareItem(std::string& name)
{
	std::shared_ptr<Item> item = std::make_shared<Item>(rareItems[name]);
	return item;
}

std::shared_ptr<SpecialItem> ItemDB::getSpecialItem(std::string& name)
{
	std::shared_ptr<SpecialItem> item = std::make_shared<SpecialItem>(specialItems[name]);
	return item;
}

std::shared_ptr<Item> ItemDB::getItem(std::string& name)
{
	if (commonItems.count(name) > 0)
	{
		std::shared_ptr<Item> item = std::make_shared<Item>(commonItems[name]);
		return item;
	}
	else if (rareItems.count(name) > 0)
	{
		std::shared_ptr<Item> item = std::make_shared<Item>(rareItems[name]);
		return item;
	}
	//else if (specialItems.count(name) > 0)
	//{
	//	std::shared_ptr<SpecialItem> item = std::make_shared<SpecialItem>(rareItems[name]);
	//	return item;
	//}
	else
	{
		std::cout << "Couldn't find item: " << name << "\n";
	}
}

std::shared_ptr<SpecialAbility> ItemDB::getAbility(std::string& name)
{
	if (abilitys.count(name) > 0)
	{
		return abilitys[name];
	}
	else
	{
		std::cout << "Couldn't find ability " << name << "\n";
	}
}