#include "VoidRun.h"
#include "Game.h"
#include "engine.h"
#include "CombatRoom.h"
#include "ItemDB.h"
#include "UI.h"
#include "System_Renderer.h"
#include "cmp_enemy.h"
#include "cmp_abilitymanager.h"
#include "TreasureRoom.h"
#include <fstream>
#include "LevelUpRoom.h"

using namespace sf; //Namespaces and other initialisation 
using namespace std;
ItemDB itemDB;

CombatRoom* testRoom;

sf::Event event;

sf::Color green(0, 255, 0, 255); //We use greeen to distinguish a highlighted button
sf::Color white(255, 255, 255, 255); //White is the default colour for our buttons

shared_ptr<Entity> pl;

bool isPaused;

sf::Time scene_delay;
sf::Clock scene_clock;
float sceneChangeDelay;

sf::Clock pauseClock;
sf::Time pause_delay;
float pauseDelay = 0.5f;

Keyboard::Key attackKey; //Various keys for interacting in the game
Keyboard::Key healKey;
Keyboard::Key rechargeKey;
Keyboard::Key runKey;
Keyboard::Key pauseKey;
Keyboard::Key special1Key;
Keyboard::Key special2Key;
Keyboard::Key special3Key;
Keyboard::Key special4Key;

int masterVolume = 100; //Volume controls in the settings
int musicVolume = 100;
int soundVolume = 100;

void MenuScene::Update(const double& dt) { //Menu Scene's Update Function

	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	titleMusic.setVolume(musicVolume * masterVolume/100);

	scene_delay = scene_clock.getElapsedTime();

	if (!inOptions)
	{
		if (Mouse::isButtonPressed(sf::Mouse::Left) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			if (NewGameButtonBox.contains(cursPos))
			{
				sound.play();
				titleMusic.stop();
				Engine::ChangeScene(&gameScene);
				gameScene.setLoadFromSave(false);
			}
			else if (LoadGameButtonBox.contains(cursPos) && LoadGameButton.getColor().a == 255)
			{
				sound.play();
				titleMusic.stop();
				Engine::ChangeScene(&gameScene);
				gameScene.setLoadFromSave(true);
			}
			else if (OptionsButtonBox.contains(cursPos))
			{
				sound.play();
				inOptions = true;
				scene_clock.restart();
			}
			else if (ExitButtonBox.contains(cursPos))
			{
				sound.play();
				Engine::GetWindow().close();
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			sound.play();
			titleMusic.stop();
			Engine::ChangeScene(&gameScene);
			gameScene.setLoadFromSave(false);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) && LoadGameButton.getColor().a == 255)
		{
			sound.play();
			titleMusic.stop();
			Engine::ChangeScene(&gameScene);
			gameScene.setLoadFromSave(true);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			sound.play();
			inOptions = true;
			scene_clock.restart();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			sound.play();
			titleMusic.stop();
			Engine::GetWindow().close();
		}

		//Checks if button box's contain mouse, and makes text green if so
		if (NewGameButtonBox.contains(cursPos))
		{
			NewGameButton.setFillColor(green);
		}
		else
		{
			NewGameButton.setFillColor(white);
		}

		if (LoadGameButton.getColor().a == 255)
		{
			if (LoadGameButtonBox.contains(cursPos))
			{
				LoadGameButton.setFillColor(green);
			}
			else
			{
				LoadGameButton.setFillColor(white);
			}
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
		Settings.Update(dt, cursPos);
}
	Scene::Update(dt);
	
}

//Renders Text
void MenuScene::Render() {
	//Queues text to render in system renderer
	if (!inOptions)
	{
		Renderer::queue(&GameName);
		Renderer::queue(&NewGameButton);
		Renderer::queue(&LoadGameButton);
		Renderer::queue(&ExitButton);
		Renderer::queue(&OptionsButton);
	}
	else
	{
		Settings.Render();
	}
	Scene::Render();
}

void MenuScene::Load() {

	//Loads font
	font.loadFromFile("res/Fonts/venusrising.ttf");

	Engine::tm.loadSound("ButtonPress", "Sounds/FX/ButtonPress.wav");
	sound.setBuffer(Engine::tm.getSound("ButtonPress"));
	sound.setVolume(soundVolume);

	//Loads music
	if (!titleMusic.openFromFile("res/Sounds/Music/TitleMusic.wav"))
	{
		cout << "Couldn't load title music\n";
	}

	//Starts music
	titleMusic.play();
	titleMusic.setVolume(50.0f);
	titleMusic.setLoop(true);

	//Assigns Font to Text
	GameName.setFont(font);
	NewGameButton.setFont(font);
	LoadGameButton.setFont(font);
	ExitButton.setFont(font);
	ResChange.setFont(font);
	ResButton.setFont(font);
	ResText.setFont(font);
	OptionsButton.setFont(font);
	BackButton.setFont(font);
	AttackText.setFont(font);
	HealText.setFont(font);
	RechargeText.setFont(font);
	RunText.setFont(font);
	Special1Text.setFont(font);
	Special2Text.setFont(font);
	Special3Text.setFont(font);
	Special4Text.setFont(font);
	AttackKeyText.setFont(font);
	HealKeyText.setFont(font);
	RechargeKeyText.setFont(font);
	RunKeyText.setFont(font);
	Special1KeyText.setFont(font);
	Special2KeyText.setFont(font);
	Special3KeyText.setFont(font);
	Special4KeyText.setFont(font);
	ResetControls.setFont(font);

	//Sets values for text
	GameName.setString("Void Run()");
	GameName.setCharacterSize(100);
	GameName.setPosition(sf::Vector2f(GAMEX / 2.0f - (GameName.getGlobalBounds().width / 2), 100.0f));
	NewGameButton.setString("NEW GAME - 1");
	NewGameButton.setCharacterSize(80);
	NewGameButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (NewGameButton.getGlobalBounds().width / 2), 300.0f));
	NewGameButtonBox = NewGameButton.getGlobalBounds(); //Creates the button boundaries
	LoadGameButton.setString("LOAD GAME - 2");
	LoadGameButton.setCharacterSize(80);
	LoadGameButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (LoadGameButton.getGlobalBounds().width / 2), 450.0f));
	LoadGameButtonBox = LoadGameButton.getGlobalBounds(); //Creates the button boundaries
	OptionsButton.setString("OPTIONS - 3");
	OptionsButton.setCharacterSize(80);
	OptionsButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (OptionsButton.getGlobalBounds().width / 2), 600.0f));
	OptionsButtonBox = OptionsButton.getGlobalBounds(); //Options Boundaries
	ExitButton.setString("EXIT - ESC");
	ExitButton.setCharacterSize(80);
	ExitButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (ExitButton.getGlobalBounds().width / 2), 750.0f));
	ExitButtonBox = ExitButton.getGlobalBounds(); //Button Boundaries
	ResChange.setString("1080p"); //Starts at 720p
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

	if (FILE* file = fopen("SaveStats.txt", "r"))
	{
		fclose(file);
		std::cout << "\nFOUND SAVE FILE\n";
	}
	else
	{
		LoadGameButton.setColor(sf::Color(255, 255, 255, 100));
		std::cout << "\NO SAVE FILE :((((((\n";
	}

	inOptions = false;

	sceneChangeDelay = 1.0f;

	attackKey = Keyboard::Num1;
	healKey = Keyboard::Num2;
	rechargeKey = Keyboard::Num3;
	runKey = Keyboard::Num4;
	pauseKey = Keyboard::Tab;
	special1Key = Keyboard::Q;
	special2Key = Keyboard::W;
	special3Key = Keyboard::E;
	special4Key = Keyboard::R;

	Settings.Load(font, false);
}

void MenuScene::setSettings(bool tf)
{
	Settings.UpdateSettings();
	inOptions = tf;
}

void GameScene::setPause(bool tf)
{
	Settings.UpdateSettings();
	combatUI.UpdateControls();
	isPaused = tf;
	if (tf)
	{
		gameMusic.pause();
	}
	else
	{
		gameMusic.play();
	}
}

void GameScene::Load() {

	LoadTextures();

	//Loads the settings icon stuff
	SettingSprite.setTexture(Engine::tm.getTex("Settings"));
	SettingSprite.setPosition(1800, 900.0f);
	SettingSprite.setScale(0.3f, 0.3f);
	SettingBox = SettingSprite.getGlobalBounds();

	//Loads the Save icon stuff
	SaveSprite.setTexture(Engine::tm.getTex("Save"));
	SaveSprite.setPosition(1700, 900.0f);
	SaveSprite.setScale(1.1f, 1.1f);
	SaveSprite.setColor(sf::Color(105, 105, 105, 255));
	SaveBox = SaveSprite.getGlobalBounds();

	font = Engine::tm.getFont();

	descText.setFont(font);
	descText.setCharacterSize(15);
	descText.setString("");


	PauseText.setFont(font);
	ResText.setFont(font);
	ResChange.setFont(font);
	ResButton.setFont(font);
	BackButton.setFont(font);

	itemDB.PopulateDB();
;
	if (loadFromSave)
	{
		std::string line;
		std::ifstream file;

		file.open("SaveStats.txt");
		int test = 0;
		int linenumber = 0 ;
		std::string string;
		float x;

		if (!file)
		{
			std::cout << "couldnt load file\n";
		}
		float HPMax = 0;
		float currentHP = 0;
		float strength = 0;
		float dex = 0;
		float exp = 0;
		int level = 0;

		if (file.is_open())
		{
			std::cout << "In save file :) \n";
			while (file >> x)
			{
				if (linenumber == 0)
				{
					currentHP = x;
				}
				else if (linenumber == 1)
				{
					HPMax = x;
				}
				else if (linenumber == 2)
				{
					strength = x;
				}
				else if (linenumber == 3)
				{
					dex = x;
				}
				else if (linenumber == 4)
				{
					exp = x;
				}
				else if (linenumber == 5)
				{
					level = x;
				}
				linenumber++;
			}
		}

		std::ifstream itemfile("SaveItems.txt");
		std::vector<std::string> items;
		std::vector<std::string> abilities;;
		bool inItem = true;
		if (itemfile.is_open())
		{
			while (std::getline(itemfile, line))
			{
				if (line == "END")
				{
					inItem = false;
				}
				else
				{
					if (inItem)
					{
						items.push_back(line);
					}
					else
					{
						abilities.push_back(line);
					}
				}
			}
		}
		//Creates Player and adds components
		pl = make_shared<Entity>();
		player = pl->addComponent<BasePlayerComponent>(HPMax, currentHP, strength, dex, exp, level, 10, &combatUI, &gameUI);
		am = pl->addComponent<AbilityManager>(4, &combatUI);
		am->Load();
		inv = pl->addComponent<Inventory>(6, &gameUI);
		inv->Load();
		playerSprite = pl->addComponent<PlayerSprite>();
		playerSprite->load();

		player->load();

		//Calls load function of the UIs
		combatUI.Load(player);
		gameUI.Load(10, player);

		for (auto &s : items)
		{
			if (s.at(0) == '*')
			{
				inv->add(itemDB.getSpecialItem(s), false);
			}
			else
			{
				inv->add(itemDB.getItem(s), false);
			}
		}

		for (auto& a : abilities)
		{
			auto i = itemDB.getAbility(a);
			i->updatePlayer(player);
			player->addAbility(itemDB.getAbility(a));
		}

		ents.list.push_back(pl);
	}
	else
	{

		//Creates Player and adds components
		pl = make_shared<Entity>();
		player = pl->addComponent<BasePlayerComponent>(100.0f, 100.0f, 20.0f, 10.0f, 0.0f, 1, 10, &combatUI, &gameUI);
		am = pl->addComponent<AbilityManager>(4, &combatUI);
		am->Load();
		inv = pl->addComponent<Inventory>(6, &gameUI);
		inv->Load();
		playerSprite = pl->addComponent<PlayerSprite>();
		playerSprite->load();
		ents.list.push_back(pl);

		player->load();

		//Calls load function of the UIs
		combatUI.Load(player);
		gameUI.Load(10, player);
	}

	textBox.setTexture(Engine::tm.getTex("TextBox"));
	textBox.setScale(sf::Vector2f(0.7f, 0.5f));
	textBox.setPosition(sf::Vector2f((GAMEX / 2) - (textBox.getGlobalBounds().width / 2), 100.0f));
	//ui.list.push_back(textBox);
	screenText.setFont(font);
	screenText.setString("Welcome to Void Run!");
	screenText.setCharacterSize(50);
	screenText.setFillColor(Color(255, 255, 255, 255));
	screenText.setPosition((textBox.getPosition().x + textBox.getGlobalBounds().width / 2) - (screenText.getGlobalBounds().width / 2),
		(textBox.getPosition().y + textBox.getGlobalBounds().height /2)- (screenText.getGlobalBounds().height));

	//Some initializing stuff
	alphaUpdate = 255;
	sceneChangeDelay = 0.5f;
	isPaused = false;

	//Loads music
	if (!gameMusic.openFromFile("res/Sounds/Music/GameMusic.wav"))
	{
		cout << "Couldn't load Game music\n";
	}

	//Starts music
	gameMusic.play();
	gameMusic.setVolume(50.0f);
	gameMusic.setLoop(true);

	Settings.Load(Engine::tm.getFont(), true);

	//Calls ChangeRoom to start the game with a random room
	ChangeRoom();
	
}

void GameScene::setLoadFromSave(bool tf)
{
	loadFromSave = tf;
}

void GameScene::Update(const double& dt) {
	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	gameMusic.setVolume(musicVolume * masterVolume/100);

	scene_delay = scene_clock.getElapsedTime();
	pause_delay = pauseClock.getElapsedTime();

	//Sets the text in the box to fade out after it is updated
	if (screenText.getFillColor().a != 0)
	{
		alphaUpdate -= 100 * dt;
		screenText.setFillColor(Color(255, 255, 255, alphaUpdate));
	}

	if (!isPaused)
	{
		if(currentRoom->isActive())
		{
			currentRoom->Update(dt, cursPos);
		}
		else
		{
			ChangeRoom();
		}
		//calls the current rooms update function
		gameUI.Update(dt, cursPos);

		//Adds random common item
		if (Keyboard::isKeyPressed(Keyboard::U) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();
			auto randItem = itemDB.randomCommonItem();
			UpdateTextBox(randItem->description);
			inv->add(randItem, true);
		}

		//Changes to a new room
		if (Keyboard::isKeyPressed(Keyboard::Space) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();
			ChangeRoom();
		}

		if (Keyboard::isKeyPressed(pauseKey) && pause_delay.asSeconds() >= pauseDelay)
		{
			pauseClock.restart();
			setPause(true);
		}

		//Checks if user clicks settings button
		if (SettingBox.contains(cursPos))
		{
			SettingSprite.setColor(green);
			if (Mouse::isButtonPressed(Mouse::Left) && pause_delay.asSeconds() >= pauseDelay)
			{
				pauseClock.restart();
				setPause(true);
			}
		}
		else
		{
			SettingSprite.setColor(white);
		}
		if (SaveBox.contains(cursPos))
		{
			SaveSprite.setColor(green);
			if (Mouse::isButtonPressed(Mouse::Left) && pause_delay.asSeconds() >= pauseDelay)
			{
				pauseClock.restart();
				SaveGame();
			}
		}
		else
		{
			SaveSprite.setColor(white);
		}
		//Update from base class
		Scene::Update(dt);
	}
	else
	{
		Settings.Update(dt, cursPos);
	}

	//Update from base class
	Scene::Update(dt);
}

//Renders Scene
void GameScene::Render() {
	if (!isPaused) // If game is not pause
	{
		gameUI.Render();
		currentRoom->Render();
		Scene::Render();
		Renderer::queue(&screenText);
		Renderer::queue(&SettingSprite);
		Renderer::queue(&SaveSprite);
		Renderer::queue(&descRect);
		Renderer::queue(&descText);
	}
	else // if paused
	{
		Settings.Render();
	}
}

//Does all the things needed when we change rooms
void GameScene::ChangeRoom() {
	player->expGained = false;

	if (ents.list.size() > 1)
	{
		ents.list[ents.list.size() - 1]->setForDelete();
	}
	//srand to ensure the random number is actually random
	srand(time(0));
	int roomType = rand() % 8;

	if (player->checkLevelUp()) {
		roomType = 10;
	}
	if (player->level > 5) {
		roomType = 0; //Once hitting level 5, the player will always go into a fight next.
	}

	if (roomType < 7) //Combat Room
	{
		UpdateTextBox("Entered Combat Room");
		//Makes new combat Room
		std::shared_ptr<CombatRoom> newRoom = make_shared<CombatRoom>(pl, &combatUI);
		//Calls load function of the new room 
		newRoom->Load();
		//Adds room to rooms vector
		rooms.push_back(newRoom);
		//Adds new entity's created by room 
		//into current scenes entity manager so they are renderered
		for each (auto e in newRoom->GetEnts())
		{
			ents.list.push_back(e);
		}
		//Set's current room to be the newly created room
		currentRoom = newRoom;
	}
	else if (roomType == 7) //Treasure Room
	{
		std::shared_ptr<TreasureRoom> newRoom = make_shared<TreasureRoom>(pl, itemDB);
		newRoom->Load();
		rooms.push_back(newRoom);
		currentRoom = newRoom;
		UpdateTextBox("Entered Treasure Room");
	}
	else if (roomType == 10)
	{
		std::shared_ptr<LevelUpRoom> newRoom = make_shared<LevelUpRoom>(pl);
		newRoom->Load();
		rooms.push_back(newRoom);
		currentRoom = newRoom;
		UpdateTextBox("Level Up!");
	}
}

Room& GameScene::getCurrentRoom()
{
	return *currentRoom;
}

//Updates the bounding boxes of all Buttons
void GameScene::UpdateButtons()
{
	Engine::UpdateButton(ResButtonBox);
	Engine::UpdateButton(BackButtonBox);
	Engine::UpdateButton(SettingBox);
}

//Updates the text inside the update box, to new text and resets the text to fade out
void GameScene::UpdateTextBox(sf::String newText)
{
	alphaUpdate = 255;
	screenText.setString(newText);
	screenText.setFillColor(Color(255, 255, 255, 255));
	screenText.setPosition((textBox.getPosition().x + textBox.getGlobalBounds().width / 2) - (screenText.getGlobalBounds().width / 2),
		(textBox.getPosition().y + textBox.getGlobalBounds().height / 2) - (screenText.getGlobalBounds().height));
}

void GameScene::LoadTextures()
{
	//Engine::tm.loadFont("venusrising.ttf");

	Engine::tm.loadTexture("Settings", "Icons/Settings.png");
	Engine::tm.loadTexture("Save", "Icons/Save.png");
	Engine::tm.loadTexture("TextBox", "Sprites/TextBox.png");
	Engine::tm.loadTexture("Attack", "Icons/Attack.png");
	Engine::tm.loadTexture("Heal", "Icons/Heal.png");
	Engine::tm.loadTexture("Recharge", "Icons/Recharge.png");
	Engine::tm.loadTexture("Run", "Icons/Run.png");
	Engine::tm.loadTexture("Charge", "Icons/Charge.png");
	Engine::tm.loadTexture("StatUp", "Icons/Arrow.png");
	Engine::tm.loadTexture("Player", "Sprites/Player.png");
	Engine::tm.loadTexture("ChestClosed", "Sprites/ChestClosed.png");
	Engine::tm.loadTexture("ChestOpen", "Sprites/ChestOpen.png");
	Engine::tm.loadTexture("QuestionMark", "Icons/QuestionMark.png");
	Engine::tm.loadTexture("Background1", "Sprites/BGspace1.jpg");
	Engine::tm.loadTexture("Pointy", "Icons/Pointy.png");
	Engine::tm.loadTexture("ExtraPadding", "Icons/ExtraPadding.png");
	Engine::tm.loadTexture("Stimulant", "Icons/Stimulant.png");
	Engine::tm.loadTexture("SpaceWatch", "Icons/SpaceWatch.png");
	Engine::tm.loadTexture("WristGuard", "Icons/WristGuard.png");
	Engine::tm.loadTexture("FaceMask", "Icons/FaceMask.png");
//	Engine::tm.loadTexture("Targeting Device", "Icons/SpaceWatch.png");
	Engine::tm.loadTexture("LaserBurst", "Icons/LaserBurst.png");
	Engine::tm.loadTexture("ChargedAttack", "Icons/ChargedAttack.png");
	Engine::tm.loadTexture("Curse", "Icons/Curse.png");
	Engine::tm.loadTexture("Dodge", "Icons/Dodge.png");
	Engine::tm.loadTexture("DoubleSlice", "Icons/DoubleSlice.png");
	Engine::tm.loadTexture("Enrage", "Icons/Enrage.png");
	Engine::tm.loadTexture("Excruciate", "Icons/Excruciate.png");
	Engine::tm.loadTexture("Bullseye", "Icons/Bullseye.png");
	Engine::tm.loadTexture("OverloadWeapon", "Icons/OverloadWeapon.png");
	Engine::tm.loadTexture("PrimalInstincts", "Icons/PrimalInstincts.png");
	Engine::tm.loadTexture("UncannySpeed", "Icons/UncannySpeed.png");
	Engine::tm.loadTexture("DeadlyFumes", "Icons/DeadlyFumes.png");
	Engine::tm.loadTexture("MagmaGrenade", "Icons/MagmaGrenade.png");
	Engine::tm.loadTexture("HoloGamble", "Icons/HoloGamble.png");
	Engine::tm.loadTexture("NanoBots", "Icons/NanoBots.png");
	Engine::tm.loadTexture("PainShare", "Icons/PainShare.png");
	Engine::tm.loadTexture("Regeneration", "Icons/Regeneration.png");
	Engine::tm.loadTexture("SuicideCharge", "Icons/SuicideCharge.png");
	Engine::tm.loadTexture("Aggressive", "Icons/Aggressive.png");
	Engine::tm.loadTexture("Defensive", "Icons/Defensive.png");
	Engine::tm.loadTexture("Passive", "Icons/Passive.png");
	Engine::tm.loadTexture("Desperate", "Icons/Desperate.png");
	Engine::tm.loadTexture("PlayerAttack", "Sprites/SpriteSheets/PlayerAttack.png");
	Engine::tm.loadTexture("PlayerHit", "Sprites/SpriteSheets/PlayerHit.png");
	Engine::tm.loadTexture("PlayerDie", "Sprites/SpriteSheets/PlayerDie.png");
	Engine::tm.loadTexture("PlayerRun", "Sprites/SpriteSheets/PlayerRun.png");
	Engine::tm.loadTexture("Alien1Attack", "Sprites/SpriteSheets/Alien1Attack.png");
	Engine::tm.loadTexture("Alien1Hit", "Sprites/SpriteSheets/Alien1Hit.png");
	Engine::tm.loadTexture("Alien1Die", "Sprites/SpriteSheets/Alien1Die.png");
	Engine::tm.loadTexture("Alien2Attack", "Sprites/SpriteSheets/Alien2Attack.png");
	Engine::tm.loadTexture("Alien2Hit", "Sprites/SpriteSheets/Alien2Hit.png");
	Engine::tm.loadTexture("Alien2Die", "Sprites/SpriteSheets/Alien2Die.png");
	Engine::tm.loadTexture("Alien3Attack", "Sprites/SpriteSheets/Alien3Attack.png");
	Engine::tm.loadTexture("Alien3Hit", "Sprites/SpriteSheets/Alien3Hit.png");
	Engine::tm.loadTexture("Alien3Die", "Sprites/SpriteSheets/Alien3Die.png");
	Engine::tm.loadTexture("BossAttack", "Sprites/SpriteSheets/BossAttack.png");
	Engine::tm.loadTexture("BossHit", "Sprites/SpriteSheets/BossHit.png");
	Engine::tm.loadTexture("BossDie", "Sprites/SpriteSheets/BossDie.png");
	Engine::tm.loadSound("Heal", "Sounds/FX/Heal.wav");
	Engine::tm.loadSound("Attack", "Sounds/FX/PlayerAttack.wav");
	Engine::tm.loadSound("Run", "Sounds/FX/Run.wav");
	Engine::tm.loadSound("Recharge", "Sounds/FX/Recharge.wav");
	Engine::tm.loadSound("LevelUp", "Sounds/FX/LevelUp.wav");
	Engine::tm.loadSound("StatUp", "Sounds/FX/StatUp.wav");
	Engine::tm.loadSound("ChestOpening", "Sounds/FX/ChestOpening.wav");
	Engine::tm.loadSound("ButtonPress", "Sounds/FX/ButtonPress.wav");
	Engine::tm.loadSound("PlayerHit", "Sounds/FX/PlayerHit.wav");
	Engine::tm.loadSound("PlayerDie", "Sounds/FX/PlayerDie.wav");
	Engine::tm.loadSound("MediumAttack", "Sounds/FX/MediumAttack.wav");
	Engine::tm.loadSound("HeavyAttack", "Sounds/FX/HeavyAttack.wav");
	Engine::tm.loadSound("PowerUp", "Sounds/FX/PowerUp.wav");
	Engine::tm.loadSound("WeakAttack", "Sounds/FX/WeakAttack.wav");
	Engine::tm.loadSound("UncannySpeed", "Sounds/FX/UncannySpeed.wav");
	Engine::tm.loadSound("Save", "Sounds/FX/Save.wav");
	Engine::tm.loadSound("Roar", "Sounds/FX/Roar.wav");
	Engine::tm.loadSound("OverloadWeapon", "Sounds/FX/OverloadWeapon.wav");
	Engine::tm.loadSound("NanoBots", "Sounds/FX/NanoBots.wav");
	Engine::tm.loadSound("MagmaGrenade", "Sounds/FX/MagmaGrenade.wav");
	Engine::tm.loadSound("HoloGamble", "Sounds/FX/HoloGamble.wav");
	Engine::tm.loadSound("DeadlyFumes", "Sounds/FX/DeadlyFumes.wav");
	Engine::tm.loadSound("LaserBurst", "Sounds/FX/LaserBurst.wav");
}

void GameScene::UpdateDesctext(std::string desc, sf::Vector2f pos)
{
	descText.setString(desc);
	descText.setPosition(pos.x - (descText.getGlobalBounds().width / 2), pos.y -
		descText.getGlobalBounds().height);
	descRect.setSize(sf::Vector2f(descText.getGlobalBounds().width, descText.getGlobalBounds().height + 20.0f));
	descRect.setFillColor(sf::Color(0, 0, 0, 255));
	descRect.setPosition(descText.getPosition());
}

void GameScene::ResetDescText()
{
	descText.setString("");
	descRect.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, 0.0f));
}

void GameScene::SaveGame()
{
	std::ofstream savefile("SaveStats.txt");
	if (savefile.is_open())
	{
		savefile << player->getCurrentHealth() << std::endl;
		savefile << player->getMaxHealth() << std::endl;
		savefile << player->getStrength() << std::endl;
		savefile << player->getDexterity() << std::endl;
		savefile << player->getExperience() << std::endl;
		savefile << player->level << std::endl;
	}
	else
	{
		std::cout << "Couldn't open savefile to save\n";	
	}

	std::ofstream iafile("SaveItems.txt");
	if (iafile.is_open())
	{
		for (auto i : inv->getItems())
		{
			iafile << i->name << std::endl;
		}
		iafile << "END" << std::endl;
		for (auto a : am->getSpecials())
		{
			iafile << a->getTexName() << std::endl;
		}
	}
	else
	{
		std::cout << "Couldn't open item and ability file to save\n";
	}

}

void VictoryScene::Render() //Render the victory scene
{
	//Queues text to render in system renderer
	Renderer::queue(&storyMessage);
	Renderer::queue(&thankYou);
	Renderer::queue(&credits);
	Renderer::queue(&menuButton);

	Scene::Render();
}

void VictoryScene::Load() //Main load function
{
	font.loadFromFile("res/Fonts/venusrising.ttf"); //Get the font
	sceneEnd = false;
	delayAmount = 2.0f;

	storyMessage.setFont(font); //Set up of the various messages on that screen
	storyMessage.setCharacterSize(20);
	storyMessage.setString("And with the defeat of the Alien Lord, Spaceship Omega had been saved once and for all.\nTroy McCool was able to return to Earth, heralded as the greatest hero of his decade.");
	thankYou.setFont(font);
	thankYou.setCharacterSize(20);
	thankYou.setString("Thank you for playing Void Run()");
	credits.setFont(font);
	credits.setCharacterSize(10);
	credits.setString("Made by Alfie & Ciaran");
	menuButton.setFont(font); //
	menuButton.setCharacterSize(10);
	menuButton.setString("Main Menu");

	storyMessage.setPosition(sf::Vector2f((GAMEX / 2) - (storyMessage.getGlobalBounds().width / 2), 300.0f)); //Position the messages
	thankYou.setPosition(sf::Vector2f((GAMEX / 2) - (thankYou.getGlobalBounds().width / 2), 500.0f));
	credits.setPosition(sf::Vector2f((GAMEX / 2) - (credits.getGlobalBounds().width / 2), 700.0f));
	menuButton.setPosition(sf::Vector2f((GAMEX / 2) - (menuButton.getGlobalBounds().width / 2), 950.0f));

	menuButtonBox = menuButton.getGlobalBounds(); //Creates the button boundaries

	victoryMusic.openFromFile("res/Sounds/Music/VictoryMusic.wav"); //Victory music
	victoryMusic.setLoop(true);
	victoryMusic.play();

}

void VictoryScene::Update(const double& dt) //Update Loop
{
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow()); //Get cursor position
	Vector2f cursPos = sf::Vector2f(tempPos);
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	delayTime = scene_clock.getElapsedTime().asSeconds(); //Delay so they can't accidentally hit Main Menu as soon as they enter
	victoryMusic.setVolume(musicVolume * masterVolume / 100);

	if (sceneEnd == true && delayTime >= delayAmount) //If they leave the scene
	{
		victoryMusic.stop(); //Stop the music
		Engine::ChangeScene(&menuScene); //Back to the main menu
	}

	if (menuButtonBox.contains(cursPos)) //If they mouse over the button, turn it green
	{
		menuButton.setFillColor(green);
	}
	else
	{
		menuButton.setFillColor(white); //Otherwise it's write
	}

	if (Mouse::isButtonPressed(sf::Mouse::Left) && sceneEnd == false) //If they're clicking
	{
		if (menuButtonBox.contains(cursPos)) //And on the menu button
		{
			delayClock.restart();
			sceneEnd = true; //Then the scene is over.
		}
	}
}