#include "VoidRun.h"
#include "Game.h"
#include "engine.h"
#include "CombatRoom.h"
#include "StatRoom.h"
#include "ItemDB.h"
#include "UI.h"
#include "System_Renderer.h"
#include "cmp_enemy.h"
#include "cmp_abilitymanager.h"
#include "TreasureRoom.h"
#include <fstream>
#include "LevelUpRoom.h"

#define GAMEX 1280
#define GAMEY 720

using namespace sf;
using namespace std;
ItemDB itemDB;

CombatRoom* testRoom;

sf::Event event;

sf::Color green(0, 255, 0, 255);
sf::Color white(255, 255, 255, 255);

shared_ptr<Entity> pl;

bool isPaused;

sf::Time scene_delay;
sf::Clock scene_clock;
float sceneChangeDelay;

sf::Clock pauseClock;
sf::Time pause_delay;
float pauseDelay = 0.5f;

Keyboard::Key attackKey;
Keyboard::Key healKey;
Keyboard::Key rechargeKey;
Keyboard::Key runKey;
Keyboard::Key pauseKey;
Keyboard::Key special1Key;
Keyboard::Key special2Key;
Keyboard::Key special3Key;
Keyboard::Key special4Key;

void MenuScene::Update(const double& dt) {

	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	scene_delay = scene_clock.getElapsedTime();

	if (!inOptions)
	{
		if (Mouse::isButtonPressed(sf::Mouse::Left) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			if (NewGameButtonBox.contains(cursPos))
			{
				titleMusic.stop();
				Engine::ChangeScene(&gameScene);
				gameScene.setLoadFromSave(false);
			}
			else if (LoadGameButtonBox.contains(cursPos) && LoadGameButton.getColor().a == 255)
			{
				titleMusic.stop();
				Engine::ChangeScene(&gameScene);
				gameScene.setLoadFromSave(true);
			}
			else if (OptionsButtonBox.contains(cursPos))
			{
				inOptions = true;
				scene_clock.restart();
			}
			else if (ExitButtonBox.contains(cursPos))
			{
				Engine::GetWindow().close();
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			titleMusic.stop();
			Engine::ChangeScene(&gameScene);
			gameScene.setLoadFromSave(false);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) && LoadGameButton.getColor().a == 255)
		{
			titleMusic.stop();
			Engine::ChangeScene(&gameScene);
			gameScene.setLoadFromSave(true);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			inOptions = true;
			scene_clock.restart();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
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
	Engine::tm.loadFont("venusrising.ttf");
	font = Engine::tm.getFont();

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
	NewGameButton.setCharacterSize(60);
	NewGameButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (NewGameButton.getGlobalBounds().width / 2), 300.0f));
	NewGameButtonBox = NewGameButton.getGlobalBounds(); //Creates the button boundaries
	LoadGameButton.setString("LOAD GAME - 2");
	LoadGameButton.setCharacterSize(60);
	LoadGameButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (LoadGameButton.getGlobalBounds().width / 2), 400.0f));
	LoadGameButtonBox = LoadGameButton.getGlobalBounds(); //Creates the button boundaries
	OptionsButton.setString("OPTIONS - 3");
	OptionsButton.setCharacterSize(60);
	OptionsButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (OptionsButton.getGlobalBounds().width / 2), 500.0f));
	OptionsButtonBox = OptionsButton.getGlobalBounds(); //Options Boundaries
	ExitButton.setString("EXIT - ESC");
	ExitButton.setCharacterSize(60);
	ExitButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (ExitButton.getGlobalBounds().width / 2), 600.0f));
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

	Settings.Load();
}

void MenuScene::setSettings(bool tf)
{
	Settings.UpdateSettings();
	inOptions = tf;
}

void GameScene::setPause(bool tf)
{
	Settings.UpdateSettings();
	isPaused = tf;
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

		if (file.is_open())
		{
			std::cout << "In save file :) \n";
			while (file >> x)
			{
				if (linenumber == 0)
				{
					HPMax = x;
				}
				else if (linenumber == 1)
				{
					currentHP = x;
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
				linenumber++;
				//test += x;
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
		player = pl->addComponent<BasePlayerComponent>(HPMax, currentHP, strength, dex, exp, 10, &combatUI, &gameUI);
		am = pl->addComponent<AbilityManager>(3);
		inv = pl->addComponent<Inventory>(2, &gameUI);
		inv->Load();
		playerSprite = pl->addComponent<PlayerSprite>();
		playerSprite->load();

		player->load();

		//Calls load function of the UIs
		combatUI.Load(player, &Engine::tm);
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

		ents.list.push_back(pl);
	}
	else
	{

		//Creates Player and adds components
		pl = make_shared<Entity>();
		player = pl->addComponent<BasePlayerComponent>(100.0f, 100.0f, 20.0f, 10.0f, 0.0f, 10, &combatUI, &gameUI);
		am = pl->addComponent<AbilityManager>(3);
		inv = pl->addComponent<Inventory>(2, &gameUI);
		inv->Load();
		playerSprite = pl->addComponent<PlayerSprite>();
		playerSprite->load();
		ents.list.push_back(pl);

		player->load();

		//Calls load function of the UIs
		combatUI.Load(player, &Engine::tm);
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

	std::shared_ptr<StatRoom> statRoom = std::make_shared<StatRoom>(pl);

	//Loads music
	if (!gameMusic.openFromFile("res/Sounds/Music/GameMusic.wav"))
	{
		cout << "Couldn't load Game music\n";
	}

	//Starts music
	gameMusic.play();
	gameMusic.setVolume(50.0f);
	gameMusic.setLoop(true);

	Settings.Load();

	//Calls ChangeRoom to start the game with a random room
	ChangeRoom();
	
	//UNCOMMENT TO SEE LOADING IN ACTION
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//setLoaded(true);
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
	scene_delay = scene_clock.getElapsedTime();
	pause_delay = pauseClock.getElapsedTime();

	//Sets the text in the box to fade out after it is updated
	if (screenText.getFillColor().a != 0)
	{
		alphaUpdate -= 0.1;
		screenText.setFillColor(Color(255, 255, 255, alphaUpdate));
	}

	if (!isPaused)
	{
		if(currentRoom->isActive())
		{
			currentRoom->Update(dt);
		}
		else
		{
			ChangeRoom();
		}
		//calls the current rooms update function
		gameUI.Update(dt);

		//Adds random special item to inventory
		if (Keyboard::isKeyPressed(Keyboard::I) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			auto tempItem = itemDB.randomSpecialItem();
			UpdateTextBox(tempItem->description);
			inv->add(tempItem, true);
			scene_clock.restart();
			//std::cout << "\nshould play attack\n";
			std::cout << "MouseX: " << Mouse::getPosition().x << " MouseY: " << Mouse::getPosition().y << "\n";
			std::cout << "Adjusted MouseX: " << cursPos.x << " Adjusted MouseY: " << cursPos.y << "\n";

		}

		//Removes an item from the inventory
		if (Keyboard::isKeyPressed(Keyboard::R) && inv->getItems().size() != 0 && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			inv->remove(0);
			scene_clock.restart();
		}

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
			isPaused = true;
		}

		//Checks if user clicks settings button
		if (SettingBox.contains(cursPos))
		{
			SettingSprite.setColor(green);
			if (Mouse::isButtonPressed(Mouse::Left) && pause_delay.asSeconds() >= pauseDelay)
			{
				pauseClock.restart();
				isPaused = true;
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
	int roomType = rand() % 2;
	//TODO: Make it so that if the player's EXP is enough to level up, then the room automatically sets to 2, otherwise it is set to 0 or 1 aat random.
	if (player->checkLevelUp()) {
		roomType = 2;
	}
	if (player->level >= 5) {
		roomType = 0; //Once hitting level 5, the player will always go into a fight next.
	}

	if (roomType == 0) //Combat Room
	{
		UpdateTextBox("Entered Combat Room");
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
			ents.list.push_back(e);
		}
		//Set's current room to be the newly created room
		currentRoom = newRoom;
	}
	else if (roomType == 1) //Treasure Room
	{
		std::shared_ptr<TreasureRoom> newRoom = make_shared<TreasureRoom>(pl, itemDB);
		newRoom->Load();
		rooms.push_back(newRoom);
		currentRoom = newRoom;
		UpdateTextBox("Entered Treasure Room");
	}
	else if (roomType == 2)
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
	Engine::tm.loadTexture("PainShare", "Icons/PainShare.png");
	Engine::tm.loadTexture("Regeneration", "Icons/Regeneration.png");
	Engine::tm.loadTexture("SuicideCharge", "Icons/SuicideCharge.png");
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
	Engine::tm.loadSound("Heal", "Sounds/FX/Heal.wav");
	Engine::tm.loadSound("Attack", "Sounds/FX/PlayerAttack.wav");
	Engine::tm.loadSound("Run", "Sounds/FX/Run.wav");
	Engine::tm.loadSound("Recharge", "Sounds/FX/Recharge.wav");
	Engine::tm.loadSound("LevelUp", "Sounds/FX/LevelUp.wav");
	Engine::tm.loadSound("StatUp", "Sounds/FX/StatUp.wav");
	Engine::tm.loadSound("ChestOpening", "Sounds/FX/ChestOpening.wav");
	Engine::tm.loadSound("ButtonPress", "Sounds/FX/ButtonPress.wav");
	Engine::tm.loadSound("PlayerHit", "Sounds/FX/PlayerHit.wav");
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
	//if (FILE* file = fopen("res/Saves/Save.txt", "r"))
	//{
	//	fclose(file);
	//	if (std::remove("res/Saves/Save.txt") != 0)
	//	{
	//	std::cout << "Couldnt delete save\n";
	//	}
	//	else
	//	{
	//		std::cout << "deletedsave save\n";
	//	}
	//}
	std::ofstream savefile("SaveStats.txt");
	if (savefile.is_open())
	{
		savefile << player->getCurrentHealth() << std::endl;
		savefile << player->getMaxHealth() << std::endl;
		savefile << player->getStrength() << std::endl;
		savefile << player->getDexterity() << std::endl;
		savefile << player->getExperience() << std::endl;
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
			iafile << a->texName << std::endl;
		}
	}
	else
	{
		std::cout << "Couldn't open item and ability file to save\n";
	}

}