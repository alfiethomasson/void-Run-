#include "cmp_inventory.h"

Inventory::Inventory(Entity* p, float inventorySize, GameUI *gui)
	: inventorySize{ inventorySize }, gameUI{ *gui }, Component(p) {}

bool Inventory::add(std::shared_ptr<Item> item, bool addStat)
{
	if (checkEmptySlot())
	{
		std::cout << "Adding item to inventory! \n";
		item->Equip(*_parent, addStat);
		//item->getSprite().set
		item->getSprite().setPosition(positions[items.size()]);
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

void Inventory::remove(int position)
{
	items[position]->Unequip(position);
	items.erase(items.begin() + position);
	boxes.erase(boxes.begin() + position);
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->getSprite().setPosition(positions[i]);
		boxes[i] = items[i]->getSprite().getGlobalBounds();
	}
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
	positions[0] = sf::Vector2f(1400.0f, 700.0f);
	positions[1] = sf::Vector2f(1500.0f, 700.0f);
	positions[2] = sf::Vector2f(1600.0f, 700.0f);
	positions[3] = sf::Vector2f(1400.0f, 800.0f);
	positions[4] = sf::Vector2f(1500.0f, 800.0f);
	positions[5] = sf::Vector2f(1600.0f, 800.0f);
	positions[6] = sf::Vector2f(1400.0f, 900.0f);
	positions[7] = sf::Vector2f(1500.0f, 900.0f);
	positions[8] = sf::Vector2f(1600.0f, 900.0f);
}

std::vector<std::shared_ptr<Item>> Inventory::getItems()
{
	return items;
}

void Inventory::update(double dt)
{
	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);
	
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

void Inventory::render()
{
	for(auto& e : items)
	{
		Renderer::queue(&e->getSprite());
	}
}