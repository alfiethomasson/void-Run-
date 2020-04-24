#include "UI.h"
#include "cmp_player.h"
#include "Game.h"

void CombatUI::Render()
{
 	Renderer::queue(&attackSprite);
	Renderer::queue(&healSprite);
	Renderer::queue(&rechargeSprite);
	Renderer::queue(&runSprite);
	Renderer::queue(&special1Sprite);
	Renderer::queue(&special2Sprite);
	Renderer::queue(&special3Sprite);
	Renderer::queue(&special4Sprite);
	Renderer::queue(&attackControl);
	Renderer::queue(&healControl);
	Renderer::queue(&rechargeControl);
	Renderer::queue(&runControl);
	Renderer::queue(&specialControl1);
	Renderer::queue(&specialControl2);
	Renderer::queue(&specialControl3);
	Renderer::queue(&specialControl4);
	Renderer::queue(&attackCost);
	Renderer::queue(&healCost);
	Renderer::queue(&rechargeCost);
	Renderer::queue(&runCost);
	Renderer::queue(&specialCost1);
	Renderer::queue(&specialCost2);
	Renderer::queue(&specialCost3);
	Renderer::queue(&specialCost4);
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
	attackSprite.setPosition(sf::Vector2f(800.0f, 800.0f));
	attackBox = attackSprite.getGlobalBounds();
	texManager->addButton("attackBox", attackBox);

	healSprite.setTexture(Engine::tm.getTex("Heal"));
	healSprite.setScale(0.3f, 0.3f);
	healSprite.setPosition(sf::Vector2f(900.0f, 800.0f));
	healBox = healSprite.getGlobalBounds();

	rechargeSprite.setTexture(Engine::tm.getTex("Recharge"));
	rechargeSprite.setScale(0.3f, 0.3f);
	rechargeSprite.setPosition(sf::Vector2f(1000.0f, 800.0f));
	rechargeBox = rechargeSprite.getGlobalBounds();

	runSprite.setTexture(Engine::tm.getTex("Run"));
	runSprite.setScale(0.3f, 0.3f);
	runSprite.setPosition(sf::Vector2f(1100.0f, 800.0f));
	runBox = runSprite.getGlobalBounds();

	special1Sprite.setPosition(sf::Vector2f(800.0f, 900.0f));

	special2Sprite.setPosition(sf::Vector2f(900.0f, 900.0f));

	special3Sprite.setPosition(sf::Vector2f(1000.0f, 900.0f));

	special4Sprite.setPosition(sf::Vector2f(1100.0f, 900.0f));

	attackControl.setFont(Engine::tm.getFont());
	healControl.setFont(Engine::tm.getFont());
	rechargeControl.setFont(Engine::tm.getFont());
	runControl.setFont(Engine::tm.getFont());
	specialControl1.setFont(Engine::tm.getFont());
	specialControl2.setFont(Engine::tm.getFont());
	specialControl3.setFont(Engine::tm.getFont());
	specialControl4.setFont(Engine::tm.getFont());
	
	attackControl.setCharacterSize(30);
	healControl.setCharacterSize(30);
	rechargeControl.setCharacterSize(30);
	runControl.setCharacterSize(30);
	specialControl1.setCharacterSize(30);
	specialControl2.setCharacterSize(30);
	specialControl3.setCharacterSize(30);
	specialControl4.setCharacterSize(30);

	UpdateControls();

	attackCost.setFont(Engine::tm.getFont());
	healCost.setFont(Engine::tm.getFont());
	rechargeCost.setFont(Engine::tm.getFont());
	runCost.setFont(Engine::tm.getFont());
	specialCost1.setFont(Engine::tm.getFont());
	specialCost2.setFont(Engine::tm.getFont());
	specialCost3.setFont(Engine::tm.getFont());
	specialCost4.setFont(Engine::tm.getFont());

	attackCost.setCharacterSize(25);
	healCost.setCharacterSize(25);
	rechargeCost.setCharacterSize(25);
	runCost.setCharacterSize(25);
	specialCost1.setCharacterSize(25);
	specialCost2.setCharacterSize(25);
	specialCost3.setCharacterSize(25);
	specialCost4.setCharacterSize(25);

	attackCost.setColor(sf::Color(30, 216, 255, 255));
	healCost.setColor(sf::Color(30, 216, 255, 255));
	rechargeCost.setColor(sf::Color(30, 216, 255, 255));
	runCost.setColor(sf::Color(30, 216, 255, 255));
	specialCost1.setColor(sf::Color(30, 216, 255, 255));
	specialCost2.setColor(sf::Color(30, 216, 255, 255));
	specialCost3.setColor(sf::Color(30, 216, 255, 255));
	specialCost4.setColor(sf::Color(30, 216, 255, 255));


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

void CombatUI::addSpecial(std::string texName, std::shared_ptr<SpecialAbility> sp)
{
	if (special1Sprite.getTexture() == NULL)
	{
		special1Sprite.setTexture(Engine::tm.getTex(texName));
		special1Sprite.setScale(0.3f, 0.3f);
		specialCost1.setString(std::to_string(sp->getAPCost()));
		specialControl1.setString(Engine::keyToString(special1Key));
		specialControl1.setPosition(special1Sprite.getPosition().x + (special1Sprite.getGlobalBounds().width / 2)
			- (specialControl1.getGlobalBounds().width / 2), 1000.0f);
	}
	else if (special2Sprite.getTexture() == NULL)
	{
		special2Sprite.setTexture(Engine::tm.getTex(texName));
		special2Sprite.setScale(0.3f, 0.3f);
		specialCost2.setString(std::to_string(sp->getAPCost()));
		specialControl2.setString(Engine::keyToString(special2Key));
		specialControl2.setPosition(special2Sprite.getPosition().x + (special2Sprite.getGlobalBounds().width / 2)
			- (specialControl2.getGlobalBounds().width / 2), 1000.0f);
	}
	else if (special3Sprite.getTexture() == NULL)
	{
		special3Sprite.setTexture(Engine::tm.getTex(texName));
		special3Sprite.setScale(0.3f, 0.3f);
		specialCost3.setString(std::to_string(sp->getAPCost()));
		specialControl3.setString(Engine::keyToString(special3Key));
		specialControl3.setPosition(special3Sprite.getPosition().x + (special3Sprite.getGlobalBounds().width / 2)
			- (specialControl3.getGlobalBounds().width / 2), 1000.0f);
	}
	else if (special4Sprite.getTexture() == NULL)
	{
		special4Sprite.setTexture(Engine::tm.getTex(texName));
		special4Sprite.setScale(0.3f, 0.3f);
		specialCost4.setString(std::to_string(sp->getAPCost()));
		specialControl4.setString(Engine::keyToString(special4Key));
		specialControl4.setPosition(special4Sprite.getPosition().x + (special4Sprite.getGlobalBounds().width / 2)
			- (specialControl4.getGlobalBounds().width / 2), 1000.0f);
	}
}

void CombatUI::resetSpecial()
{
	special1Sprite = sf::Sprite();
	special2Sprite = sf::Sprite();
	special3Sprite = sf::Sprite();
	special4Sprite = sf::Sprite();
}

void CombatUI::UpdateControls()
{
	attackControl.setString(Engine::keyToString(attackKey));
	healControl.setString(Engine::keyToString(healKey));
	rechargeControl.setString(Engine::keyToString(rechargeKey));
	runControl.setString(Engine::keyToString(runKey));

	attackControl.setPosition(attackSprite.getPosition().x + (attackSprite.getGlobalBounds().width / 2)
		- (attackControl.getGlobalBounds().width / 2), 900.0f);
	healControl.setPosition(healSprite.getPosition().x + (healSprite.getGlobalBounds().width / 2)
		- (healControl.getGlobalBounds().width / 2), 900.0f);
	rechargeControl.setPosition(rechargeSprite.getPosition().x + (rechargeSprite.getGlobalBounds().width / 2)
		- (rechargeControl.getGlobalBounds().width / 2), 900.0f);
	runControl.setPosition(runSprite.getPosition().x + (runSprite.getGlobalBounds().width / 2)
		- (runControl.getGlobalBounds().width / 2), 900.0f);
	specialControl1.setPosition(special1Sprite.getPosition().x + (special1Sprite.getGlobalBounds().width / 2)
		- (specialControl1.getGlobalBounds().width / 2), 1000.0f);
	specialControl2.setPosition(special2Sprite.getPosition().x + (special2Sprite.getGlobalBounds().width / 2)
		- (specialControl2.getGlobalBounds().width / 2), 1000.0f);
	specialControl3.setPosition(special3Sprite.getPosition().x + (special3Sprite.getGlobalBounds().width / 2)
		- (specialControl3.getGlobalBounds().width / 2), 1000.0f);
	specialControl4.setPosition(special4Sprite.getPosition().x + (special4Sprite.getGlobalBounds().width / 2)
		- (specialControl3.getGlobalBounds().width / 2), 1000.0f);
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
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50);
				sound.play();
				inStatUp = false;
				return false;
			}
			if (stat2Box.contains(cursPos))
			{
				player->addStats(0, 20, 0);
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50);
				sound.play();
				inStatUp = false;
				return false;
			}
			if (stat3Box.contains(cursPos))
			{
				player->addStats(0, 0, 10);
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50);
				sound.play();
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
	playerIcon.setPosition(0.0f, 800.0f);

	stat1.setTexture(Engine::tm.getTex("StatUp"));
	stat2.setTexture(Engine::tm.getTex("StatUp"));
	stat3.setTexture(Engine::tm.getTex("StatUp"));
	stat1.setScale(0.3f, 0.3f);
	stat2.setScale(0.3f, 0.3f);
	stat3.setScale(0.3f, 0.3f);
	stat1.setRotation(90);
	stat2.setRotation(90);
	stat3.setRotation(90);
	stat1.setPosition(900.0f, 500.0f);
	stat2.setPosition(1000.0f, 500.0f);
	stat3.setPosition(1100.0f, 500.0f);

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
	background.setScale(Engine::getWindowSize().x / background.getGlobalBounds().width, 0.7f);
}

sf::Sprite GameUI::getNewCell()
{
	sf::Sprite cell;
	cell.setTexture(Engine::tm.getTex("Charge"));
	cell.setScale(0.05f, 0.15f);
	height += 20;
	cell.setPosition(sf::Vector2f(800.0f + height, 750.0f));
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

void GameUI::playSound(const std::string& name, int volume)
{
	sound.setBuffer(Engine::tm.getSound(name));
	sound.setVolume(volume);
	sound.play();
}