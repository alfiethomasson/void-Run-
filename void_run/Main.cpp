#include <iostream>
#include <SFML/Graphics.hpp>
#include "System_Renderer.h"
#include "Scene.h"
#include "VoidRun.h"
#include "Game.h"
//#include "Scene.h"


using namespace sf;
using namespace std;

Color black(0, 0, 0);

float ghostNumber = 4;

EntityManager em;

void Load()
{
	// Load Scene-Local Assets
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->Load();
	menuScene->Load();
	// Start at main menu
	activeScene = menuScene;

}

void Update(RenderWindow& window)
{

	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->Update(dt);

	//quit via esc (TO REMOVE)
	if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		window.close();
	}

}

void Render(RenderWindow& window)
{ 
	activeScene->Render();
	// flush to screen
	Renderer::render();
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "VOID RUN()");
	Renderer::initialise(window);
	Load();
	while (window.isOpen()) {
		window.clear(black);
		Update(window);
		Render(window);
		window.display();
	}
}
