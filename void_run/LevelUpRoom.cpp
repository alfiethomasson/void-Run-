#include "LevelUpRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_player.h"
#include "cmp_sprite.h"
#include "VoidRun.h"

bool choicePicked;

LevelUpRoom::LevelUpRoom(std::shared_ptr <Entity> p) //Create level up room
	: delayAmount(2.0f), Room(p) {};

void LevelUpRoom::Load() { //Load files

	Room::Load();

	choicePicked = false; //Set choice picked to false - This is used to disable options once they have made a decision so that they cannot pick multiple

	ability1Text.setFont(Engine::tm.getFont()); //Ability 1 set up
	ability2Text.setFont(Engine::tm.getFont()); //And ability 2, too
	ability1Text.setCharacterSize(35);
	ability2Text.setCharacterSize(35);

	if (p->level == 2) //If they're level 2, they have two options:
	{
		auto lb = std::make_shared<LaserBurst>(); //A high powered laser blast!
		lb->load();
		sp1 = lb;

		auto df = std::make_shared<DeadlyFumes>(); //Or toxic, deadly fumes!
		df->load();
		sp2 = df;
	}
	else if (p->level == 3) //At level 3, different options:
	{
		auto pi = std::make_shared<HoloGamble>(); //A random deck of cards to shuffle their stats...
		pi->load();
		sp1 = pi;

		auto ow = std::make_shared<OverloadWeapon>(); //Or the ability to overload their weapon!
		ow->load();
		sp2 = ow;
	}
	else if (p->level == 4) //At level 4, more options:
	{
		auto mg = std::make_shared<PrimalInstincts>(); //A savage rage of primal instincts for one room..
		mg->load();
		sp1 = mg;

		auto us = std::make_shared<UncannySpeed>(); //Or a massive speed boost!
		us->load();
		sp2 = us;
	}
	else if (p->level == 5) //Lastly, at 5th level:
	{
		auto mg = std::make_shared<NanoBots>(); //Regenerative nanobots..
		mg->load();
		sp1 = mg;

		auto us = std::make_shared<MagmaGrenade>(); //Or an explosive magma grenade!
		us->load();
		sp2 = us;
	}

	ability1.setTexture(Engine::tm.getTex(sp1->getTexName())); //Set up textures for ability 1
	ability1Text.setString(sp1->getName());
	sp1->updatePlayer(p);

	ability2.setTexture(Engine::tm.getTex(sp2->getTexName())); //Set up textures for ability 2
	ability2Text.setString(sp2->getName());
	sp2->updatePlayer(p);

	ability1.setScale(0.5f, 0.5f); //Set up of scale, positions, etc for text.
	ability2.setScale(0.5f, 0.5f);
	ability1.setPosition(GAMEX / 2 - 300.0f, 500.0f);
	ability2.setPosition(GAMEX / 2 + 300.0f, 500.0f);
	ability1Text.setPosition(ability1.getPosition().x + (ability1.getGlobalBounds().width / 2) - 
	ability1Text.getGlobalBounds().width / 2, 400.0f);
	ability2Text.setPosition(ability2.getPosition().x + (ability2.getGlobalBounds().width / 2) -
	ability2Text.getGlobalBounds().width / 2, 400.0f);


	ability1Box = ability1.getGlobalBounds(); //Create buttons over the text to click on
	ability2Box = ability2.getGlobalBounds();
}	

void LevelUpRoom::Update(const double& dt, sf::Vector2f cursPos) { //Update loop, gets cursor position
	delayTime = delayClock.getElapsedTime().asSeconds();

	if (choicePicked && delayTime >= delayAmount) //Cannot select within the first second of entering the room to prevent accidental misclick
	{
		setInactive();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !choicePicked) //If the player has clicked, and not picked a choice..
	{
		if (ability1Box.contains(cursPos)) //If they're on option 1, they pick that!
		{
			sound.setBuffer(Engine::tm.getSound("PowerUp")); //They get ability 1!
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.play();
			p->addAbility(sp1); //Add it to their abilities
			choicePicked = true; //Choice picked true so that they can't pick both.
		}
		if (ability2Box.contains(cursPos)) //If they're on option 2, they pick that!
		{
			sound.setBuffer(Engine::tm.getSound("PowerUp"));
			sound.setVolume(soundVolume * masterVolume / 100);
			sound.play();
			delayClock.restart();
			p->addAbility(sp2); //Add it to their abilities
			choicePicked = true; //Choice picked true so that they can't pick both.
		}
	}
}

void LevelUpRoom::Render() {

	if (!choicePicked) {
		Renderer::queue(&ability1);
		Renderer::queue(&ability2);
		Renderer::queue(&ability1Text);
		Renderer::queue(&ability2Text);
	}
}