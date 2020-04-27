#include "cmp_inventory.h"

Inventory::Inventory(Entity* p, float inventorySize, GameUI *gui)
	: inventorySize{ inventorySize }, gameUI{ *gui }, Component(p) {}

//Adds item to inventory
bool Inventory::add(std::shared_ptr<Item> item, bool addStat)
{
	//checks if empty slot in inventory and if so adds item
	if (checkEmptySlot())
	{
		std::cout << "Adding item to inventory! \n";
		//calls equip function on new item
		item->Equip(*_parent, addStat);
		//sets item position to position in inventory
		item->getSprite().setPosition(positions[items.size()]);
		//gets bounding box of item
		sf::FloatRect tempBox = item->getSprite().getGlobalBounds();
		boxes.push_back(tempBox);
		items.push_back(item);
		return true;
	}
	else
	{
		return false;
	}
}

//Remove item from position 
void Inventory::remove(int position)
{
	//Calls unequip on item in position passed through 
	items[position]->Unequip(position);
	//removes item from items and boxes vector
	items.erase(items.begin() + position);
	boxes.erase(boxes.begin() + position);
	//updates other items positions to reflect this
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->getSprite().setPosition(positions[i]);
		boxes[i] = items[i]->getSprite().getGlobalBounds();
	}
}

//Checks if there is an empty slot in inventory
bool Inventory::checkEmptySlot()
{
	if (items.size() < inventorySize) // if size of items vector is smaller than the variable inventory size
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Sets positions for inventory items
void Inventory::Load()
{
	positions[0] = sf::Vector2f(1400.0f, 800.0f);
	positions[1] = sf::Vector2f(1500.0f, 800.0f);
	positions[2] = sf::Vector2f(1600.0f, 800.0f);
	positions[3] = sf::Vector2f(1400.0f, 900.0f);
	positions[4] = sf::Vector2f(1500.0f, 900.0f);
	positions[5] = sf::Vector2f(1600.0f, 900.0f);
	positions[6] = sf::Vector2f(1400.0f, 1000.0f);
	positions[7] = sf::Vector2f(1500.0f, 1000.0f);
	positions[8] = sf::Vector2f(1600.0f, 1000.0f);
}

//returns all items in inventory
std::vector<std::shared_ptr<Item>> Inventory::getItems()
{
	return items;
}

void Inventory::update(double dt)
{
	//gets current cursor position
	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);
	//updates curspos for window size
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;
	
	//checks all items in inventory, to show tooltip with what item is called
	for (int i = 0; i < boxes.size(); i++)
	{
		if (boxes[i].contains(cursPos))
		{
			gameUI.descText.setString(items[i]->description);
			gameUI.descText.setPosition(sf::Vector2f(boxes[i].getPosition().x + (boxes[i].width / 2) - 
				(gameUI.descText.getLocalBounds().width / 2),
				boxes[i].getPosition().y - 50.0f));
		}

	}
}

//renders all items in inventory
void Inventory::render()
{
	for(auto& e : items)
	{
		Renderer::queue(&e->getSprite());
	}
}