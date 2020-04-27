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

sf::Color green(0, 255, 0, 255); //We use greeen to distinguish a highlighted button
sf::Color white(255, 255, 255, 255); //White is the default colour for our buttons

shared_ptr<Entity> pl;

bool isPaused;

sf::Time scene_delay;
sf::Clock scene_clock;
float sceneChangeDelay;

//some delay stuff
sf::Clock pauseClock;
sf::Time pause_delay;
float pauseDelay = 0.5f;

//Extern values defined in game.h
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
	//Updates mouse position by window size
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	//Sets music volume to settings volumes
	titleMusic.setVolume(musicVolume * masterVolume/100);
	sound.setVolume(soundVolume * masterVolume / 100);

	scene_delay = scene_clock.getElapsedTime();

	if (!inOptions) // If on main screen, NOT in option
	{
		//Checks if any buttons are pressed
		if (Mouse::isButtonPressed(sf::Mouse::Left) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			if (NewGameButtonBox.contains(cursPos)) // Start New game
			{
				sound.play();
				titleMusic.stop();
				Engine::ChangeScene(&gameScene); // Change to gameScene
				gameScene.setLoadFromSave(false); // sets game to not load from save, start new game
			}
			else if (LoadGameButtonBox.contains(cursPos) && LoadGameButton.getColor().a == 255)
			{ // load game
				sound.play();
				titleMusic.stop();
				Engine::ChangeScene(&gameScene);  // move to gamescene
				gameScene.setLoadFromSave(true); // set gamescene to load from save not start new
			}
			else if (OptionsButtonBox.contains(cursPos)) // move to options
			{
				sound.play();
				inOptions = true;
				scene_clock.restart();
			}
			else if (ExitButtonBox.contains(cursPos)) // Quit game
			{
				sound.play();
				Engine::GetWindow().close();
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Num1)) // start new game
		{
			sound.play();
			titleMusic.stop();
			Engine::ChangeScene(&gameScene);
			gameScene.setLoadFromSave(false);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) && LoadGameButton.getColor().a == 255) //if load game is possible. loadgame
		{
			sound.play();
			titleMusic.stop();
			Engine::ChangeScene(&gameScene);
			gameScene.setLoadFromSave(true);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) && scene_delay.asSeconds() >= sceneChangeDelay) // move to option
		{
			sound.play();
			inOptions = true;
			scene_clock.restart();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) // quits game
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

		if (LoadGameButton.getColor().a == 255) // if loadgame is available
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
	else // in options
	{
		Settings.Update(dt, cursPos); // update settings screen
}
	Scene::Update(dt);
	
}

//Renders Text
void MenuScene::Render() {
	//Queues text to render in system renderer
	if (!inOptions) // not in options
	{
		Renderer::queue(&GameName);
		Renderer::queue(&NewGameButton);
		Renderer::queue(&LoadGameButton);
		Renderer::queue(&ExitButton);
		Renderer::queue(&OptionsButton);
	}
	else // in options
	{
		Settings.Render();
	}
	Scene::Render(); // call base render
}

void MenuScene::Load() {

	//Loads font
	font.loadFromFile("res/Fonts/venusrising.ttf"); // load font

	Engine::tm.loadSound("ButtonPress", "Sounds/FX/ButtonPress.wav"); // load sound into texturemanager
	sound.setBuffer(Engine::tm.getSound("ButtonPress")); // load UI button press sound into sound
	sound.setVolume(soundVolume);

	//Loads music
	if (!titleMusic.openFromFile("res/Sounds/Music/TitleMusic.wav"))
	{
		cout << "Couldn't load title music\n";
	}

	//Starts music
	titleMusic.play();
	titleMusic.setVolume(musicVolume * masterVolume / 100);
	titleMusic.setLoop(true);

	//Assigns Font to Texts
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

	//Sets default values
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

	//loads settings screen
	Settings.Load(font, false);
}

//Update setting screen
void MenuScene::setSettings(bool tf)
{
	Settings.UpdateSettings();
	inOptions = tf;
}

//Update controls and setting screen
void GameScene::setPause(bool tf)
{
	Settings.UpdateSettings();
	combatUI.UpdateControls();
	isPaused = tf;
	if (tf) // play or pause game music depending on going in or out of pause
	{
		gameMusic.pause();
	}
	else
	{
		gameMusic.play();
	}
}

void GameScene::Load() {

	//Calls load textures, loading the majority of textures and sounds used by the game
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

	//gets font
	font = Engine::tm.getFont();

	//sets default values for desctext, the tooltip showing what stuff is
	descText.setFont(font);
	descText.setCharacterSize(15);
	descText.setString("");
	 
	//loads fonts
	PauseText.setFont(font);
	ResText.setFont(font);
	ResChange.setFont(font);
	ResButton.setFont(font);
	BackButton.setFont(font);

	//calls populateDB on the item database, loading items and special abilities
	itemDB.PopulateDB();
;
	if (loadFromSave) // if loading from save
	{
		//default values for save file
		std::string line;
		std::ifstream file; // ifstream is read only file

		file.open("SaveStats.txt"); // Opens save file for stats
		int linenumber = 0 ;
		float x;

		if (!file)
		{
			std::cout << "couldnt load file\n";
		}

		//default values (will be changed)
		float HPMax = 0;
		float currentHP = 0;
		float strength = 0;
		float dex = 0;
		float exp = 0;
		int level = 0;

		//If file is succesfully opened
		if (file.is_open())
		{
			//While there is new numbers in file
			while (file >> x)
			{
				//depending on line number, sets variables to what is on save file
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
				//incremenets line number
				linenumber++;
			}
		}

		//Opens new ifstream (readonly) for items and abilities that are saved
		std::ifstream itemfile("SaveItems.txt");
		//empty vectors to store stuff in 
		std::vector<std::string> items;
		std::vector<std::string> abilities;;
		bool inItem = true; // items are first in txt
		if (itemfile.is_open()) // if file is opened succesfully
		{
			while (std::getline(itemfile, line)) // while there is new lines
			{
				if (line == "END") // Checks if the line is the "End" string, difference between items and abilities
				{
					inItem = false;
				}
				else
				{
					if (inItem) // before END is reached
					{
						items.push_back(line);
					}
					else // after END is reached
					{
						abilities.push_back(line);
					}
				}
			}
		}
		//Creates Player and adds components
		pl = make_shared<Entity>();
		//Creates base player component using our saved values
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

		//For all strings in items 
		for (auto &s : items)
		{
			if (s.at(0) == '*') // if item is a special item
			{
				inv->add(itemDB.getSpecialItem(s), false); // get item from item DB special items and add to inventory
			}
			else
			{
				inv->add(itemDB.getItem(s), false); // get item from item DB normal items and add to inventory
			}
		}

		//For all strings in abilities
		for (auto& a : abilities)
		{
			//Gets ability from itemDB
			auto i = itemDB.getAbility(a);
			//Sets player on new ability
			i->updatePlayer(player);
			//Adds ability to player
			player->addAbility(itemDB.getAbility(a));
		}
		//Adds player to ents to be rendered and updated
		ents.list.push_back(pl);
	}
	else // NOT loaded from save
	{

		//Creates Player and adds components
		pl = make_shared<Entity>();
		//default values
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

	//Some default text stuff
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

	//Initializing some values
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

	//Load pause screen ( same as settings on main menu
	Settings.Load(Engine::tm.getFont(), true);

	//Calls ChangeRoom to start the game with a random room
	ChangeRoom();
	
}

//Sets if scene should be loaded from save or not
void GameScene::setLoadFromSave(bool tf)
{
	loadFromSave = tf;
}

void GameScene::Update(const double& dt) {
	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);
	//updates curs pos depending on window size
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	//sets music volume
	gameMusic.setVolume(musicVolume * masterVolume/100);

	//gets delay time 
	scene_delay = scene_clock.getElapsedTime();
	pause_delay = pauseClock.getElapsedTime();

	//Sets the text in the box to fade out after it is updated
	if (screenText.getFillColor().a != 0)
	{
		alphaUpdate -= 100 * dt;
		screenText.setFillColor(Color(255, 255, 255, alphaUpdate));
	}

	if (!isPaused) // If game isnt paused
	{
		if(currentRoom->isActive()) // if current room is active and functional
		{
			currentRoom->Update(dt, cursPos); // update it!
		}
		else
		{
			ChangeRoom(); // Move to next room 
		}

		//Update gameUI
		gameUI.Update(dt, cursPos);
		//update Inventory
		inv->update(dt);

		if (Keyboard::isKeyPressed(pauseKey) && pause_delay.asSeconds() >= pauseDelay) // If pause key is pressed
		{
			pauseClock.restart();
			setPause(true); // Pause the game
		}

		//Checks if user clicks settings button
		if (SettingBox.contains(cursPos))
		{
			SettingSprite.setColor(green);
			if (Mouse::isButtonPressed(Mouse::Left) && pause_delay.asSeconds() >= pauseDelay) // if settings is pressed
			{
				pauseClock.restart();
				setPause(true); // Pause the game!
			}
		}
		else
		{
			SettingSprite.setColor(white);
		}
		if (SaveBox.contains(cursPos))
		{
			SaveSprite.setColor(green);
			if (Mouse::isButtonPressed(Mouse::Left) && pause_delay.asSeconds() >= pauseDelay) // if save is pressed
			{
				pauseClock.restart();
				SaveGame(); //save game!
			}
		}
		else
		{
			SaveSprite.setColor(white);
		}
	}
	else
	{
		Settings.Update(dt, cursPos); // Update pause screen
	}

	//Update from base class
	Scene::Update(dt);
}

//Renders Scene
void GameScene::Render() {
	if (!isPaused) // If game is not paused
	{
		//Renders UI
		gameUI.Render();
		//Renders Room
		currentRoom->Render();
		//Renders base scene
		Scene::Render();
		Renderer::queue(&screenText);
		Renderer::queue(&SettingSprite);
		Renderer::queue(&SaveSprite);
		Renderer::queue(&descRect);
		Renderer::queue(&descText);
	}
	else // if paused
	{
		Settings.Render(); //Render pause menu
	}
}

//Does all the things needed when we change rooms
void GameScene::ChangeRoom() {
	//Sets players exp gain to false to allow it to gain EXP again
	player->expGained = false;

	//makes sure that all ents are set for deletion except player
	if (ents.list.size() > 1)
	{
		ents.list[ents.list.size() - 1]->setForDelete();
	}
	//srand to ensure the random number is actually random
	srand(time(0));
	//Random number to check room type
	int roomType = rand() % 8;

	//If player has got enough EXP to level up
	if (player->checkLevelUp()) {
		roomType = 10; // set room type to 10 so next room will be a level up room
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
		//Make new Treasure Room
		std::shared_ptr<TreasureRoom> newRoom = make_shared<TreasureRoom>(pl, itemDB);
		newRoom->Load();
		//Set to current Room
		currentRoom = newRoom;
		UpdateTextBox("Entered Treasure Room");
	}
	else if (roomType == 10)
	{
		//Make level Up room
		std::shared_ptr<LevelUpRoom> newRoom = make_shared<LevelUpRoom>(pl);
		newRoom->Load();
		//Set to current Room
		currentRoom = newRoom;
		UpdateTextBox("Level Up!");
	}
}

//Return current Room
Room& GameScene::getCurrentRoom()
{
	return *currentRoom;
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
	//Loads all textures and sounds we need 
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

//Updates the tooltip to show what something does, called by UI and player.  Show what abilities etc do
void GameScene::UpdateDesctext(std::string desc, sf::Vector2f pos)
{
	descText.setString(desc);
	descText.setPosition(pos.x - (descText.getGlobalBounds().width / 2), pos.y -
		descText.getGlobalBounds().height);
	descRect.setSize(sf::Vector2f(descText.getGlobalBounds().width, descText.getGlobalBounds().height + 20.0f));
	descRect.setFillColor(sf::Color(0, 0, 0, 255));
	descRect.setPosition(descText.getPosition());
}

//Resets desc text to nothin
void GameScene::ResetDescText()
{
	descText.setString("");
	descRect.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, 0.0f));
}

//Saves game
void GameScene::SaveGame()
{
	//Opens savefile to write only
	std::ofstream savefile("SaveStats.txt");
	if (savefile.is_open()) // if it opened okay
	{
		//Writes players stats to SaveStats on new lines
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

	//Opens save file for items and abilities
	std::ofstream iafile("SaveItems.txt");
	if (iafile.is_open()) // If opened okay
	{
		//Loop through items and add them to save items on new lines
		for (auto i : inv->getItems())
		{
			iafile << i->name << std::endl;
		}
		iafile << "END" << std::endl; // Add "END" to save items to distinguish between items and abilities
		//Loops through special abilities and adds them to save items on new lines
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