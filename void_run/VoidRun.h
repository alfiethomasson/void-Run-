#pragma once
//#include "Scene.h"
//#include "ecm.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include "engine.h"
#include "CombatRoom.h"
#include "Room.h"
#include "ItemDB.h"
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

	sf::Music titleMusic;
	
	bool inOptions;

public:
	MenuScene() = default;
	~MenuScene() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UpdateButtons();
};

class GameScene : public Scene {
private:
	sf::Text PauseText;
	sf::Text ResButton;
	sf::Text ResChange;
	sf::Text ResText;
	sf::Text BackButton;
	sf::Font font;
	sf::FloatRect ResButtonBox;
	sf::FloatRect BackButtonBox;
	sf::Clock scoreClock;

	sf::FloatRect SettingBox;
	sf::Texture SettingIcon;
	sf::Sprite SettingSprite;

	std::vector<std::shared_ptr<Room>> rooms;
	std::shared_ptr<Room> currentRoom;

	sf::Sprite textBox;
	sf::Texture BoxTexture;

	float alphaUpdate;


public:
	sf::Text screenText;

	GameScene() = default;
	~GameScene() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void Pause();
	void ChangeRoom();
	bool playerTurn;
	void UpdateButtons();
	void UpdateTextBox(sf::String newText);
};
