#include "UI.h"
#include "cmp_player.h"
#include "system_renderer.h"
#include "game.h"

sf::Color Green(0, 255, 0, 255);
sf::Color White(255, 255, 255, 255);
#include "Game.h"

void CombatUI::Render()
{
	//Renders all objects in combat UI
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
	//Checks all UI boxes to see if cursor is in them
	if (CheckBoxes(cursPos))
	{
		//Same for each box, if cursor is
		//in box it calls UpdateDescText and shows the tooltip for the respective ability
		if (attackBox.contains(cursPos))
		{
			gameScene.UpdateDesctext("ATTACK ENEMY\nDamage = " + std::to_string(player->getStrength()), sf::Vector2f(attackBox.getPosition().x,
				attackBox.getPosition().y - 75.0f));
		}
		if (healBox.contains(cursPos))
		{
			gameScene.UpdateDesctext("HEAL\nAmount = " + std::to_string(player->getDexterity()), sf::Vector2f(healBox.getPosition().x,
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
		//Checks all special boxes to see if they are active first, and then if they contain the cursor
		if (special1Sprite.getTexture() != NULL && special1Box.contains(cursPos))
		{
			gameScene.UpdateDesctext(sp1->getDescription(), sf::Vector2f(special1Sprite.getPosition().x, special1Sprite.getPosition().y - 75.0f));
		}
		if (special2Sprite.getTexture() != NULL && special2Box.contains(cursPos))
		{
			gameScene.UpdateDesctext(sp2->getDescription(), sf::Vector2f(special2Sprite.getPosition().x, special2Sprite.getPosition().y - 75.0f));
		}
		if (special3Sprite.getTexture() != NULL && special3Box.contains(cursPos))
		{
			gameScene.UpdateDesctext(sp3->getDescription(), sf::Vector2f(special3Sprite.getPosition().x, special3Sprite.getPosition().y - 75.0f));
		}
		if (special4Sprite.getTexture() != NULL && special4Box.contains(cursPos))
		{
			gameScene.UpdateDesctext(sp4->getDescription(), sf::Vector2f(special4Sprite.getPosition().x, special4Sprite.getPosition().y - 75.0f));
		}
	}
	else
	{
		//Hides the tooltip
		gameScene.ResetDescText();
	}
}

void CombatUI::Load(std::shared_ptr<BasePlayerComponent> p)
{
	//Assigns player
	player = p;

	//Assigns the textures and postions for the base abilities and future special abilities
	attackSprite.setTexture(Engine::tm.getTex("Attack"));
	attackSprite.setScale(0.3f, 0.3f);
	attackSprite.setPosition(sf::Vector2f(790.0f, 800.0f));
	attackBox = attackSprite.getGlobalBounds();

	healSprite.setTexture(Engine::tm.getTex("Heal"));
	healSprite.setScale(0.3f, 0.3f);
	healSprite.setPosition(sf::Vector2f(890.0f, 800.0f));
	healBox = healSprite.getGlobalBounds();

	rechargeSprite.setTexture(Engine::tm.getTex("Recharge"));
	rechargeSprite.setScale(0.3f, 0.3f);
	rechargeSprite.setPosition(sf::Vector2f(990.0f, 800.0f));
	rechargeBox = rechargeSprite.getGlobalBounds();

	runSprite.setTexture(Engine::tm.getTex("Run"));
	runSprite.setScale(0.3f, 0.3f);
	runSprite.setPosition(sf::Vector2f(1090.0f, 800.0f));
	runBox = runSprite.getGlobalBounds();

	special1Sprite.setPosition(sf::Vector2f(790.0f, 925.0f));

	special2Sprite.setPosition(sf::Vector2f(890.0f, 925.0f));

	special3Sprite.setPosition(sf::Vector2f(990.0f, 925.0f));

	special4Sprite.setPosition(sf::Vector2f(1090.0f, 925.0f));

	//Sets fonts for all control text in UI
	attackControl.setFont(Engine::tm.getFont());
	healControl.setFont(Engine::tm.getFont());
	rechargeControl.setFont(Engine::tm.getFont());
	runControl.setFont(Engine::tm.getFont());
	specialControl1.setFont(Engine::tm.getFont());
	specialControl2.setFont(Engine::tm.getFont());
	specialControl3.setFont(Engine::tm.getFont());
	specialControl4.setFont(Engine::tm.getFont());
	
	//Sets character size for all text in UI
	attackControl.setCharacterSize(30);
	healControl.setCharacterSize(30);
	rechargeControl.setCharacterSize(30);
	runControl.setCharacterSize(30);
	specialControl1.setCharacterSize(30);
	specialControl2.setCharacterSize(30);
	specialControl3.setCharacterSize(30);
	specialControl4.setCharacterSize(30);

	//updates controls with correct keys
	UpdateControls();

	//Sets fonts for all cost text in UI
	attackCost.setFont(Engine::tm.getFont());
	healCost.setFont(Engine::tm.getFont());
	rechargeCost.setFont(Engine::tm.getFont());
	runCost.setFont(Engine::tm.getFont());
	specialCost1.setFont(Engine::tm.getFont());
	specialCost2.setFont(Engine::tm.getFont());
	specialCost3.setFont(Engine::tm.getFont());
	specialCost4.setFont(Engine::tm.getFont());

	//Sets character size for all cost text in UI
	attackCost.setCharacterSize(25);
	healCost.setCharacterSize(25);
	rechargeCost.setCharacterSize(25);
	runCost.setCharacterSize(25);
	specialCost1.setCharacterSize(25);
	specialCost2.setCharacterSize(25);
	specialCost3.setCharacterSize(25);
	specialCost4.setCharacterSize(25);

	//Sets costs to be the same color as action points
	attackCost.setColor(sf::Color(30, 216, 255, 255));
	healCost.setColor(sf::Color(30, 216, 255, 255));
	rechargeCost.setColor(sf::Color(30, 216, 255, 255));
	runCost.setColor(sf::Color(30, 216, 255, 255));
	specialCost1.setColor(sf::Color(30, 216, 255, 255));
	specialCost2.setColor(sf::Color(30, 216, 255, 255));
	specialCost3.setColor(sf::Color(30, 216, 255, 255));
	specialCost4.setColor(sf::Color(30, 216, 255, 255));

	//Updates all the cost text to have correct text and positions
	UpdateCosts();
}

sf::FloatRect& CombatUI::getAttackBox()
{
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

sf::FloatRect& CombatUI::getSp1Box()
{
	return special1Box;
}

sf::FloatRect& CombatUI::getSp2Box()
{
	return special2Box;
}

sf::FloatRect& CombatUI::getSp3Box()
{
	return special3Box;
}

sf::FloatRect& CombatUI::getSp4Box()
{
	return special4Box;
}

//Checks all buttons to see if cursor is contained in them
bool CombatUI::CheckBoxes(sf::Vector2f curspos)
{
	//if any boxes contain mouse, return true.  else false
	if (attackBox.contains(curspos) || healBox.contains(curspos)
		|| rechargeBox.contains(curspos) || runBox.contains(curspos) || special1Box.contains(curspos)
		|| special2Box.contains(curspos) || special3Box.contains(curspos) || special4Box.contains(curspos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Adds new special ability to combatUI
void CombatUI::addSpecial(std::string texName, std::shared_ptr<SpecialAbility> sp)
{
	//Looks for inactive special slot, and if inactive sets up special slot
	if (special1Sprite.getTexture() == NULL)
	{
		//sets correct key for special
		sp->setKey(special1Key);
		sp1 = sp;
		//Assign specials texture, scale, how much they cost, and positions
		special1Sprite.setTexture(Engine::tm.getTex(texName));
		special1Sprite.setScale(0.3f, 0.3f);
		specialCost1.setString(std::to_string(sp1->getAPCost()));
		specialControl1.setString(Engine::keyToString(special1Key));
		specialControl1.setPosition(special1Sprite.getPosition().x + (special1Sprite.getGlobalBounds().width / 2)
			- (specialControl1.getGlobalBounds().width / 2), 1000.0f);
		specialCost1.setPosition(special1Sprite.getPosition().x + special1Sprite.getGlobalBounds().width - costOffset -
		(specialCost1.getGlobalBounds().width), special1Sprite.getPosition().y + costOffset - (specialCost1.getGlobalBounds().height / 2));
		special1Box = special1Sprite.getGlobalBounds();
	}
	else if (special2Sprite.getTexture() == NULL)
	{
		sp->setKey(special2Key);
		sp2 = sp;
		special2Sprite.setTexture(Engine::tm.getTex(texName));
		special2Sprite.setScale(0.3f, 0.3f);
		specialCost2.setString(std::to_string(sp->getAPCost()));
		specialControl2.setString(Engine::keyToString(special2Key));
		specialControl2.setPosition(special2Sprite.getPosition().x + (special2Sprite.getGlobalBounds().width / 2)
			- (specialControl2.getGlobalBounds().width / 2), 1000.0f);
		specialCost2.setPosition(special2Sprite.getPosition().x + special2Sprite.getGlobalBounds().width - costOffset -
			(specialCost2.getGlobalBounds().width), special2Sprite.getPosition().y + costOffset - (specialCost2.getGlobalBounds().height / 2));
		special2Box = special2Sprite.getGlobalBounds();
	}
	else if (special3Sprite.getTexture() == NULL)
	{
		sp->setKey(special3Key);
		sp3 = sp;
		special3Sprite.setTexture(Engine::tm.getTex(texName));
		special3Sprite.setScale(0.3f, 0.3f);
		specialCost3.setString(std::to_string(sp->getAPCost()));
		specialControl3.setString(Engine::keyToString(special3Key));
		specialControl3.setPosition(special3Sprite.getPosition().x + (special3Sprite.getGlobalBounds().width / 2)
			- (specialControl3.getGlobalBounds().width / 2), 1000.0f);
		specialCost3.setPosition(special3Sprite.getPosition().x + special3Sprite.getGlobalBounds().width - costOffset -
			(specialCost3.getGlobalBounds().width), special3Sprite.getPosition().y + costOffset - (specialCost3.getGlobalBounds().height / 2));
		special3Box = special3Sprite.getGlobalBounds();
	}
	else if (special4Sprite.getTexture() == NULL)
	{
		sp->setKey(special4Key);
		sp4 = sp;
		special4Sprite.setTexture(Engine::tm.getTex(texName));
		special4Sprite.setScale(0.3f, 0.3f);
		specialCost4.setString(std::to_string(sp->getAPCost()));
		specialControl4.setString(Engine::keyToString(special4Key));
		specialControl4.setPosition(special4Sprite.getPosition().x + (special4Sprite.getGlobalBounds().width / 2)
			- (specialControl4.getGlobalBounds().width / 2), 1000.0f);
		specialCost4.setPosition(special4Sprite.getPosition().x + special4Sprite.getGlobalBounds().width - costOffset -
			(specialCost4.getGlobalBounds().width), special4Sprite.getPosition().y + costOffset - (specialCost4.getGlobalBounds().height / 2));
		special4Box = special4Sprite.getGlobalBounds();
	}
}

//Resets all specials!
void CombatUI::resetSpecial()
{
	special1Sprite = sf::Sprite();
	special2Sprite = sf::Sprite();
	special3Sprite = sf::Sprite();
	special4Sprite = sf::Sprite();
}

//Updates all controls to be up to date in case player has changed controls
void CombatUI::UpdateControls()
{
	attackControl.setString(Engine::keyToString(attackKey));
	healControl.setString(Engine::keyToString(healKey));
	rechargeControl.setString(Engine::keyToString(rechargeKey));
	runControl.setString(Engine::keyToString(runKey));
	if (special1Sprite.getTexture() != NULL)
	{
		specialControl1.setString(Engine::keyToString(special1Key));
	}
	if (special2Sprite.getTexture() != NULL)
	{
		specialControl2.setString(Engine::keyToString(special2Key));
	}
	if (special3Sprite.getTexture() != NULL)
	{
		specialControl3.setString(Engine::keyToString(special3Key));
	}
	if (special4Sprite.getTexture() != NULL)
	{
		specialControl4.setString(Engine::keyToString(special4Key));
	}

	attackControl.setPosition(attackSprite.getPosition().x + (attackSprite.getGlobalBounds().width / 2)
		- (attackControl.getGlobalBounds().width / 2), 875.0f);
	healControl.setPosition(healSprite.getPosition().x + (healSprite.getGlobalBounds().width / 2)
		- (healControl.getGlobalBounds().width / 2), 875.0f);
	rechargeControl.setPosition(rechargeSprite.getPosition().x + (rechargeSprite.getGlobalBounds().width / 2)
		- (rechargeControl.getGlobalBounds().width / 2), 875.0f);
	runControl.setPosition(runSprite.getPosition().x + (runSprite.getGlobalBounds().width / 2)
		- (runControl.getGlobalBounds().width / 2), 875.0f);
	specialControl1.setPosition(special1Sprite.getPosition().x + (special1Sprite.getGlobalBounds().width / 2)
		- (specialControl1.getGlobalBounds().width / 2), 975.0f);
	specialControl2.setPosition(special2Sprite.getPosition().x + (special2Sprite.getGlobalBounds().width / 2)
		- (specialControl2.getGlobalBounds().width / 2), 975.0f);
	specialControl3.setPosition(special3Sprite.getPosition().x + (special3Sprite.getGlobalBounds().width / 2)
		- (specialControl3.getGlobalBounds().width / 2), 975.0f);
	specialControl4.setPosition(special4Sprite.getPosition().x + (special4Sprite.getGlobalBounds().width / 2)
		- (specialControl3.getGlobalBounds().width / 2), 975.0f);
}

//Updates all costs in UI in case of updated cost
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

void GameUI::Update(double dt, sf::Vector2f cursPos)
{
	//If Back To Menu button contains Cursor and player is dead
	if (backToMenuBox.contains(cursPos) && player->getCurrentHealth() == 0)
	{
		//Set text green
		backToMenu.setColor(Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // if mouse is pressed
		{
			//Change to menu
			gameScene.gameMusic.stop();
			Engine::ChangeScene(&menuScene);
		}
	}
	else
	{
		GameOverButton.setColor(White);
	}
}

//When enemy is killed this is looped
bool GameUI::updateStatOptions()
{
	//Sets stat up text
	statUp();
	//Gets curser position
	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);

	//Updates cursor position to reflect window size
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	//If in stat up
	if (inStatUp)
	{
		//If mouse button is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//if stat boxes contain mouse
			if (stat1Box.contains(cursPos))
			{
				//Add specific stat to player
				player->addStats(strengthUp, 0, 0);
				//play sound
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50 * soundVolume / 100 * masterVolume / 100);
				sound.play();
				//set values to false to break out of function
				inStatUp = false;
				return false;
			}
			if (stat2Box.contains(cursPos))
			{
				player->addStats(0, hpUp, 0);
				sound.setBuffer(Engine::tm.getSound("StatUp"));
				sound.setVolume(50 * soundVolume / 100 * masterVolume / 100);
				sound.play();
				inStatUp = false;
				return false;
			}
			if (stat3Box.contains(cursPos))
			{
				player->addStats(0, 0, dexUp);
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
	//Render background of game
	Renderer::queue(&background);

	//Render all action points
	for (auto& e : cells)
	{
		Renderer::queue(&e);
	}

	//Render player icon
	Renderer::queue(&playerIcon);
	//if in stat up after killing enemy
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

	//if player is dead, render game over stuff
	if (player->getCurrentHealth() == 0)
	{
		Renderer::queue(&GameOverButton);
		Renderer::queue(&backToMenu);
	}
}

//Load important stuff for the GameUI
void GameUI::Load(int maxAP, std::shared_ptr<BasePlayerComponent> p)
{
	//Set default values
	player = p;
	inStatUp = false;
	MaxAP = maxAP;
	APAmount = 0;
	cells.clear();
	height = 0;

	//Gain full AP
	gainAP(MaxAP);

	//Sets values for text and sprites, textures, fonts, strings etc
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

	stat1Box = stat1.getGlobalBounds();
	stat2Box = stat2.getGlobalBounds();
	stat3Box = stat3.getGlobalBounds();

	//Sets values for statup after enemies are killed
	strengthUp = 5;
	hpUp = 10;
	dexUp = 5;

	//More initializing text and sprites
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
	RewardsText.setPosition((Engine::getWindowSize().x / 2) - (RewardsText.getLocalBounds().width / 2), 250.0f);
	StrengthText.setPosition(stat1.getPosition().x - (StrengthText.getGlobalBounds().width / 2), 400.0f);
	HealthText.setPosition(stat2.getPosition().x - (HealthText.getLocalBounds().width / 2), 400.0f);
	DexterityText.setPosition(stat3.getPosition().x - (DexterityText.getLocalBounds().width / 2), 400.0f);
	HealthText.setFillColor(sf::Color(220, 20, 60, 255));
	StrengthText.setFillColor(sf::Color(0, 0, 205, 255));
	DexterityText.setFillColor(sf::Color(0, 255, 127, 255));

	//Sets the background!
	background.setTexture(Engine::tm.getTex("Background1"));
	//Move the background up so combat UI has space to be seen
	background.setScale(GAMEX / background.getGlobalBounds().width, 0.7f);

	//Game Over text and back to menu 
	GameOverButton.setFont(font);
	GameOverButton.setString("GAME OVER");
	GameOverButton.setCharacterSize(60);
	GameOverButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (GameOverButton.getGlobalBounds().width / 2),
		GAMEY / 2.0f - (GameOverButton.getGlobalBounds().height / 2) + 100.0f));
	GameOverButtonBox = GameOverButton.getGlobalBounds();
	backToMenu.setFont(font);
	backToMenu.setString("Back To Menu");
	backToMenu.setCharacterSize(60);
	backToMenu.setPosition(sf::Vector2f(GAMEX / 2.0f - (backToMenu.getGlobalBounds().width / 2),
		300.0f));
	backToMenuBox = backToMenu.getGlobalBounds();

}

//Creates new action point cell
sf::Sprite GameUI::getNewCell()
{
	sf::Sprite cell;
	cell.setTexture(Engine::tm.getTex("Charge"));
	cell.setScale(0.10f, 0.2f);
	//Adds to height so future cells are placed correctly
	height += 20;
	cell.setPosition(sf::Vector2f(870.0f + height, 700.0f));
	//rotates as tex is 90 degrees off
	cell.setRotation(90);
	return cell;
}

//Sets values for stat up
void GameUI::statUp()
{
	inStatUp = true;
	HealthText.setString("Max Health\n    + " + std::to_string(hpUp));
	StrengthText.setString("Strength\n    + " + std::to_string(strengthUp));
	DexterityText.setString("Dexterity\n  + " + std::to_string(dexUp));
}

//Spend AP and update on action points 
void GameUI::useAP(int amount)
{
	//get temp value of current AP minus amount, and sets to 0 if less than 0
	int temp = APAmount - amount;
	if (temp < 0)
	{
		APAmount = 0;
	}
	else
	{
		APAmount = temp;
	}
	//If currentAmount is not 0
	if (APAmount != 0)
	{
		//deletes cell for each that has been spent
		for (int i = 0; i < amount; i++)
		{
			cells.pop_back();
			height -= 20;
		}
	}
	else
	{
		//if apamount is 0, clears cells
		while (!cells.empty())
		{
			cells.pop_back();
			height -= 20;
		}
	}
}

//Gain AP on UI
void GameUI::gainAP(int amount)
{
	//Gets temp value to ensure you dont add above limit
	int temp = APAmount + amount;
	if (temp > MaxAP)
	{
		//Creates only enough cells to fill AP bar
		for (int i = 0; i < MaxAP - APAmount; i++)
		{
			cells.push_back(getNewCell());
		}
		APAmount = MaxAP;
	}
	else
	{
		//Creates new cells for amount gained
		APAmount = temp;
		for (int i = 0; i < amount; i++)
		{
			cells.push_back(getNewCell());
		}
	}
}

//returns current AP amount of gameUI
int GameUI::getAPAmount()
{
	return cells.size();
}

//Updates the text of the tooltip description text that many other functions call to show what abilities do etc
void GameUI::UpdateDesc(std::string string)
{
	descText.setString(string);
}

//Updates the position of the tooltip description text that many other functions call to show what abilities do etc
void GameUI::UpdateDescPos(sf::Vector2f pos)
{
	descText.setPosition(pos);
}

//Plays sound from UI
void GameUI::playSound(const std::string& name, int volume)
{
	sound.setBuffer(Engine::tm.getSound(name));
	sound.setVolume(volume * soundVolume/100 * masterVolume/100);
	sound.play();
}

//Big Update in settings to check if any buttons are pressed
void SettingUI::Update(const double& dt, sf::Vector2f cursPos)
{
	//get current time for delays
	delayTime = delayClock.getElapsedTime().asSeconds();

	//If Res box contains cursor
	if (ResButtonBox.contains(cursPos))
	{
		ResButton.setColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left) && delayTime >= delayAmount) // if mouse is pressed
		{
			//play UI sound
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.play();
			delayClock.restart();
			//Changes resolution to next on list, 720p, 1080p, fullscreen
			if (Engine::getWindowSize().y == 1080) // if window is 1080p
			{
				//if window isnt fullscreen, go fullscreen
				if (!Engine::getFullscreen())
				{
					ResChange.setString("FS");
					Engine::SetFullScreen(Engine::GetWindow(), true);
				}
				else // go 720p
				{
					ResChange.setString("720p");
					Engine::SetFullScreen(Engine::GetWindow(), false);
					Engine::ChangeResolution(1280, 720, GAMEX, GAMEY);
				}
			}
			else // go 1080p from 720p
			{ 
				ResChange.setString("1080p");
				Engine::ChangeResolution(1920, 1080, GAMEX, GAMEY);
			}
		}
	}
	else
	{
		ResButton.setColor(White);
	}

	//Checks if master volume left box is clicked, and reduces master volume if so
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
	//Checks if master volume right box is clicked, and Increases master volume if so
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
	//Checks if music volume left box is clicked, and reduces music volume if so
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
	//Checks if music volume right box is clicked, and increases music volume if so
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
	//Checks if soundFX volume left box is clicked, and reduces FX volume if so
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
	//Checks if FX volume right box is clicked, and increases FX volume if so
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

	//Checks if right key on keyboard is pressed, and changes screen resolution like before if so
	if (Keyboard::isKeyPressed(Keyboard::Right) && delayTime >= delayAmount)
	{
		sound.setVolume(soundVolume* masterVolume / 100);
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
			ResChange.setString("1080p");
			Engine::ChangeResolution(1920, 1080, GAMEX, GAMEY);
		}
	}

	//If back to menu box is clicked, change scene to main menu
	if (toMenuBox.contains(cursPos))
	{
		toMenuText.setColor(Green);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			sound.setVolume(soundVolume* masterVolume / 100);
			sound.play();
			menuScene.setSettings(false);
			gameScene.gameMusic.stop();
			Engine::ChangeScene(&menuScene);
			menuScene.setSettings(false);
			gameScene.setPause(false);
		}
	}
	else
	{
		toMenuText.setColor(White);
	}

	//Checks each Key in the change controls section, and if any include mouse and have a key pressed on them change that key 
	//to pressed key
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
	
	//If reset controls clicked, reset controls to default values
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

	//If back button clicked return to previous screen (main menu, game scene)
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

	//If backspace is called go back to previous scene
	if (Keyboard::isKeyPressed(Keyboard::BackSpace))
	{
		sound.setVolume(soundVolume* masterVolume / 100);
		sound.play();
		menuScene.setSettings(false);
		gameScene.setPause(false);
	}

}

//Loads stuff for setting UI
void SettingUI::Load(sf::Font &font, bool p)
{
	pause = p;

	//Loads sound for menu button presses
	sound.setBuffer(Engine::tm.getSound("ButtonPress"));

	//Sets font for all text
	ResChange.setFont(font);
	ResText.setFont(font);
	ResButton.setFont(font);
	MasterText.setFont(font);
	MusicText.setFont(font);
	FXText.setFont(font);
	MasterLeft.setFont(font);
	MasterRight.setFont(font);
	MusicLeft.setFont(font);
	MusicRight.setFont(font);
	FXLeft.setFont(font);
	FXRight.setFont(font);
	BackButton.setFont(font);
	AttackText.setFont(font);
	HealText.setFont(font);
	RechargeText.setFont(font);
	RunText.setFont(font);
	Special1Text.setFont(font);
	Special2Text.setFont(font);
	Special3Text.setFont(font);
	Special4Text.setFont(font);
	PauseText.setFont(font);
	AttackKeyText.setFont(font);
	HealKeyText.setFont(font);
	RechargeKeyText.setFont(font);
	RunKeyText.setFont(font);
	Special1KeyText.setFont(font);
	Special2KeyText.setFont(font);
	Special3KeyText.setFont(font);
	Special4KeyText.setFont(font);
	PauseKeyText.setFont(font);
	ResetControls.setFont(font);
	HowToText.setFont(font);

	//Sets string and position etc for all text
	BackButton.setString("BACK - BACKSPACE");
	BackButton.setCharacterSize(40);
	BackButton.setPosition(sf::Vector2f(1300.0f, 975.0f));
	BackBox = BackButton.getGlobalBounds();

	ResChange.setString("1080p"); //Starts at 720p
	ResChange.setCharacterSize(60);
	ResChange.setPosition(sf::Vector2f(GAMEX / 2.0f + 100.0f, 50.0f));
	ResText.setString("Resolution: ");
	ResText.setCharacterSize(60);
	ResText.setPosition(sf::Vector2f(GAMEX / 2.0f - 500.0f, 50.0f));
	ResButton.setString(" > ");
	ResButton.setCharacterSize(100);
	ResButton.setPosition(sf::Vector2f(GAMEX / 2.0f + 380.0f, 20.0f));
	ResButtonBox = ResButton.getGlobalBounds();

	MasterText.setString("Master Volume: " + std::to_string(masterVolume));
	MasterText.setCharacterSize(40);
	MasterText.setPosition(sf::Vector2f(GAMEX / 2 - 350.0f, 150.0f));
	MusicText.setString("Music Volume: " + std::to_string(musicVolume));
	MusicText.setCharacterSize(40);
	MusicText.setPosition(sf::Vector2f(GAMEX / 2 - 350.0f, 200.0f));
	FXText.setString("FX Volume: " + std::to_string(soundVolume));
	FXText.setCharacterSize(40);
	FXText.setPosition(sf::Vector2f(GAMEX / 2 - 300.0f, 250.0f));

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

	AttackText.setString("Attack Key: ");
	AttackText.setCharacterSize(40);
	AttackText.setPosition(sf::Vector2f((GAMEX / 2)
		- AttackText.getGlobalBounds().width, 300.0f));
	HealText.setString("Heal Key  ");
	HealText.setCharacterSize(40);
	HealText.setPosition(sf::Vector2f((GAMEX / 2)
		- HealText.getGlobalBounds().width, 350.0f));
	RechargeText.setString("Recharge Key: ");
	RechargeText.setCharacterSize(40);
	RechargeText.setPosition(sf::Vector2f((GAMEX / 2)
		- RechargeText.getGlobalBounds().width, 400.0f));
	RunText.setString("Run Key: ");
	RunText.setCharacterSize(40);
	RunText.setPosition(sf::Vector2f((GAMEX / 2)
		- RunText.getGlobalBounds().width, 450.0f));
	Special1Text.setString("Special 1 Key: ");
	Special1Text.setCharacterSize(40);
	Special1Text.setPosition(sf::Vector2f((GAMEX / 2)
		- Special1Text.getGlobalBounds().width, 500.0f));
	Special2Text.setString("Special 2 Key: ");
	Special2Text.setCharacterSize(40);
	Special2Text.setPosition(sf::Vector2f((GAMEX / 2)
		- Special2Text.getGlobalBounds().width, 550.0f));
	Special3Text.setString("Special 3 Key: ");
	Special3Text.setCharacterSize(40);
	Special3Text.setPosition(sf::Vector2f((GAMEX / 2)
		- Special3Text.getGlobalBounds().width, 600.0f));
	Special4Text.setString("Special 4 Key: ");
	Special4Text.setCharacterSize(40);
	Special4Text.setPosition(sf::Vector2f((GAMEX / 2)
		- Special4Text.getGlobalBounds().width, 650.0f));
	PauseText.setString("Pause Key: ");
	PauseText.setCharacterSize(40);
	PauseText.setPosition(sf::Vector2f((GAMEX / 2)
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
	ResetControls.setPosition((GAMEX / 2) - (ResetControls.getGlobalBounds().width / 2), 800.0f);
	ResetBox = ResetControls.getGlobalBounds();

	//Updates how to text to explain how to change controls
	HowToText.setString("To change controls hover\nmouse over key and hold down\n new key on keyboard");
	HowToText.setCharacterSize(25);
	HowToText.setPosition(1200.0f, 400.0f);

	//If this is pause screen not settings, allows you to return to main menu from game scene
	if (pause)
	{
		toMenuText.setFont(Engine::tm.getFont());
		toMenuText.setString("To Main Menu\n(Remember to save!)");
		toMenuText.setCharacterSize(30);
		toMenuText.setPosition(50.0f, 50.0f);
		toMenuBox = toMenuText.getGlobalBounds();
	}
}

void SettingUI::Render()
{
	//Renders all buttons
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
	if (pause) // if pause not settings
	{
		Renderer::queue(&toMenuText);
	}
}

//Resets all controls back to default
void SettingUI::ResetKeys()
{
	AttackKeyText.setString("1");
	attackKey = Keyboard::Num1;
	HealKeyText.setString("2");
	healKey = Keyboard::Num2;
	RechargeKeyText.setString("3");
	rechargeKey = Keyboard::Num3;
	RunKeyText.setString("4");
	runKey = Keyboard::Num4;
	Special1KeyText.setString("Q");
	special1Key = Keyboard::Num1;
	Special2KeyText.setString("W");
	special2Key = Keyboard::Num2;
	Special3KeyText.setString("E");
	special3Key = Keyboard::Num3;
	Special4KeyText.setString("R");
	special4Key = Keyboard::Num4;
	PauseKeyText.setString("Tab");
	pauseKey = Keyboard::Tab;

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

//Checks if key is pressed and if so assigns that key to the key passed through
//A bit buggy, event handler is very slow and sometimes doesn't work
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

//Updates Settings if things have been changed
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