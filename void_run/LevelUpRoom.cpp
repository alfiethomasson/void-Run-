#include "LevelUpRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"
#include "VoidRun.h"

bool choicePicked;

LevelUpRoom::LevelUpRoom(std::shared_ptr <Entity> p)
	: delayAmount(2.0f), Room(p) {};

void LevelUpRoom::Load() {

	if (!statUPTex.loadFromFile("res/Icons/Arrow.png"))
	{
		std::cout << "Couldnt load up arrow in levelling up room\n";
	}

	Room::Load();

	//auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	//p = a[0];

	choicePicked = false;

	statIncrease1.setTexture(statUPTex);
	statIncrease2.setTexture(statUPTex);
	statIncrease3.setTexture(statUPTex);
	statIncrease1.setScale(0.3f, 0.3f);
	statIncrease2.setScale(0.3f, 0.3f);
	statIncrease3.setScale(0.3f, 0.3f);
	statIncrease1.setRotation(90);
	statIncrease2.setRotation(90);
	statIncrease3.setRotation(90);
	statIncrease1.setPosition(500.0f, 250.0f);
	statIncrease2.setPosition(700.0f, 250.0f);
	statIncrease3.setPosition(900.0f, 250.0f);

	ability1Text.setFont(Engine::tm.getFont());
	ability2Text.setFont(Engine::tm.getFont());
	ability1Text.setCharacterSize(35);
	ability2Text.setCharacterSize(35);

	if (p->level == 2)
	{
		auto lb = std::make_shared<LaserBurst>();
		lb->load();
		sp1 = lb;

		auto df = std::make_shared<DeadlyFumes>();
		df->load();
		sp2 = df;
	}
	else if (p->level == 3)
	{
		auto pi = std::make_shared<HoloGamble>();
		pi->load();
		sp1 = pi;

		auto ow = std::make_shared<OverloadWeapon>();
		ow->load();
		sp2 = ow;
	}
	else if (p->level == 4)
	{
		auto mg = std::make_shared<PrimalInstincts>();
		mg->load();
		sp1 = mg;

		auto us = std::make_shared<UncannySpeed>();
		us->load();
		sp2 = us;
	}
	else if (p->level == 5)
	{
		auto mg = std::make_shared<NanoBots>();
		mg->load();
		sp1 = mg;

		auto us = std::make_shared<MagmaGrenade>();
		us->load();
		sp2 = us;
	}

	ability1.setTexture(Engine::tm.getTex(sp1->getTexName()));
	ability1Text.setString(sp1->getName());
	sp1->updatePlayer(p);

	ability2.setTexture(Engine::tm.getTex(sp2->getTexName()));
	ability2Text.setString(sp2->getName());
	sp2->updatePlayer(p);

	ability1.setScale(0.5f, 0.5f);
	ability2.setScale(0.5f, 0.5f);
	ability1.setPosition(GAMEX / 2 - 300.0f, 500.0f);
	ability2.setPosition(GAMEX / 2 + 300.0f, 500.0f);
	ability1Text.setPosition(ability1.getPosition().x + (ability1.getGlobalBounds().width / 2) - 
		ability1Text.getGlobalBounds().width / 2, 400.0f);
	ability2Text.setPosition(ability2.getPosition().x + (ability2.getGlobalBounds().width / 2) -
		ability2Text.getGlobalBounds().width / 2, 400.0f);

	statIncrease1Box = statIncrease1.getGlobalBounds();
	statIncrease2Box = statIncrease2.getGlobalBounds();
	statIncrease3Box = statIncrease3.getGlobalBounds();
	ability1Box = ability1.getGlobalBounds();
	ability2Box = ability2.getGlobalBounds();
}	

void LevelUpRoom::Update(const double& dt, sf::Vector2f cursPos) {
	delayTime = delayClock.getElapsedTime().asSeconds();

	if (choicePicked && delayTime >= delayAmount)
	{
		setInactive();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !choicePicked)
	{
		if (ability1Box.contains(cursPos))
		{
			sound.setBuffer(Engine::tm.getSound("PowerUp"));
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.play();
			p->addAbility(sp1);
			choicePicked = true;
		}
		if (ability2Box.contains(cursPos))
		{
			sound.setBuffer(Engine::tm.getSound("PowerUp"));
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.play();
			delayClock.restart();
			p->addAbility(sp2);
			choicePicked = true;
		}
		//if (statIncrease1Box.contains(cursPos))
		//{
		//	p->addStats(5, 0, 0);
		//	choicePicked = true;
		//}
		//if (statIncrease2Box.contains(cursPos))
		//{
		//	p->addStats(0, 10, 0);
		//	choicePicked = true;
		//}
		//if (statIncrease3Box.contains(cursPos))
		//{
		//	p->addStats(0, 0, 5);
		//	choicePicked = true;
		//}
	}
}

void LevelUpRoom::Render() {

	if (!choicePicked) {
		Renderer::queue(&ability1);
		Renderer::queue(&ability2);
		//Renderer::queue(&statIncrease1);
		//Renderer::queue(&statIncrease2);
		//Renderer::queue(&statIncrease3);
		Renderer::queue(&ability1Text);
		Renderer::queue(&ability2Text);
		//Renderer::queue(&statIncrease1Text);
		//Renderer::queue(&statIncrease2Text);
		//Renderer::queue(&statIncrease3Text);
	}
}