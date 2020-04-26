#pragma once
#include "Item.h"
#include "Specials.h"
#include <time.h>  
#include <random>
#include <chrono>

class ItemDB {
private:
	std::map<std::string, Item> commonItems;
	std::map<std::string, Item> rareItems;
	std::map<std::string, SpecialItem> specialItems;
public:

	void PopulateDB();

	std::shared_ptr<Item> randomCommonItem();
	std::shared_ptr<Item> randomRareItem();
	std::shared_ptr<SpecialItem> randomSpecialItem();

	std::shared_ptr<Item> getCommonItem(std::string& name);
	std::shared_ptr<Item> getRareItem(std::string& name);
	std::shared_ptr<SpecialItem> getSpecialItem(std::string& name);

	std::shared_ptr<Item> getItem(std::string& name);

	//template <class T>
	//std::shared_ptr<T> createClass()
	//{
	//	return new T();
	//}
};