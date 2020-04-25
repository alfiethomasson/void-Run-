#include "UI.h"
#include "cmp_player.h"
#include "system_renderer.h"
#include "game.h"

sf::Color Green(0, 255, 0, 255);
sf::Color White(255, 255, 255, 255);
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

void CombatUI::Update(double dt, sf::Vector2f cursPos)
{
	if (CheckBoxes(cursPos))
	{
		if (getAttackBox().contains(cursPos))
		{
			//std::cout << "HEY";
			gameScene.UpdateDesctext("ATTACK ENEMY\nDamage = " + std::to_string(player->getStrength()), sf::Vector2f(attackBox.getPosition().x,
				attackBox.getPosition().y - 75.0f));
		}
		if (healBox.contains(cursPos))
		{
			gameScene.UpdateDesctext("HEAL\nAmount = " + std::to_string(30), sf::Vector2f(healBox.getPosition().x,
				healBox.getPosition().y - 75.0f));
		}
		if (rechargeBox.contains(cursPos))
		{
			gameScene.UpdateDesctext("RECHARGE ENERGY\nAmount = " + std::to_string(6), sf::Vector2f(rechargeBox.getPosition().x,
				rechargeBox.getPosition().y - 75.0f));

		}
		if (runBox.contains(cursPos))
		{
			gameScene.UpdateDesctext("RUN FROM ENEMY\nChance = " + std::to_string(player->getRunChance()), sf::Vector2f(runBox.getPosition().x,
				runBox.getPosition().y - 75.0f));
		}
	}
	else
	{
		gameScene.ResetDescText();
	}
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
				player->addStats(5, 0, 0);
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50 * soundVolume / 100 * masterVolume / 100);
				sound.play();
				inStatUp = false;
				return false;
			}
			if (stat2Box.contains(cursPos))
			{
				player->addStats(0, 10, 0);
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50 * soundVolume / 100 * masterVolume / 100);
				sound.play();
				inStatUp = false;
				return false;
			}
			if (stat3Box.contains(cursPos))
			{
				player->addStats(0, 0, 5);
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50 * soundVolume/100 * masterVolume/100);
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

	if (player->getCurrentHealth() == 0)
	{
		Renderer::queue(&GameOverButton);
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
	descText.setFont(Engine::tm.getFont());
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
	stat1.setPosition((Engine::getWindowSize().x / 2) - 275.0f, 500.0f);
	stat2.setPosition(Engine::getWindowSize().x / 2 , 500.0f);
	stat3.setPosition((Engine::getWindowSize().x / 2) + 275.0f, 500.0f);
	std::cout << "WINDOW 1 POS" << Engine::getWindowSize().x << "\n";

	stat1Box = stat1.getGlobalBounds();
	stat2Box = stat2.getGlobalBounds();
	stat3Box = stat3.getGlobalBounds();

	strengthUp = 5;
	hpUp = 10;
	dexUp = 5;

	RewardsText.setFont(Engine::tm.getFont());
	StrengthText.setFont(Engine::tm.getFont());
	HealthText.setFont(Engine::tm.getFont());
	DexterityText.setFont(Engine::tm.getFont());
	RewardsText.setCharacterSize(60);
	StrengthText.setCharacterSize(25);
	HealthText.setCharacterSize(25);
	DexterityText.setCharacterSize(25);
	RewardsText.setString("REWARDS");
	//std::string strengthstr = "Max HP \n +10";
	StrengthText.setString("Max HP + 10");
	HealthText.setString("Strength +5 ");
	DexterityText.setString("Dexterity +5 ");
	RewardsText.setPosition((Engine::getWindowSize().x / 2) - (RewardsText.getLocalBounds().width / 2), 100.0f);
	StrengthText.setPosition(stat1.getPosition().x - (StrengthText.getGlobalBounds().width / 2), 400.0f);
	HealthText.setPosition(stat2.getPosition().x - (HealthText.getLocalBounds().width / 2), 400.0f);
	DexterityText.setPosition(stat3.getPosition().x - (DexterityText.getLocalBounds().width / 2), 400.0f);
	HealthText.setFillColor(sf::Color(220, 20, 60, 255));
	StrengthText.setFillColor(sf::Color(0, 0, 205, 255));
	DexterityText.setFillColor(sf::Color(0, 255, 127, 255));

	background.setTexture(Engine::tm.getTex("Background1"));
	background.setScale(Engine::getWindowSize().x / background.getGlobalBounds().width, 0.7f);

	GameOverButton.setFont(font);
	GameOverButton.setString("Gg idiot");
	GameOverButton.setCharacterSize(60);
	GameOverButton.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.0f - (GameOverButton.getGlobalBounds().width / 2),
		Engine::getWindowSize().y / 2.0f - (GameOverButton.getGlobalBounds().height / 2) + 100.0f));
	GameOverButtonBox = GameOverButton.getGlobalBounds();
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
	HealthText.setString("Max Health\n    + " + std::to_string(hpUp));
	StrengthText.setString("Strength\n    + " + std::to_string(strengthUp));
	DexterityText.setString("Dexterity\n  + " + std::to_string(dexUp));
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
	sound.setVolume(volume * soundVolume/100 * masterVolume/100);
	sound.play();
}

void SettingUI::Update(const double& dt, sf::Vector2f cursPos)
{
	delayTime = delayClock.getElapsedTime().asSeconds();

	if (ResButtonBox.contains(cursPos))
	{
		ResButton.setColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left) && delayTime >= delayAmount)
		{
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.play();
			delayClock.restart();
			if (Engine::getWindowSize().y == 1080)
			{
				if (!Engine::getFullscreen())
				{
					ResChange.setString("FS");
					Engine::SetFullScreen(Engine::GetWindow(), true);
				}
				else
				{
					ResChange.setString("720p");
					Engine::SetFullScreen(Engine::GetWindow(), false);
					Engine::ChangeResolution(1280, 720, GAMEX, GAMEY);
				}
			}
			else
			{
				Engine::ChangeResolution(1920, 1080, GAMEX, GAMEY);
			}
		}
	}
	else
	{
		ResButton.setColor(White);
	}

	if (MasterLeftBox.contains(cursPos))
	{
		MasterLeft.setFillColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left) && delayTime >= volumeDelayAmount)
		{
			delayClock.restart();
			if (masterVolume > 0)
			{
				sound.setVolume(soundVolume * masterVolume / 100);
				sound.play();
				masterVolume -= 1;
			}
			MasterText.setString("Master Volume: " + std::to_string(masterVolume));
		}
	}
	else
	{
		MasterLeft.setFillColor(White);
	}
	if (MasterRightBox.contains(cursPos))
	{
		MasterRight.setFillColor(Green);
		if(Mouse::isButtonPressed(Mouse::Left) && delayTime >= volumeDelayAmount)
		{
			delayClock.restart();
			if (masterVolume < 100)
			{
				sound.setVolume(soundVolume * masterVolume / 100);
				sound.play();
				masterVolume += 1;
			}
			MasterText.setString("Master Volume: " + std::to_string(masterVolume));
		}
	}
	else
	{
		MasterRight.setFillColor(White);
	}
	if (MusicLeftBox.contains(cursPos))
	{
		MusicLeft.setFillColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left) && delayTime >= volumeDelayAmount)
		{
			delayClock.restart();
			if (musicVolume > 0)
			{
				sound.setVolume(soundVolume * masterVolume / 100);
				sound.play();
				musicVolume -= 1;
			}
			MusicText.setString("Music Volume: " + std::to_string(musicVolume));
		}
	}
	else
	{
		MusicLeft.setFillColor(White);
	}
	if (MusicRightBox.contains(cursPos))
	{
		MusicRight.setFillColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left) && delayTime >= volumeDelayAmount)
		{
			delayClock.restart();
			if (musicVolume < 100)
			{
				sound.setVolume(soundVolume * masterVolume / 100);
				sound.play();
				musicVolume += 1;
			}
			MusicText.setString("Music Volume: " + std::to_string(musicVolume));
		}
	}
	else
	{
		MusicRight.setFillColor(White);
	}
	if (FXLeftBox.contains(cursPos))
	{
		FXLeft.setFillColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left) && delayTime >= volumeDelayAmount)
		{
			delayClock.restart();
			if (soundVolume > 0)
			{
				sound.setVolume(soundVolume* masterVolume / 100);
				sound.play();
				soundVolume -= 1;
			}
			FXText.setString("FX Volume: " + std::to_string(soundVolume));
		}
	}
	else
	{
		FXLeft.setFillColor(White);
	}
	if (FXRightBox.contains(cursPos))
	{
		FXRight.setFillColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left) && delayTime >= volumeDelayAmount)
		{
			delayClock.restart();
			if (soundVolume < 100)
			{
				sound.setVolume(soundVolume* masterVolume / 100);
				sound.play();
				soundVolume += 1;
			}
			FXText.setString("FX Volume: " + std::to_string(soundVolume));
		}
	}
	else
	{
		FXRight.setFillColor(White);
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) && delayTime >= delayAmount)
	{
		sound.setVolume(soundVolume* masterVolume / 100);
		sound.play();
		delayClock.restart();
		if (Engine::getWindowSize().y != 1080)
		{
			ResChange.setString("1080p");
			Engine::ChangeResolution(1920, 1080, GAMEX, GAMEY);
		}
		else
		{
			ResChange.setString("720p");
			Engine::ChangeResolution(1280, 720, GAMEX, GAMEY);
		}
	}

	if(AttackBox.contains(cursPos))
	{
		CheckKeyPress(AttackKeyText, AttackBox, attackKey);
	}
	else if (HealBox.contains(cursPos))
	{
		CheckKeyPress(HealKeyText, HealBox, healKey);
	}
	else if (RechargeBox.contains(cursPos))
	{
		CheckKeyPress(RechargeKeyText, RechargeBox, rechargeKey);
	}
	else if (RunBox.contains(cursPos))
	{
		CheckKeyPress(RunKeyText, RunBox, runKey);
	}
	else if (Special1Box.contains(cursPos))
	{
		CheckKeyPress(Special1KeyText, Special1Box, special1Key);
	}
	else if (Special2Box.contains(cursPos))
	{
		CheckKeyPress(Special2KeyText, Special2Box, special2Key);
	}
	else if (Special3Box.contains(cursPos))
	{
		CheckKeyPress(Special3KeyText, Special3Box, special3Key);
	}
	else if (Special4Box.contains(cursPos))
	{
		CheckKeyPress(Special4KeyText, Special4Box, special4Key);
	}
	else if (PauseBox.contains(cursPos))
	{
		CheckKeyPress(PauseKeyText, PauseBox, pauseKey);
	}
	
	if (ResetBox.contains(cursPos))
	{
		ResetControls.setColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			sound.setVolume(soundVolume* masterVolume / 100);
			sound.play();
			ResetKeys();
		}
	}
	else
	{
		ResetControls.setColor(White);
	}

	if (BackBox.contains(cursPos))
	{
		BackButton.setColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			sound.setVolume(soundVolume* masterVolume / 100);
			sound.play();
			menuScene.setSettings(false);
			gameScene.setPause(false);
		}
	}
	else
	{
		BackButton.setColor(White);
	}

	if (Keyboard::isKeyPressed(Keyboard::BackSpace))
	{
		sound.setVolume(soundVolume* masterVolume / 100);
		sound.play();
		menuScene.setSettings(false);
		gameScene.setPause(false);
	}

}

void SettingUI::Load()
{
	sound.setBuffer(Engine::tm.getSound("ButtonPress"));

	ResChange.setFont(Engine::tm.getFont());
	ResText.setFont(Engine::tm.getFont());
	ResButton.setFont(Engine::tm.getFont());
	MasterText.setFont(Engine::tm.getFont());
	MusicText.setFont(Engine::tm.getFont());
	FXText.setFont(Engine::tm.getFont());
	//MasterTextVolume.setFont(Engine::tm.getFont());
	//MusicTextVolume.setFont(Engine::tm.getFont());
	//FXTextVolume.setFont(Engine::tm.getFont());
	MasterLeft.setFont(Engine::tm.getFont());
	MasterRight.setFont(Engine::tm.getFont());
	MusicLeft.setFont(Engine::tm.getFont());
	MusicRight.setFont(Engine::tm.getFont());
	FXLeft.setFont(Engine::tm.getFont());
	FXRight.setFont(Engine::tm.getFont());
	BackButton.setFont(Engine::tm.getFont());
	AttackText.setFont(Engine::tm.getFont());
	HealText.setFont(Engine::tm.getFont());
	RechargeText.setFont(Engine::tm.getFont());
	RunText.setFont(Engine::tm.getFont());
	Special1Text.setFont(Engine::tm.getFont());
	Special2Text.setFont(Engine::tm.getFont());
	Special3Text.setFont(Engine::tm.getFont());
	Special4Text.setFont(Engine::tm.getFont());
	PauseText.setFont(Engine::tm.getFont());
	AttackKeyText.setFont(Engine::tm.getFont());
	HealKeyText.setFont(Engine::tm.getFont());
	RechargeKeyText.setFont(Engine::tm.getFont());
	RunKeyText.setFont(Engine::tm.getFont());
	Special1KeyText.setFont(Engine::tm.getFont());
	Special2KeyText.setFont(Engine::tm.getFont());
	Special3KeyText.setFont(Engine::tm.getFont());
	Special4KeyText.setFont(Engine::tm.getFont());
	PauseKeyText.setFont(Engine::tm.getFont());
	ResetControls.setFont(Engine::tm.getFont());
	HowToText.setFont(Engine::tm.getFont());

	BackButton.setString("BACK - BACKSPACE");
	BackButton.setCharacterSize(40);
	BackButton.setPosition(sf::Vector2f(1300.0f, 975.0f));
	BackBox = BackButton.getGlobalBounds();

	ResChange.setString("1080p"); //Starts at 720p
	ResChange.setCharacterSize(60);
	ResChange.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.0f + 100.0f, 50.0f));
	ResText.setString("Resolution: ");
	ResText.setCharacterSize(60);
	ResText.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.0f - 500.0f, 50.0f));
	ResButton.setString(" > ");
	ResButton.setCharacterSize(100);
	ResButton.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.0f + 380.0f, 20.0f));
	ResButtonBox = ResButton.getGlobalBounds();

	MasterText.setString("Master Volume: " + std::to_string(masterVolume));
	MasterText.setCharacterSize(40);
	MasterText.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2 - 350.0f, 150.0f));
	MusicText.setString("Music Volume: " + std::to_string(musicVolume));
	MusicText.setCharacterSize(40);
	MusicText.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2 - 350.0f, 200.0f));
	FXText.setString("FX Volume: " + std::to_string(soundVolume));
	FXText.setCharacterSize(40);
	FXText.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2 - 300.0f, 250.0f));

	/*MasterTextVolume.setString(std::to_string(masterVolume));
	MasterTextVolume.setCharacterSize(40);
	MasterTextVolume.setPosition(MasterText.getPosition().x + MasterText.getGlobalBounds().width
	+ 50.0f, MasterText.getPosition().y);
	MasterVolumeBox = MasterTextVolume.getGlobalBounds();
	MusicTextVolume.setString(std::to_string(musicVolume));
	MusicTextVolume.setCharacterSize(40);
	MusicTextVolume.setPosition(MusicText.getPosition().x + MasterText.getGlobalBounds().width
		+ 50.0f, MusicText.getPosition().y);
	MusicVolumeBox = MusicTextVolume.getGlobalBounds();
	FXTextVolume.setString(std::to_string(soundVolume));
	FXTextVolume.setCharacterSize(40);
	FXTextVolume.setPosition(FXText.getPosition().x + MasterText.getGlobalBounds().width
		+ 50.0f, FXText.getPosition().y);
	FXVolumeBox = FXTextVolume.getGlobalBounds();*/

	MasterLeft.setString("<");
	MasterRight.setString(">");
	MasterLeft.setCharacterSize(40);
	MasterRight.setCharacterSize(40);
	MasterLeft.setPosition(MasterText.getPosition().x + MasterText.getGlobalBounds().width + 50.0f, MasterText.getPosition().y);
	MasterRight.setPosition(MasterText.getPosition().x + MasterText.getGlobalBounds().width + 100.0f, MasterText.getPosition().y);
	MasterLeftBox = MasterLeft.getGlobalBounds();
	MasterRightBox = MasterRight.getGlobalBounds();

	MusicLeft.setString("<");
	MusicRight.setString(">");
	MusicLeft.setCharacterSize(40);
	MusicRight.setCharacterSize(40);
	MusicLeft.setPosition(MusicText.getPosition().x + MusicText.getGlobalBounds().width + 50.0f, MusicText.getPosition().y);
	MusicRight.setPosition(MusicText.getPosition().x + MusicText.getGlobalBounds().width + 100.0f, MusicText.getPosition().y);
	MusicLeftBox = MusicLeft.getGlobalBounds();
	MusicRightBox = MusicRight.getGlobalBounds();

	FXLeft.setString("<");
	FXRight.setString(">");
	FXLeft.setCharacterSize(40);
	FXRight.setCharacterSize(40);
	FXLeft.setPosition(FXText.getPosition().x + FXText.getGlobalBounds().width + 50.0f, FXText.getPosition().y);
	FXRight.setPosition(FXText.getPosition().x + FXText.getGlobalBounds().width + 100.0f, FXText.getPosition().y);
	FXLeftBox = FXLeft.getGlobalBounds();
	FXRightBox = FXRight.getGlobalBounds();

	//FXText.setString("FX Volume: ");
	//FXText.setCharacterSize(40);
	//FXText.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2 - 300.0f, 200.0f));

	AttackText.setString("Attack Key: ");
	AttackText.setCharacterSize(40);
	AttackText.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- AttackText.getGlobalBounds().width, 300.0f));
	HealText.setString("Heal Key  ");
	HealText.setCharacterSize(40);
	HealText.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- HealText.getGlobalBounds().width, 350.0f));
	RechargeText.setString("Recharge Key: ");
	RechargeText.setCharacterSize(40);
	RechargeText.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- RechargeText.getGlobalBounds().width, 400.0f));
	RunText.setString("Run Key: ");
	RunText.setCharacterSize(40);
	RunText.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- RunText.getGlobalBounds().width, 450.0f));
	Special1Text.setString("Special 1 Key: ");
	Special1Text.setCharacterSize(40);
	Special1Text.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- Special1Text.getGlobalBounds().width, 500.0f));
	Special2Text.setString("Special 2 Key: ");
	Special2Text.setCharacterSize(40);
	Special2Text.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- Special2Text.getGlobalBounds().width, 550.0f));
	Special3Text.setString("Special 3 Key: ");
	Special3Text.setCharacterSize(40);
	Special3Text.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- Special3Text.getGlobalBounds().width, 600.0f));
	Special4Text.setString("Special 4 Key: ");
	Special4Text.setCharacterSize(40);
	Special4Text.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- Special4Text.getGlobalBounds().width, 650.0f));
	PauseText.setString("Pause Key: ");
	PauseText.setCharacterSize(40);
	PauseText.setPosition(sf::Vector2f((Engine::getWindowSize().x / 2)
		- PauseText.getGlobalBounds().width, 700.0f));

	AttackKeyText.setString(Engine::keyToString(attackKey));
	AttackKeyText.setCharacterSize(40);
	AttackKeyText.setPosition(AttackText.getPosition().x + AttackText.getGlobalBounds().width + 75.0f, AttackText.getPosition().y);
	AttackBox = AttackKeyText.getGlobalBounds();
	HealKeyText.setString(Engine::keyToString(healKey));
	HealKeyText.setCharacterSize(40);
	HealKeyText.setPosition(HealText.getPosition().x + HealText.getGlobalBounds().width + 75.0f, HealText.getPosition().y);
	HealBox = HealKeyText.getGlobalBounds();
	RechargeKeyText.setString(Engine::keyToString(rechargeKey));
	RechargeKeyText.setCharacterSize(40);
	RechargeKeyText.setPosition(RechargeText.getPosition().x + RechargeText.getGlobalBounds().width + 75.0f, RechargeText.getPosition().y);
	RechargeBox = RechargeKeyText.getGlobalBounds();
	RunKeyText.setString(Engine::keyToString(runKey));
	RunKeyText.setCharacterSize(40);
	RunKeyText.setPosition(RunText.getPosition().x + RunText.getGlobalBounds().width + 75.0f, RunText.getPosition().y);
	RunBox = RunKeyText.getGlobalBounds();
	Special1KeyText.setString(Engine::keyToString(special1Key));
	Special1KeyText.setCharacterSize(40);
	Special1KeyText.setPosition(Special1Text.getPosition().x + Special1Text.getGlobalBounds().width + 75.0f, Special1Text.getPosition().y);
	Special1Box = Special1KeyText.getGlobalBounds();
	Special2KeyText.setString(Engine::keyToString(special2Key));
	Special2KeyText.setCharacterSize(40);
	Special2KeyText.setPosition(Special2Text.getPosition().x + Special2Text.getGlobalBounds().width + 75.0f, Special2Text.getPosition().y);
	Special2Box = Special2KeyText.getGlobalBounds();
	Special3KeyText.setString(Engine::keyToString(special3Key));
	Special3KeyText.setCharacterSize(40);
	Special3KeyText.setPosition(Special3Text.getPosition().x + Special3Text.getGlobalBounds().width + 75.0f, Special3Text.getPosition().y);
	Special3Box = Special3KeyText.getGlobalBounds();
	Special4KeyText.setString(Engine::keyToString(special4Key));
	Special4KeyText.setCharacterSize(40);
	Special4KeyText.setPosition(Special4Text.getPosition().x + Special4Text.getGlobalBounds().width + 75.0f, Special4Text.getPosition().y);
	Special4Box = Special4KeyText.getGlobalBounds();
	PauseKeyText.setString(Engine::keyToString(pauseKey));
	PauseKeyText.setCharacterSize(40);
	PauseKeyText.setPosition(PauseText.getPosition().x + PauseText.getGlobalBounds().width + 75.0f, PauseText.getPosition().y);
	PauseBox = PauseKeyText.getGlobalBounds();

	ResetControls.setString("Reset Controls  ");
	ResetControls.setCharacterSize(50);
	ResetControls.setPosition((Engine::getWindowSize().x / 2) - (ResetControls.getGlobalBounds().width / 2), 800.0f);
	ResetBox = ResetControls.getGlobalBounds();

	HowToText.setString("To change controls hover\nmouse over key and hold down\n new key on keyboard");
	HowToText.setCharacterSize(25);
	HowToText.setPosition(1200.0f, 400.0f);
}

void SettingUI::Render()
{
	Renderer::queue(&ResButton);
	Renderer::queue(&ResChange);
	Renderer::queue(&ResText);
	Renderer::queue(&MasterText);
	Renderer::queue(&MusicText);
	Renderer::queue(&FXText);
	Renderer::queue(&MasterLeft);
	Renderer::queue(&MasterRight);
	Renderer::queue(&MusicLeft);
	Renderer::queue(&MusicRight);
	Renderer::queue(&FXLeft);
	Renderer::queue(&FXRight);
	Renderer::queue(&AttackText);
	Renderer::queue(&HealText);
	Renderer::queue(&RechargeText);
	Renderer::queue(&RunText);
	Renderer::queue(&PauseText);
	Renderer::queue(&Special1Text);
	Renderer::queue(&Special2Text);
	Renderer::queue(&Special3Text);
	Renderer::queue(&Special4Text);
	Renderer::queue(&AttackKeyText);
	Renderer::queue(&HealKeyText);
	Renderer::queue(&RechargeKeyText);
	Renderer::queue(&RunKeyText);
	Renderer::queue(&PauseKeyText);
	Renderer::queue(&Special1KeyText);
	Renderer::queue(&Special2KeyText);
	Renderer::queue(&Special3KeyText);
	Renderer::queue(&Special4KeyText);
	Renderer::queue(&ResetControls);
	Renderer::queue(&BackButton);
	Renderer::queue(&HowToText);
}

void SettingUI::ResetKeys()
{
	AttackKeyText.setString("1");
	HealKeyText.setString("2");
	RechargeKeyText.setString("3");
	RunKeyText.setString("4");
	Special1KeyText.setString("Q");
	Special2KeyText.setString("W");
	Special3KeyText.setString("E");
	Special4KeyText.setString("R");
	PauseKeyText.setString("Tab");

	AttackBox = AttackKeyText.getGlobalBounds();
	HealBox = AttackKeyText.getGlobalBounds();
	RechargeBox = AttackKeyText.getGlobalBounds();
	RunBox = AttackKeyText.getGlobalBounds();
	Special1Box = Special1KeyText.getGlobalBounds();
	Special2Box = Special2KeyText.getGlobalBounds();
	Special3Box = Special3KeyText.getGlobalBounds();
	Special4Box = Special4KeyText.getGlobalBounds();
	PauseBox = PauseKeyText.getGlobalBounds();
}

void SettingUI::CheckKeyPress(sf::Text& changeText, sf::FloatRect& box, sf::Keyboard::Key& key)
{
	sf::Event Event;
	while (Engine::GetWindow().pollEvent(Event))
	{
		if (Event.type == sf::Event::KeyPressed)
		{
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.play();
			key = Event.key.code;
			changeText.setString(Engine::keyToString(Event.key.code));
			box = changeText.getGlobalBounds();
		}
	}
}

void SettingUI::UpdateSettings()
{
	if (!Engine::getFullscreen())
	{
		ResChange.setString(std::to_string(Engine::getWindowSize().y) + "p");
	}
	else
	{
		ResChange.setString("FS");
	}

	AttackKeyText.setString(Engine::keyToString(attackKey));
	HealKeyText.setString(Engine::keyToString(healKey));
	RechargeKeyText.setString(Engine::keyToString(rechargeKey));
	RunKeyText.setString(Engine::keyToString(runKey));
	Special1KeyText.setString(Engine::keyToString(special1Key));
	Special2KeyText.setString(Engine::keyToString(special2Key));
	Special3KeyText.setString(Engine::keyToString(special3Key));
	Special4KeyText.setString(Engine::keyToString(special4Key));
	PauseKeyText.setString(Engine::keyToString(pauseKey));

	AttackBox = AttackKeyText.getGlobalBounds();
	HealBox = AttackKeyText.getGlobalBounds();
	RechargeBox = AttackKeyText.getGlobalBounds();
	RunBox = AttackKeyText.getGlobalBounds();
	Special1Box = Special1KeyText.getGlobalBounds();
	Special2Box = Special2KeyText.getGlobalBounds();
	Special3Box = Special3KeyText.getGlobalBounds();
	Special4Box = Special4KeyText.getGlobalBounds();
	PauseBox = PauseKeyText.getGlobalBounds();

	MasterText.setString("Master Volume: " + std::to_string(masterVolume));
	MusicText.setString("Music Volume: " + std::to_string(musicVolume));
	FXText.setString("FX Volume: " + std::to_string(soundVolume));
}