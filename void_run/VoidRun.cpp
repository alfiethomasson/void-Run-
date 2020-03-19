#include "VoidRun.h"
#include "Game.h"
#include <iostream>
#include "System_Renderer.h"
#include "System_resources.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "engine.h"

using namespace sf;
using namespace std;

//std::shared_ptr<Scene> gameScene;
//std::shared_ptr<Scene> menuScene;
//std::shared_ptr<Scene> activeScene;

std::shared_ptr<BasePlayerComponent> player;

sf::Event event;

sf::Color green(0, 255, 0, 255);
sf::Color white(255, 255, 255, 255);


void MenuScene::Update(const double& dt) {
	
	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);

	//while events are available to poll
	while (Engine::GetWindow().pollEvent(event))
	{
		//If we want to close game
		if(event.type == sf::Event::Closed)
		{
			Engine::GetWindow().close();
		}
		//If we want to go to game from menu
		if (sf::Keyboard::isKeyPressed(Keyboard::Num1))
		{
			//activeScene = gameScene;
		}
		//If we want to close game
		if (Keyboard::isKeyPressed(Keyboard::Num2)) {
			Engine::GetWindow().close();
		}
		//If we click button
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (PlayButtonBox.contains(cursPos))
			{
				std::cout << "Should change to game\n";
				Engine::ChangeScene(&gameScene);
			//	activeScene = gameScene;
			}
			if (ExitButtonBox.contains(cursPos))
			{
				std::cout << "Should change to exit\n";
				Engine::GetWindow().close();
			}
		}
	}

	//Checks if button box's contain mouse, and makes text green if so
	if (PlayButtonBox.contains(cursPos))
	{
		PlayButton.setFillColor(green);
	}
	else
	{
		PlayButton.setFillColor(white);
	}

	if (ExitButtonBox.contains(cursPos))
	{
		ExitButton.setFillColor(green);
	}
	else
	{
		ExitButton.setFillColor(white);
	}

	Scene::Update(dt);
	
}

//Renders Text
void MenuScene::Render() {
	//Queues text to render in system renderer
	Renderer::queue(&GameName);
	Renderer::queue(&PlayButton);
	Renderer::queue(&ExitButton);
	Scene::Render();
}

void MenuScene::Load() {
	//Loads font
if (!font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/GamesEngAlfie/res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}
	//const string& fontName = "Mandalore";
	//Resources::load(fontName);

	//Assigns Font to Text
	GameName.setFont(font);
	PlayButton.setFont(font);
	ExitButton.setFont(font);

	//Sets values for text
	GameName.setString("Void Run()");
	GameName.setCharacterSize(100);
	GameName.setPosition(sf::Vector2f(gameWidth / 3.5f, gameHeight / 5.0f));
	PlayButton.setString("PLAY - 1");
	PlayButton.setCharacterSize(60);
	PlayButton.setPosition(sf::Vector2f(gameWidth / 2.35f, gameHeight / 2.25f));
	PlayButtonBox = PlayButton.getGlobalBounds(); //Creates the button boundaries
	ExitButton.setString("EXIT - 2");
	ExitButton.setCharacterSize(60);
	ExitButton.setPosition(sf::Vector2f(gameWidth / 2.35f, gameHeight / 1.65f));
	ExitButtonBox = ExitButton.getGlobalBounds(); //Button Boundaries
}

void GameScene::Load() {
	//Creates Player and adds components
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

	ents.list.push_back(pl);

	//Creates Enemy and adds components
	auto enemy1 = make_shared<Entity>();
	s = enemy1->addComponent<ShapeComponent>();
	i = enemy1->addComponent<EntityInfo>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(Vector2f(-500.0f, -200.0f));
	i->setStrength(10);
	i->setHealth(50);
	i->setDexterity(10);

	ents.list.push_back(enemy1);

	ChangeRoom();
}

void GameScene::Update(const double& dt) {
	//Changes scene to Menu ****TO REMOVE****
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
	//	activeScene = menuScene;
	}

	//Update from base class
	Scene::Update(dt);
}

//Renders Scene
void GameScene::Render() {
	Scene::Render();
}

//Does all the things needed when we change rooms
void GameScene::ChangeRoom() {
	//Updates the player's current enemy
	player->updateEnemy(ents.list[ents.list.size() - 1]);
}