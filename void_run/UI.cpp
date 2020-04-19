#include "UI.h"
#include "cmp_player.h"
#include "system_renderer.h"
#include "game.h"

sf::Color Green(0, 255, 0, 255);
sf::Color White(255, 255, 255, 255);

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
	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);

	if (GameOverButtonBox.contains(cursPos))
	{
		GameOverButton.setColor(Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Engine::ChangeScene(&menuScene);
		}
	}
	else
	{
		GameOverButton.setColor(White);
	}
}

bool GameUI::updateStatOptions()
{
	statUp();
	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);
	if (inStatUp)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (stat1Box.contains(cursPos))
			{
				player->addStats(10, 0, 0);
				inStatUp = false;
				return false;
			}
			if (stat2Box.contains(cursPos))
			{
				player->addStats(0, 20, 0);
				inStatUp = false;
				return false;
			}
			if (stat3Box.contains(cursPos))
			{
				player->addStats(0, 0, 10);
				inStatUp = false;
				return false;
			}
		}
	}
	return true;
}

void GameUI::Render()
{
	for (auto& e : cells)
	{
		Renderer::queue(&e);
	}
	Renderer::queue(&descText);
	if (inStatUp) {
		Renderer::queue(&stat1);
		Renderer::queue(&stat2);
		Renderer::queue(&stat3);
		Renderer::queue(&RewardsText);
		Renderer::queue(&DexterityText);
		Renderer::queue(&HealthText);
		Renderer::queue(&StrengthText);
	}

	if (player->getCurrentHealth() == 0)
	{
		Renderer::queue(&GameOverButton);
	}
}

void GameUI::Load(int maxAP, std::shared_ptr<BasePlayerComponent> p)
{
	player = p;
	inStatUp = false;

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

	stat1Box = stat1.getGlobalBounds();
	stat2Box = stat2.getGlobalBounds();
	stat3Box = stat3.getGlobalBounds();

	RewardsText.setFont(font);
	StrengthText.setFont(font);
	HealthText.setFont(font);
	DexterityText.setFont(font);
	RewardsText.setCharacterSize(60);
	StrengthText.setCharacterSize(30);
	HealthText.setCharacterSize(30);
	DexterityText.setCharacterSize(30);
	RewardsText.setString("REWARDS");
	StrengthText.setString("Strength - " + std::to_string(player->getStrength()));
	HealthText.setString("Max Health - " + std::to_string(player->getMaxHealth()));
	DexterityText.setString("Dexterity - " + std::to_string(player->getDexterity()));
	RewardsText.setPosition((Engine::getWindowSize().x / 2) - (RewardsText.getLocalBounds().width / 2), 100.0f);
	StrengthText.setPosition(stat1.getPosition().x - StrengthText.getLocalBounds().width, 300.0f);
	HealthText.setPosition(stat2.getPosition().x - HealthText.getLocalBounds().width, 300.0f);
	DexterityText.setPosition(stat3.getPosition().x - DexterityText.getLocalBounds().width, 300.0f);

	GameOverButton.setFont(font);
	GameOverButton.setString("Gg idiot");
	GameOverButton.setCharacterSize(60);
	GameOverButton.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.0f - (GameOverButton.getGlobalBounds().width / 2),
		Engine::getWindowSize().y / 2.0f - (GameOverButton.getGlobalBounds().height / 2) + 100.0f));
	GameOverButtonBox = GameOverButton.getGlobalBounds();
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

void GameUI::statUp()
{
	inStatUp = true;
	StrengthText.setString("Strength + 10");
	HealthText.setString("Max Health + 20 ");
	DexterityText.setString("Current Dex + 10 ");
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