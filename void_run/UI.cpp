#include "UI.h"
#include "cmp_player.h"

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
	//Renderer::queue(&stat1);
	//Renderer::queue(&stat2);
	//Renderer::queue(&stat3);
	//Renderer::queue(&RewardsText);
	//Renderer::queue(&DexterityText);
}

void GameUI::Load(int maxAP, std::shared_ptr<BasePlayerComponent> p)
{
	player = p;

	if (!CellTex.loadFromFile("res/Icons/Charge.png"))
	{
		std::cout << "Couldnt load AP Charge\n";
	}
	if (!statUPTex.loadFromFile("res/Icons/Arrow.png"))
	{
		std::cout << "Couldnt load up arrow in stat room\n";
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

	stat1.setTexture(statUPTex);
	stat2.setTexture(statUPTex);
	stat3.setTexture(statUPTex);
	stat1.setScale(0.3f, 0.3f);
	stat2.setScale(0.3f, 0.3f);
	stat3.setScale(0.3f, 0.3f);
	stat1.setRotation(90);
	stat2.setRotation(90);
	stat3.setRotation(90);
	stat1.setPosition(500.0f, 400.0f);
	stat2.setPosition(700.0f, 400.0f);
	stat3.setPosition(900.0f, 400.0f);

	RewardsText.setFont(font);
	StrengthText.setFont(font);
	HealthText.setFont(font);
	DexterityText.setFont(font);
	RewardsText.setCharacterSize(60);
	StrengthText.setCharacterSize(30);
	HealthText.setCharacterSize(30);
	DexterityText.setCharacterSize(30);
	RewardsText.setString("REWARDS");
	//StrengthText.setString("Strength Up\n Current Strength - " + p->getStrength());
	//HealthText.setString("Health Up\n Current Max Health - " + p->getMaxHealth());
	//DexterityText.setString("Dexterity Up\n Current Dex - " + p->getDexterity());
	RewardsText.setPosition((Engine::getWindowSize().x / 2) - (RewardsText.getLocalBounds().width / 2), 100.0f);
	StrengthText.setPosition((Engine::getWindowSize().x / 4) - (StrengthText.getLocalBounds().width / 2), 300.0f);
	HealthText.setPosition(((Engine::getWindowSize().x / 4) * 2) - (HealthText.getLocalBounds().width / 2), 300.0f);
	DexterityText.setPosition(((Engine::getWindowSize().x / 34) * 3) - (DexterityText.getLocalBounds().width / 2), 300.0f);
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