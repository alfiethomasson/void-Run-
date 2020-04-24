#include "UI.h"
#include "cmp_player.h"
#include "Game.h"

void CombatUI::Render()
{
 	Renderer::queue(&attackSprite);
	Renderer::queue(&specialSprite);
	Renderer::queue(&healSprite);
	Renderer::queue(&rechargeSprite);
	Renderer::queue(&runSprite);
	Renderer::queue(&attackControl);
	Renderer::queue(&healControl);
	Renderer::queue(&rechargeControl);
	Renderer::queue(&runControl);
	Renderer::queue(&attackCost);
	Renderer::queue(&healCost);
	Renderer::queue(&rechargeCost);
	Renderer::queue(&runCost);
}

void CombatUI::turnUpdate()
{

}

void CombatUI::Load(std::shared_ptr<BasePlayerComponent> p, TextureManager* tm)
{
	player = p;
	texManager = tm;

	attackSprite.setTexture(Engine::tm.getTex("Attack"));
	attackSprite.setScale(0.3f, 0.3f);
	attackSprite.setPosition(sf::Vector2f(400.0f, 600.0f));
	attackBox = attackSprite.getGlobalBounds();
	texManager->addButton("attackBox", attackBox);

	healSprite.setTexture(Engine::tm.getTex("Heal"));
	healSprite.setScale(0.3f, 0.3f);
	healSprite.setPosition(sf::Vector2f(500.0f, 600.0f));
	healBox = healSprite.getGlobalBounds();

	rechargeSprite.setTexture(Engine::tm.getTex("Recharge"));
	rechargeSprite.setScale(0.3f, 0.3f);
	rechargeSprite.setPosition(sf::Vector2f(600.0f, 600.0f));
	rechargeBox = rechargeSprite.getGlobalBounds();

	runSprite.setTexture(Engine::tm.getTex("Run"));
	runSprite.setScale(0.3f, 0.3f);
	runSprite.setPosition(sf::Vector2f(700.0f, 600.0f));
	runBox = runSprite.getGlobalBounds();

	specialSprite.setPosition(sf::Vector2f(800.0f, 600.0f));
	specialBox = specialSprite.getGlobalBounds();

	if (!font.loadFromFile("res/Fonts/mandalore.ttf"))
	{
		std::cout << "couldnt load font combat ui\n";
	}

	attackControl.setFont(font);
	healControl.setFont(font);
	rechargeControl.setFont(font);
	runControl.setFont(font);
	
	attackControl.setCharacterSize(30);
	healControl.setCharacterSize(30);
	rechargeControl.setCharacterSize(30);
	runControl.setCharacterSize(30);

	UpdateControls();

	attackCost.setFont(font);
	healCost.setFont(font);
	rechargeCost.setFont(font);
	runCost.setFont(font);
	specialCost1.setFont(font);
	specialCost2.setFont(font);
	specialCost3.setFont(font);

	attackCost.setCharacterSize(25);
	healCost.setCharacterSize(25);
	rechargeCost.setCharacterSize(25);
	runCost.setCharacterSize(25);

	attackCost.setColor(sf::Color(30, 216, 255, 255));
	healCost.setColor(sf::Color(30, 216, 255, 255));
	rechargeCost.setColor(sf::Color(30, 216, 255, 255));
	runCost.setColor(sf::Color(30, 216, 255, 255));

	UpdateCosts();
	std::cout << "UI SIZE = " << texManager->getButtonMap().size();
}

sf::FloatRect& CombatUI::getAttackBox()
{
	//std::cout << "attack sprite is at: " << attackSprite.getPosition() << "\n";
	//return attackSprite.getTextureRect();
	return attackBox;
}

sf::FloatRect& CombatUI::getHealBox()
{
	return healBox;
}

sf::FloatRect& CombatUI::getRechargeBox()
{
	return rechargeBox;
}

sf::FloatRect& CombatUI::getRunBox()
{
	return runBox;
}

bool CombatUI::CheckBoxes(sf::Vector2f curspos)
{
	if (attackSprite.getTextureRect().contains((sf::Vector2i)curspos) || specialBox.contains(curspos) || healBox.contains(curspos)
		|| rechargeBox.contains(curspos) || runBox.contains(curspos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CombatUI::addSpecial(std::string texName)
{
	specialSprite.setTexture(Engine::tm.getTex(texName));
	specialSprite.setPosition(sf::Vector2f(600.0f, 600.0f));
	specialSprite.setScale(0.3f, 0.3f);
}

void CombatUI::resetSpecial()
{
	specialSprite = sf::Sprite();
}

void CombatUI::UpdateControls()
{
	attackControl.setString(Engine::keyToString(attackKey));
	healControl.setString(Engine::keyToString(healKey));
	rechargeControl.setString(Engine::keyToString(rechargeKey));
	runControl.setString(Engine::keyToString(runKey));

	attackControl.setPosition(attackSprite.getPosition().x + (attackSprite.getGlobalBounds().width / 2)
		- (attackControl.getGlobalBounds().width / 2), 680.0f);
	healControl.setPosition(healSprite.getPosition().x + (healSprite.getGlobalBounds().width / 2)
		- (healControl.getGlobalBounds().width / 2), 680.0f);
	rechargeControl.setPosition(rechargeSprite.getPosition().x + (rechargeSprite.getGlobalBounds().width / 2)
		- (rechargeControl.getGlobalBounds().width / 2), 680.0f);
	runControl.setPosition(runSprite.getPosition().x + (runSprite.getGlobalBounds().width / 2)
		- (runControl.getGlobalBounds().width / 2), 680.0f);
}

void CombatUI::UpdateCosts()
{
	std::cout << " player attackcost " << std::to_string(player->baseAttackCost);
	attackCost.setString(std::to_string(player->baseAttackCost));
	healCost.setString(std::to_string(player->healCost));
	rechargeCost.setString(std::to_string(player->rechargeCost));
	runCost.setString(std::to_string(player->runCost));

	attackCost.setPosition(attackSprite.getPosition().x + attackSprite.getGlobalBounds().width - costOffset -
		(attackCost.getGlobalBounds().width), attackSprite.getPosition().y  + costOffset - (attackCost.getGlobalBounds().height / 2));
	healCost.setPosition(healSprite.getPosition().x + healSprite.getGlobalBounds().width - costOffset -
		healCost.getGlobalBounds().width, rechargeSprite.getPosition().y + costOffset - (rechargeCost.getGlobalBounds().height / 2));
	rechargeCost.setPosition(rechargeSprite.getPosition().x + rechargeSprite.getGlobalBounds().width - costOffset -
		rechargeCost.getGlobalBounds().width, rechargeSprite.getPosition().y + costOffset - (rechargeCost.getGlobalBounds().height / 2));
	runCost.setPosition(runSprite.getPosition().x + runSprite.getGlobalBounds().width - costOffset -
		runCost.getGlobalBounds().width, runSprite.getPosition().y + costOffset - (runCost.getGlobalBounds().height / 2));
}

void GameUI::Update(double dt)
{

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
	Renderer::queue(&background);

	for (auto& e : cells)
	{
		Renderer::queue(&e);
	}
	Renderer::queue(&playerIcon);
	if (inStatUp)
	{
		Renderer::queue(&stat1);
		Renderer::queue(&stat2);
		Renderer::queue(&stat3);
		Renderer::queue(&RewardsText);
		Renderer::queue(&DexterityText);
		Renderer::queue(&HealthText);
		Renderer::queue(&StrengthText);
	}
}

void GameUI::Load(int maxAP, std::shared_ptr<BasePlayerComponent> p)
{
	player = p;
	inStatUp = false;
	MaxAP = maxAP;
	APAmount = 0;
	cells.clear();
	height = 0;

	gainAP(MaxAP);
	if (!font.loadFromFile("res/Fonts/mandalore.ttf"))
	{
		std::cout << "failed to load mandalore font in game ui\n";
	}
	descText.setFont(font);
	descText.setCharacterSize(30);
	descText.setString("");

	playerIcon.setTexture(Engine::tm.getTex("Player"));
	playerIcon.setScale(0.5f, 0.5f);
	playerIcon.setPosition(0.0f, 500.0f);

	stat1.setTexture(Engine::tm.getTex("StatUp"));
	stat2.setTexture(Engine::tm.getTex("StatUp"));
	stat3.setTexture(Engine::tm.getTex("StatUp"));
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

	background.setTexture(Engine::tm.getTex("Background1"));
	background.setScale(Engine::getWindowSize().x / background.getGlobalBounds().width, 0.5f);
}

sf::Sprite GameUI::getNewCell()
{
	sf::Sprite cell;
	cell.setTexture(Engine::tm.getTex("Charge"));
	cell.setScale(0.05f, 0.15f);
	height += 20;
	cell.setPosition(sf::Vector2f(550.0f + height, 550.0));
	cell.setRotation(90);
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
	std::cout << "GAMEUI GAINING AP: " << amount << "\n";
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