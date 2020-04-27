#include "TreasureRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"

TreasureRoom::TreasureRoom(std::shared_ptr <Entity> p, ItemDB &iDB)
	: itemDB{ iDB }, chestOpened{ false }, delayAmount{ 2.0f }, Room(p) {}

void TreasureRoom::Update(const double& dt, sf::Vector2f cursPos) {

	delayTime = delayClock.getElapsedTime().asSeconds();

	if (chestOpened && delayTime >= delayAmount)
	{
		setInactive();
	}

	if (iconBox.contains(cursPos))
	{
		gameScene.UpdateDesctext("OPEN CHEST\nWhat will you get?", sf::Vector2f(iconBox.getPosition().x,
			iconBox.getPosition().y - 75.0f));
		if (Mouse::isButtonPressed(Mouse::Left) && !chestOpened)
		{
			OpenChest();
		}
	}
	else
	{
		gameScene.ResetDescText();
	}
	if (Keyboard::isKeyPressed(attackKey) && !chestOpened)
	{
		OpenChest();
	}
}

void TreasureRoom::OpenChest()
{
	sound.setBuffer(Engine::tm.getSound("ChestOpening"));
	sound.setVolume(soundVolume * masterVolume / 100);
	sound.play();

	chestSprite.setTexture(Engine::tm.getTex("ChestOpen"));

	srand(time(0));

	int randNum = rand() % 5;
	if (randNum < 2)
	{
		inv->add(itemDB.randomCommonItem(), true);
	}
	else if (randNum == 2 || randNum == 3)
	{
		inv->add(itemDB.randomRareItem(), true);
	}
	else
	{
		inv->add(itemDB.randomSpecialItem(), true);
	}
	chestOpened = true;
	delayClock.restart();
}

void TreasureRoom::Render() {
	Renderer::queue(&chestSprite);
	Renderer::queue(&iconSprite);
	Renderer::queue(&PressText);
}

void TreasureRoom::Load() {
	std::cout << "Entered a Treasure Room!\n";
	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];

	auto i = player->GetCompatibleComponent<Inventory>();
	inv = i[0];
	p->isTurn = false;

	chestSprite.setTexture(Engine::tm.getTex("ChestClosed"));
	chestSprite.setPosition(1500.0f, 500.0f);
	chestSprite.setScale(-0.3, 0.3f);

	iconSprite.setTexture(Engine::tm.getTex("QuestionMark"));
	iconSprite.setScale(0.6f, 0.6f);
	iconSprite.setPosition(GAMEX / 2 - iconSprite.getGlobalBounds().width / 2, 800.0f);
	iconBox = iconSprite.getGlobalBounds();

	PressText.setFont(Engine::tm.getFont());
	PressText.setCharacterSize(30);
	PressText.setString(Engine::keyToString(attackKey));
	PressText.setPosition(iconSprite.getPosition().x + (iconSprite.getGlobalBounds().width / 2)
		- (PressText.getGlobalBounds().width / 2), 950.0f);
}
