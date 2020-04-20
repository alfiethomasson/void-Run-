#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "engine.h"
#include "CombatRoom.h"
#include "StatRoom.h"
#include "Room.h"
#include "ItemDB.h"
#include "UI.h"
#include "System_Renderer.h"
#include "System_resources.h"
#include "cmp_player.h"
#include "LevelUpRoom.h"
#include "cmp_enemy.h"
#include "cmp_inventory.h"
#include "cmp_sprite.h"
#include "cmp_abilitymanager.h"
#include "TreasureRoom.h"
#include <time.h>

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

	std::shared_ptr<Room> statRoom;

public:
	sf::Text screenText;
	CombatUI combatUI;
	GameUI gameUI;

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
