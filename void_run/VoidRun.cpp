#include <iostream>
#include "VoidRun.h"
#include "ecm.h"
//#include "Entity.h"
//#include "Ghost.h"
//#include "Player.h"	
#include "System_Renderer.h"
#include "LevelSystem.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_entityinfo.h"

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

//#define GHOSTS_COUNT 4

void MenuScene::Update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::Update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::Render() {
	Renderer::queue(&text);
	Scene::Render();
}

void MenuScene::Load() {
	//Set up the text element here!

	if (!font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/GamesEngAlfie/res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}
	text.setFont(font);
}

void GameScene::Load() {
	auto pl = make_shared<Entity>(); 
	auto s = pl->addComponent<ShapeComponent>();
	//pl->addComponent<PlayerMovementComponent>();
	auto i = pl->addComponent<EntityInfo>();
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



/*
	const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
								 {219, 133, 28},   // orange Clyde
								 {70, 191, 238},   // cyan Inky
								 {234, 130, 229} }; // pink Pinky

	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		ghost->addComponent<EnemyAIComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(ghost);*/
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