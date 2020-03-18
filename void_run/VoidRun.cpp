#include <iostream>
#include "VoidRun.h"
#include "ecm.h"
#include "Game.h"	
#include "System_Renderer.h"
#include "LevelSystem.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

std::shared_ptr<BasePlayerComponent> player;

//#define GHOSTS_COUNT 4

void MenuScene::Update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		activeScene = gameScene;
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		Renderer::getWindow().close();
	}
	Scene::Update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Vector2i tempPos = sf::Mouse::getPosition(Renderer::getWindow());
		Vector2f cursPos = sf::Vector2f(tempPos);
		//std::cout << cursPos.x << " , " << cursPos.y << "\n";
		if (PlayButtonBox.contains(cursPos))
		{
			std::cout << "Should change to game\n";
			activeScene = gameScene;
		}
		if (ExitButtonBox.contains(cursPos))
		{
			std::cout << "Should change to exit\n";
			Renderer::getWindow().close();
		}

	}

}

void MenuScene::Render() {
	Renderer::queue(&GameName);
	Renderer::queue(&PlayButton);
	Renderer::queue(&ExitButton);
	Scene::Render();
}

void MenuScene::Load() {
	//Set up the text element here!

if (!font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/GamesEngAlfie/res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}
	GameName.setFont(font);
	PlayButton.setFont(font);
	ExitButton.setFont(font);

	GameName.setString("Void Run()");
	GameName.setCharacterSize(100);
	GameName.setPosition(sf::Vector2f(gameWidth / 3.5f, gameHeight / 5.0f));
	PlayButton.setString("PLAY - 1");
	PlayButton.setCharacterSize(60);
	PlayButton.setPosition(sf::Vector2f(gameWidth / 2.35f, gameHeight / 2.25f));
	PlayButtonBox = PlayButton.getGlobalBounds();
	ExitButton.setString("EXIT - 2");
	ExitButton.setCharacterSize(60);
	ExitButton.setPosition(sf::Vector2f(gameWidth / 2.35f, gameHeight / 1.65f));
	ExitButtonBox = ExitButton.getGlobalBounds();
}

void GameScene::Load() {
	auto pl = make_shared<Entity>(); 
	auto s = pl->addComponent<ShapeComponent>();
	//pl->addComponent<PlayerMovementComponent>();
	auto i = pl->addComponent<EntityInfo>();
	player = pl->addComponent<BasePlayerComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(-200.0f, -200.0f));
	i->setStrength(10);
	i->setHealth(50);
	i->setDexterity(10);

	_ents.list.push_back(pl);

	auto enemy1 = make_shared<Entity>();
	s = enemy1->addComponent<ShapeComponent>();
	i = enemy1->addComponent<EntityInfo>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(Vector2f(-500.0f, -200.0f));
	i->setStrength(10);
	i->setHealth(50);
	i->setDexterity(10);

	_ents.list.push_back(enemy1);

	ChangeRoom();
}

void GameScene::Update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	//_ents.Update(dt);
	Scene::Update(dt);
	//...
}

void GameScene::Render() {
	//ls::Render(Renderer::getWindow());

	//Renderer::queue(&text);
	Scene::Render();
}

void GameScene::ChangeRoom() {
	player->updateEnemy(_ents.list[_ents.list.size() - 1]);
}