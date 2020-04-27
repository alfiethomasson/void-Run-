#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>  
#include "cmp_player.h"
#include "Room.h"
#include "cmp_inventory.h"
#include "PlayerSprite.h"
#include "LevelUpRoom.h"
#include "cmp_enemy.h"
#include "cmp_sprite.h"
#include "cmp_abilitymanager.h"
#include "TreasureRoom.h"
#include <time.h>

class PlayerSprite;

class MenuScene : public Scene {
private:
	sf::Text GameName;
	sf::Text NewGameButton;
	sf::Text LoadGameButton;
	sf::Text ExitButton;
	sf::Text OptionsButton;
	sf::Text ResButton;
	sf::Text ResChange;
	sf::Text ResText;
	sf::Text ToControlText;
	sf::Text AttackText;
	sf::Text HealText;
	sf::Text RechargeText;
	sf::Text RunText;
	sf::Text PauseText;
	sf::Text Special1Text;
	sf::Text Special2Text;
	sf::Text Special3Text;
	sf::Text Special4Text;
	sf::Text AttackKeyText;
	sf::Text HealKeyText;
	sf::Text RechargeKeyText;
	sf::Text RunKeyText;
	sf::Text PauseKeyText;
	sf::Text Special1KeyText;
	sf::Text Special2KeyText;
	sf::Text Special3KeyText;
	sf::Text Special4KeyText;
	sf::Text ResetControls;
	sf::Text BackButton;
	sf::Text toChangeControls;
	sf::Font font;
	sf::FloatRect NewGameButtonBox;
	sf::FloatRect LoadGameButtonBox;
	sf::FloatRect ExitButtonBox;
	sf::FloatRect ResButtonBox;
	sf::FloatRect OptionsButtonBox;
	sf::FloatRect BackButtonBox;

	sf::Music titleMusic;
	
	bool inOptions;
	bool inControls;

	SettingUI Settings;

public:
	MenuScene() = default;
	~MenuScene() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void ChangeControls();
	void UpdateButtons();
	void setSettings(bool tf);
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

	sf::FloatRect SaveBox;
	sf::Texture SaveIcon;
	sf::Sprite SaveSprite;

	std::shared_ptr<Room> currentRoom;

	sf::Sprite textBox;
	sf::Texture BoxTexture;

	float alphaUpdate;

	std::shared_ptr<Room> statRoom;

	std::shared_ptr<BasePlayerComponent> player;
	std::shared_ptr<Inventory> inv;
	std::shared_ptr<AbilityManager> am;
	std::shared_ptr<PlayerSprite> playerSprite;

	bool loadFromSave;

	SettingUI Settings;

	ItemDB itemDB;

public:
	sf::Text screenText;
	CombatUI combatUI;
	GameUI gameUI;
	sf::Music gameMusic;

	sf::Text descText;
	sf::RectangleShape descRect;

	GameScene() = default;
	~GameScene() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void Pause();
	void ChangeRoom();
	bool playerTurn;
	void UpdateTextBox(sf::String newText);
	void LoadTextures() override;
	void UpdateDesctext(std::string, sf::Vector2f pos);
	void ResetDescText();
	void setLoadFromSave(bool tf);

	void setPause(bool tf);

	void SaveGame();

	Room& getCurrentRoom();
};

class VictoryScene : public Scene {
private:
	sf::Text storyMessage;
	sf::Text thankYou;
	sf::Text credits;
	sf::Text menuButton;

	sf::Font font;
	sf::FloatRect menuButtonBox;

	sf::Music victoryMusic;
	bool sceneEnd;

	sf::Clock delayClock;
	int delayTime;
	int delayAmount;

public:
	VictoryScene() = default;
	~VictoryScene() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
};