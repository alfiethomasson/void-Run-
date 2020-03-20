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

#define GAMEX 1280
#define GAMEY 720

using namespace sf;
using namespace std;

//std::shared_ptr<Scene> gameScene;
//std::shared_ptr<Scene> menuScene;
//std::shared_ptr<Scene> activeScene;

std::shared_ptr<BasePlayerComponent> player;

sf::Event event;

sf::Color green(0, 255, 0, 255);
sf::Color white(255, 255, 255, 255);

sf::FloatRect CalculateViewport(const sf::Vector2u & screensize, const sf::Vector2u & gamesize); 
void UpdateButton(FloatRect &button);

float xMultiply;
float yMultiply;


void MenuScene::Update(const double& dt) {
	

	std::cout << xMultiply;

	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);

	//while events are available to poll
	while (Engine::GetWindow().pollEvent(event))
	{
		//Switch for all event types
		switch (event.type)
		{
			case sf::Event::Closed:
				Engine::GetWindow().close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (PlayButtonBox.contains(cursPos))
					{
						Engine::ChangeScene(&gameScene);
					}
					if (ExitButtonBox.contains(cursPos))
					{
						Engine::GetWindow().close();
					}
				}

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					Engine::ChangeScene(&gameScene);
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					Engine::GetWindow().close();
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					// All together now in a reusable solution.
					const sf::Vector2u screensize(1920, 1080);
					const sf::Vector2u gamesize(GAMEX, GAMEY);
					//set View as normal
					Engine::GetWindow().setSize(screensize);
					sf::FloatRect visibleArea(0.f, 0.f, gamesize.x, gamesize.y);
					auto v = sf::View(visibleArea);
					// figure out how to scale and maintain aspect;
					auto viewport = CalculateViewport(screensize, gamesize);
					//Optionally Center it
					bool centered = true;
					if (centered) {
						viewport.left = (1.0 - viewport.width) * 0.5;
						viewport.top = (1.0 - viewport.height) * 0.5;
					}
					//set!
					v.setViewport(viewport);
					Engine::GetWindow().setView(v);
					//ExitButtonBox = ExitButton.getGlobalBounds();
					//std::cout << PlayButtonBox.getPosition().x << " , " << PlayButtonBox.getPosition().y << "\n";
					float winX = Engine::getWindowSize().x;
					float winY = Engine::getWindowSize().y;
					xMultiply = winX / GAMEX;
					yMultiply = winY / GAMEY;
					UpdateButton(PlayButtonBox);
					UpdateButton(ExitButtonBox);
					//std::cout << xMultiply << " , " << yMultiply << "\n";
					std::cout << PlayButtonBox.getPosition().x << " , " << PlayButtonBox.getPosition().y << "\n";
				}
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
	GameName.setPosition(sf::Vector2f(GAMEX / 2.0f - (GameName.getGlobalBounds().width / 2), GAMEY / 5.0f));
	PlayButton.setString("PLAY - 1");
	PlayButton.setCharacterSize(60);
	PlayButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (PlayButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 150.0f));
	PlayButtonBox = PlayButton.getGlobalBounds(); //Creates the button boundaries
	std::cout << PlayButtonBox.getPosition().x << " , " << PlayButtonBox.getPosition().y << "\n";
	ExitButton.setString("EXIT - 2");
	ExitButton.setCharacterSize(60);
	ExitButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (ExitButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 250.0f));
	ExitButtonBox = ExitButton.getGlobalBounds(); //Button Boundaries

	xMultiply = 1.0f;
	yMultiply = 1.0f;
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
	
	//UNCOMMENT TO SEE LOADING IN ACTION
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	setLoaded(true);
}

void GameScene::Update(const double& dt) {
	//Changes scene to Menu ****TO REMOVE****
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		Engine::ChangeScene(&menuScene);
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

// Create FloatRect to fits Game into Screen while preserving aspect
sf::FloatRect CalculateViewport(const sf::Vector2u& screensize,
	const sf::Vector2u& gamesize) {

	const Vector2f screensf(screensize.x, screensize.y);
	const Vector2f gamesf(gamesize.x, gamesize.y);
	const float gameAspect = gamesf.x / gamesf.y;
	const float screenAspect = screensf.x / screensf.y;
	float scaledWidth;  // final size.x of game viewport in piels
	float scaledHeight; //final size.y of game viewport in piels
	bool scaleSide = false; // false = scale to screen.x, true = screen.y

	//Work out which way to scale
	if (gamesize.x > gamesize.y) { // game is wider than tall
	  // Can we use full width?
		if (screensf.y < (screensf.x / gameAspect)) {
			//no, not high enough to fit game height
			scaleSide = true;
		}
		else {
			//Yes, use all width available
			scaleSide = false;
		}
	}
	else { // Game is Square or Taller than Wide
   // Can we use full height?
		if (screensf.x < (screensf.y * gameAspect)) {
			// No, screensize not wide enough to fit game width
			scaleSide = false;
		}
		else {
			// Yes, use all height available
			scaleSide = true;
		}
	}

	if (scaleSide) { // use max screen height
		scaledHeight = screensf.y;
		scaledWidth = floor(scaledHeight * gameAspect);
	}
	else { //use max screen width
		scaledWidth = screensf.x;
		scaledHeight = floor(scaledWidth / gameAspect);
	}

	//calculate as percent of screen
	const float widthPercent = (scaledWidth / screensf.x);
	const float heightPercent = (scaledHeight / screensf.y);

	return sf::FloatRect(0, 0, widthPercent, heightPercent);
}

void UpdateButton(FloatRect &button)
{
	button.width = button.width * xMultiply;
	button.height = button.height * yMultiply;
	button.left = button.left * xMultiply;
	button.top = button.top * yMultiply;
}
