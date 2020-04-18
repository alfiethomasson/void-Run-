#include "UI.h"

void CombatUI::Render()
{
 	Renderer::queue(&attackSprite);
	Renderer::queue(&specialSprite);
}

void CombatUI::turnUpdate()
{

}

void CombatUI::Load()
{
	if (!attackTex.loadFromFile("res/Icons/Attack.png"))
	{
		std::cout << "Couldn't load attack icon\n";
	}
	attackSprite.setTexture(attackTex);
	attackSprite.setScale(0.3f, 0.3f);
	attackSprite.setPosition(sf::Vector2f(500.0f, 600.0f));
	attackBox = attackSprite.getGlobalBounds();

	specialSprite.setPosition(sf::Vector2f(600.0f, 600.0f));
	specialBox = specialSprite.getGlobalBounds();
}

sf::FloatRect& CombatUI::getAttackBox()
{
	return attackBox;
}

void CombatUI::addSpecial(std::string texName)
{
	if (!specialTex.loadFromFile("res/icons/" + texName + ".png"))
	{
		std::cout << "Failed to load " << texName << " combat icon\n";
	}
	specialSprite.setTexture(specialTex);
	specialSprite.setPosition(sf::Vector2f(600.0f, 600.0f));
	specialSprite.setScale(0.3f, 0.3f);
}

void CombatUI::resetSpecial()
{
	specialSprite = sf::Sprite();
}

void GameUI::Update(double dt)
{

}

void GameUI::Render()
{
	for (auto& e : cells)
	{
		Renderer::queue(&e);
	}
	Renderer::queue(&descText);
//	Renderer::queue(&APContainer);
}

void GameUI::Load(int maxAP)
{
	if (!CellTex.loadFromFile("res/Icons/Charge.png"))
	{
		std::cout << "Couldnt load AP Charge\n";
	}
	MaxAP = maxAP;
	APAmount = MaxAP;

	for(int i = 0; i < MaxAP; i++)
	{
		sf::Sprite cell;
		cell.setTexture(CellTex);
		cell.setScale(0.2f, 0.15f);
		height += 20;
		cell.setPosition(sf::Vector2f(60.0f, 550.0f - (height)));
		cells.push_back(cell);
	}
	if (!font.loadFromFile("res/Fonts/mandalore.ttf"))
	{
		std::cout << "failed to load mandalore font in game ui\n";
	}
	descText.setFont(font);
	descText.setCharacterSize(30);
	descText.setString("");
}

sf::Sprite GameUI::getNewCell()
{
	//if (!CellTex.loadFromFile("res/Icons/Charge.png"))
	//{
	//	std::cout << "Couldnt load AP Charge\n";
	//}
	sf::Sprite cell;
	cell.setTexture(CellTex);
	cell.setScale(0.2f, 0.15f);
	height += 20;
	cell.setPosition(sf::Vector2f(60.0f, 550.0f - (height)));
	return cell;
}


void GameUI::useAP(int amount)
{
	int temp = APAmount - amount;
	if (temp < 0)
	{
		APAmount = 0;
	}
	else
	{
		APAmount = temp;
	}
	if (APAmount != 0)
	{
		for (int i = 0; i < amount; i++)
		{
			cells.pop_back();
			height -= 20;
		}
	}
	else
	{
		while (!cells.empty())
		{
			cells.pop_back();
			height -= 20;
		}
	}
}

void GameUI::gainAP(int amount)
{
	int temp = APAmount + amount;
	if (temp > MaxAP)
	{
		for (int i = 0; i < MaxAP - APAmount; i++)
		{
			cells.push_back(getNewCell());
		}
		APAmount = MaxAP;
	}
	else
	{
		APAmount = temp;
		for (int i = 0; i < amount; i++)
		{
			cells.push_back(getNewCell());
		}
	}
}

int GameUI::getAPAmount()
{
	return cells.size();
}

void GameUI::UpdateDesc(std::string string)
{
	descText.setString(string);
}

void GameUI::UpdateDescPos(sf::Vector2f pos)
{
	descText.setPosition(pos);
}