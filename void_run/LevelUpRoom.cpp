#include "LevelUpRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"
#include "VoidRun.h"

bool choicePicked;

LevelUpRoom::LevelUpRoom(std::shared_ptr <Entity> p)
	: Room(p) {};

void LevelUpRoom::Load() {

	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];

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

	statIncrease1Box = statIncrease1.getGlobalBounds();
	statIncrease2Box = statIncrease2.getGlobalBounds();
	statIncrease3Box = statIncrease3.getGlobalBounds();
}	

void LevelUpRoom::Update(const double& dt) {

	if (!statUPTex.loadFromFile("res/Icons/Arrow.png"))
	{
		std::cout << "Couldnt load up arrow in levelling up room\n";
	}

	sf::Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f cursPos = sf::Vector2f(tempPos);

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (statIncrease1Box.contains(cursPos))
		{
			p->addStats(5, 0, 0);
			choicePicked = true;
		}
		if (statIncrease2Box.contains(cursPos))
		{
			p->addStats(0, 10, 0);
			choicePicked = true;
		}
		if (statIncrease3Box.contains(cursPos))
		{
			p->addStats(0, 0, 5);
			choicePicked = true;
		}
	}*/
}

void LevelUpRoom::Render() {
	//Renderer::queue(&ability1);
	//Renderer::queue(&ability2);
	Renderer::queue(&statIncrease1);
	Renderer::queue(&statIncrease2);
	Renderer::queue(&statIncrease3);
	//Renderer::queue(&ability1Text);
	//Renderer::queue(&ability2Text);
	Renderer::queue(&statIncrease1Text);
	Renderer::queue(&statIncrease2Text);
	Renderer::queue(&statIncrease3Text);
}