#include "VoidRun.h"
#include "Game.h"
#include <iostream>
#include "System_Renderer.h"
#include "System_resources.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_enemy.h"
#include "engine.h"
#include "CombatRoom.h"
#include "TreasureRoom.h"
#include <time.h>  

#define GAMEX 1280
#define GAMEY 720

using namespace sf;
using namespace std;

//std::shared_ptr<Scene> gameScene;
//std::shared_ptr<Scene> menuScene;
//std::shared_ptr<Scene> activeScene;

std::shared_ptr<BasePlayerComponent> player;

CombatRoom* testRoom;

sf::Event event;
bool isPaused = false;

sf::Color green(0, 255, 0, 255);
sf::Color white(255, 255, 255, 255);

shared_ptr<Entity> pl;

sf::Time scene_delay;
sf::Clock scene_clock;
float sceneChangeDelay;

void MenuScene::Update(const double& dt) {

	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);

	scene_delay = scene_clock.getElapsedTime();

	if (!inOptions)
	{
		if (Mouse::isButtonPressed(sf::Mouse::Left) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			if (PlayButtonBox.contains(cursPos))
			{
				Engine::ChangeScene(&gameScene);
			}
			if (OptionsButtonBox.contains(cursPos))
			{
				inOptions = true;
				scene_clock.restart();
			}
			if (ExitButtonBox.contains(cursPos))
			{
				Engine::GetWindow().close();
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			Engine::ChangeScene(&gameScene);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			Engine::GetWindow().close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			inOptions = true;
			scene_clock.restart();
			std::cout << "Bruh.";
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

		if (OptionsButtonBox.contains(cursPos))
		{
			OptionsButton.setFillColor(green);
		}
		else
		{
			OptionsButton.setFillColor(white);
		}
	}
	else
	{
		if ((Keyboard::isKeyPressed(sf::Keyboard::Right) || (Mouse::isButtonPressed(sf::Mouse::Left) && ResButtonBox.contains(cursPos)))
			&& scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();

			if (Engine::getWindowSize().y != 1080)
			{
				ResChange.setString("1080p");
				ChangeResolution(1920, 1080, GAMEX, GAMEY);
				UpdateButtons();
			}
			else
			{
				ResChange.setString("720p");
				ChangeResolution(1280, 720, GAMEX, GAMEY);
				UpdateButtons();
			}
		}
		if ((Keyboard::isKeyPressed(sf::Keyboard::Num2) || (Mouse::isButtonPressed(sf::Mouse::Left) && BackButtonBox.contains(cursPos)))
			&& scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();
			inOptions = false;
		}

	if (ResButtonBox.contains(cursPos))
	{
		ResButton.setFillColor(green);
	}
	else
	{
		ResButton.setFillColor(white);
	}
	if (BackButtonBox.contains(cursPos))
	{
		BackButton.setFillColor(green);
	}
	else
	{
		BackButton.setFillColor(white);
	}
}
	Scene::Update(dt);
	
}

//Renders Text
void MenuScene::Render() {
	//Queues text to render in system renderer
	if (!inOptions)
	{
		Renderer::queue(&GameName);
		Renderer::queue(&PlayButton);
		Renderer::queue(&ExitButton);
		Renderer::queue(&OptionsButton);
	}
	else
	{
		Renderer::queue(&ResChange);
		Renderer::queue(&ResText);
		Renderer::queue(&ResButton);
		Renderer::queue(&BackButton);
	}
	Scene::Render();
}

void MenuScene::Load() {
	//Loads font
	//if (!font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/void-Run-/res/Fonts/mandalore.ttf"))
	if (!font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/void-Run-/res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}
	//const string& fontName = "Mandalore";
	//Resources::load(fontName);

	//Assigns Font to Text
	GameName.setFont(font);
	PlayButton.setFont(font);
	ExitButton.setFont(font);
	ResChange.setFont(font);
	ResButton.setFont(font);
	ResText.setFont(font);
	OptionsButton.setFont(font);
	BackButton.setFont(font);

	//Sets values for text
	GameName.setString("Void Run()");
	GameName.setCharacterSize(100);
	GameName.setPosition(sf::Vector2f(GAMEX / 2.0f - (GameName.getGlobalBounds().width / 2), GAMEY / 5.0f));
	PlayButton.setString("PLAY - 1");
	PlayButton.setCharacterSize(60);
	PlayButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (PlayButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 150.0f));
	PlayButtonBox = PlayButton.getGlobalBounds(); //Creates the button boundaries
	ExitButton.setString("EXIT - ESC");
	ExitButton.setCharacterSize(60);
	ExitButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (ExitButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 350.0f));
	ExitButtonBox = ExitButton.getGlobalBounds(); //Button Boundaries
	OptionsButton.setString("OPTIONS - 2");
	OptionsButton.setCharacterSize(60);
	OptionsButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (OptionsButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 250.0f));
	OptionsButtonBox = OptionsButton.getGlobalBounds(); //Options Boundaries
	ResChange.setString("720p"); //Starts at 720p
	ResChange.setCharacterSize(60);
	ResChange.setPosition(sf::Vector2f(GAMEX / 2.0f - (ResChange.getGlobalBounds().width / 2), GAMEY / 2.0f - (ResChange.getGlobalBounds().height / 2)));
	ResText.setString("Resolution: ");
	ResText.setCharacterSize(60);
	ResText.setPosition(sf::Vector2f(GAMEX / 2.0f - 300.0f, GAMEY / 2.0f - (ResText.getGlobalBounds().height / 2)));
	ResButton.setString(" > ");
	ResButton.setCharacterSize(60);
	ResButton.setPosition(sf::Vector2f(GAMEX / 2.0f + 80.0f, GAMEY / 2.0f - (ResButton.getGlobalBounds().height / 2)));
	ResButtonBox = ResButton.getGlobalBounds();
	BackButton.setString("BACK - 2");
	BackButton.setCharacterSize(60);
	BackButton.setPosition(sf::Vector2f(GAMEX / 2.0f - 300.0f, GAMEY / 2.0f - (BackButton.getGlobalBounds().height / 2) + 50.0f));
	BackButtonBox = BackButton.getGlobalBounds();

	//buttons.push_back(PlayButtonBox);
//	buttons.push_back(ExitButtonBox);
	buttons.push_back(ResButtonBox);
	//buttons.push_back(OptionsButtonBox);
	//buttons.push_back(BackButtonBox);

	xMultiply = 1.0f; //Initial values for variables
	yMultiply = 1.0f;
	inOptions = false;

	sceneChangeDelay = 1.0f;
}

void MenuScene::UpdateButtons()
{
	UpdateButton(PlayButtonBox);
	UpdateButton(ExitButtonBox);
	UpdateButton(ResButtonBox);
	UpdateButton(OptionsButtonBox);
	UpdateButton(BackButtonBox);
}

void GameScene::Load() {

	if (!font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/void-Run-/res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}

	if (!SettingIcon.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/void-Run-/res/Sprites/WhiteSquare.png"))
	{
		cout << "Could not load setting icon White\n";
	}

	SettingSprite.setTexture(SettingIcon);
	SettingSprite.setPosition(1150.0f, 600.0f);
	SettingSprite.setScale(0.2f, 0.2f);
	SettingBox = SettingSprite.getGlobalBounds();

	PauseText.setFont(font);
	ResText.setFont(font);
	ResChange.setFont(font);
	ResButton.setFont(font);
	BackButton.setFont(font);
	PauseText.setString("PAUSED");
	PauseText.setCharacterSize(100);
	PauseText.setPosition(sf::Vector2f(GAMEX / 2 - (PauseText.getGlobalBounds().width / 2), 200.0f));

	cout << Engine::getWindowSize().y << "\n";
	ResChange.setString(to_string(Engine::getWindowSize().y) + "p"); //Starts at 720p
	ResChange.setCharacterSize(60);
	ResChange.setPosition(sf::Vector2f(GAMEX / 2.0f - (ResChange.getGlobalBounds().width / 2), GAMEY / 2.0f - (ResChange.getGlobalBounds().height / 2)));
	ResText.setString("Resolution: ");
	ResText.setCharacterSize(60);
	ResText.setPosition(sf::Vector2f(GAMEX / 2.0f - 300.0f, GAMEY / 2.0f - (ResText.getGlobalBounds().height / 2)));
	ResButton.setString(" > ");
	ResButton.setCharacterSize(60);
	ResButton.setPosition(sf::Vector2f(GAMEX / 2.0f + 80.0f, GAMEY / 2.0f - (ResButton.getGlobalBounds().height / 2)));
	ResButtonBox = ResButton.getGlobalBounds();

	buttons.push_back(SettingBox);
	buttons.push_back(ResButtonBox);

	//Creates Player and adds components
	pl = make_shared<Entity>(); 
	auto s = pl->addComponent<ShapeComponent>();
	//pl->addComponent<PlayerMovementComponent>();
	auto i = pl->addComponent<EntityInfo>();
	player = pl->addComponent<BasePlayerComponent>(100.0f, 20.0f, 10.0f);
	s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(-200.0f, -200.0f));
	i->setStrength(10);
	i->setHealth(50);
	i->setDexterity(10);
	ents.list.push_back(pl);

	//ents.list.push_back(pl);

	sceneChangeDelay = 1.0f;

	ChangeRoom();
	
	//UNCOMMENT TO SEE LOADING IN ACTION
//	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//setLoaded(true);
}

void GameScene::Update(const double& dt) {
	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);

	if (!isPaused)
	{
		scene_delay = scene_clock.getElapsedTime();
		currentRoom->Update(dt);

		if (Keyboard::isKeyPressed(Keyboard::Space) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();
			ChangeRoom();
		}
		if (SettingBox.contains(cursPos))
		{
			SettingSprite.setColor(green);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				isPaused = true;
			}
		}
		else
		{
			SettingSprite.setColor(white);
		}
		//Update from base class
		Scene::Update(dt);
	}
	else
	{
		if (Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (ResButtonBox.contains(cursPos))
				{
					if (Engine::getWindowSize().y != 1080)
					{
						ResChange.setString("1080p");
						ChangeResolution(1920, 1080, GAMEX, GAMEY);
					}
					else
					{
						ResChange.setString("720p");
						ChangeResolution(1280, 720, GAMEX, GAMEY);
					}
				}
				if (BackButtonBox.contains(cursPos))
				{
					isPaused = false;
				}
			}
		if (Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (Engine::getWindowSize().y != 1080)
				{
					ResChange.setString("1080p");
					ChangeResolution(1920, 1080, GAMEX, GAMEY);
					UpdateButtons();
				}
				else
				{
					ResChange.setString("720p");
					ChangeResolution(1280, 720, GAMEX, GAMEY);
					UpdateButtons();
				}
			}
		if(Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				isPaused = false;
			}
	}

	//Update from base class
	Scene::Update(dt);
}

//Renders Scene
void GameScene::Render() {
	if (!isPaused)
	{
		Renderer::queue(&SettingSprite);
		Scene::Render();
	}
	else
	{
		Renderer::queue(&PauseText);
		Renderer::queue(&ResButton);
		Renderer::queue(&ResChange);
		Renderer::queue(&ResText);
		Renderer::queue(&BackButton);
	}
}

//Does all the things needed when we change rooms
void GameScene::ChangeRoom() {
	//Updates the player's current enemy
	//player->updateEnemy(ents.list[ents.list.size() - 1]);

	//Makes sure you don't delete the player entity
	if(ents.list.size() > 1)
	{
		ents.list[ents.list.size() - 1]->setForDelete();
	}
	//srand to ensure the random number is actually random
	srand(time(0));
	int roomType = rand() % 2;
	if (roomType == 0) //Combat Room
	{
		//Makes new combat Room
		std::shared_ptr<CombatRoom> newRoom = make_shared<CombatRoom>(pl);
		//Calls load function of the new room 
		newRoom->Load();
		//Adds room to rooms vector
		rooms.push_back(newRoom);
		//Adds new entity's created by room 
		//into current scenes entity manager so they are renderered
		for each (auto e in newRoom->GetEnts())
		{
			//Updates the player's current enemy
		//	player->updateEnemy(ents.list[ents.list.size() - 1]);
			ents.list.push_back(e);
		}
		//Set's current room to be the newly created room
		currentRoom = newRoom;
	}
	else if(roomType == 1) //Treasure Room
	{
		std::shared_ptr<TreasureRoom> newRoom = make_shared<TreasureRoom>();
		newRoom->Load();
		rooms.push_back(newRoom);
		currentRoom = newRoom;
	}
	
}

//Need to fill in Pause function
void GameScene::Pause() {
}

void GameScene::UpdateButtons()
{
	UpdateButton(ResButtonBox);
	UpdateButton(BackButtonBox);
	UpdateButton(SettingBox);
}

