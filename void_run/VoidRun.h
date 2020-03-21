#pragma once
//#include "Scene.h"
//#include "ecm.h"
#include <iostream>
#include "engine.h"
//#include "Game.h"

class MenuScene : public Scene {
private:
	sf::Text GameName;
	sf::Text PlayButton;
	sf::Text ExitButton;
	sf::Text OptionsButton;
	sf::Text ResButton;
	sf::Text ResChange;
	sf::Text ResText;
	sf::Text BackButton;
	sf::Font font;
	sf::FloatRect PlayButtonBox;
	sf::FloatRect ExitButtonBox;
	sf::FloatRect ResButtonBox;
	sf::FloatRect OptionsButtonBox;
	sf::FloatRect BackButtonBox;

	bool inOptions;

public:
	MenuScene() = default;
	~MenuScene() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void ChangeResolution(int x, int y);
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	~GameScene() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void ChangeRoom();
};
