#pragma once
#include "Item.h"
#include "Specials.h"
#include <time.h>  
#include <random>
#include <chrono>

class ItemDB {
private:
	std::vector<Item> commonItems;
	std::vector<Item> rareItems;
	std::vector<SpecialItem> specialItems;
public:

	void PopulateDB();

	std::shared_ptr<Item> randomCommonItem();
	std::shared_ptr<Item> randomRareItem();
	std::shared_ptr<SpecialItem> randomSpecialItem();

	//template <class T>
	//std::shared_ptr<T> createClass()
	//{
	//	return new T();
	//}
};