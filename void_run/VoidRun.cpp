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

void MenuScene::Update(const double& dt) {

	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);

	scene_delay = scene_clock.getElapsedTime();

	if (!inOptions)
	{
		if (Mouse::isButtonPressed(sf::Mouse::Left) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			if (PlayButtonBox.contains(cursPos))
			{
				titleMusic.stop();
				Engine::ChangeScene(&gameScene);
			}
			if (OptionsButtonBox.contains(cursPos))
			{
				inOptions = true;
				scene_clock.restart();
			}
			if (ExitButtonBox.contains(cursPos))
			{
				Engine::GetWindow().close();
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			titleMusic.stop();
			Engine::ChangeScene(&gameScene);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			Engine::GetWindow().close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			inOptions = true;
			scene_clock.restart();
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
		if ((Keyboard::isKeyPressed(sf::Keyboard::Right) || (Mouse::isButtonPressed(sf::Mouse::Left) && ResButtonBox.contains(cursPos)))
			&& scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();

			if (Engine::getWindowSize().y != 1080)
			{
				ResChange.setString("1080p");
				ChangeResolution(1920, 1080, GAMEX, GAMEY);
				UpdateButtons();
			}
			else
			{
				ResChange.setString("720p");
				ChangeResolution(1280, 720, GAMEX, GAMEY);
				UpdateButtons();
			}
		}
		if ((Keyboard::isKeyPressed(sf::Keyboard::Num2) || (Mouse::isButtonPressed(sf::Mouse::Left) && BackButtonBox.contains(cursPos)))
			&& scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();
			inOptions = false;
		}

	if (ResButtonBox.contains(cursPos))
	{
		ResButton.setFillColor(green);
	}
	else
	{
		ResButton.setFillColor(white);
	}
	if (BackButtonBox.contains(cursPos))
	{
		BackButton.setFillColor(green);
	}
	else
	{
		BackButton.setFillColor(white);
	}
}
	Scene::Update(dt);
	
}

//Renders Text
void MenuScene::Render() {
	//Queues text to render in system renderer
	if (!inOptions)
	{
		Renderer::queue(&GameName);
		Renderer::queue(&PlayButton);
		Renderer::queue(&ExitButton);
		Renderer::queue(&OptionsButton);
	}
	else
	{
		Renderer::queue(&ResChange);
		Renderer::queue(&ResText);
		Renderer::queue(&ResButton);
		Renderer::queue(&BackButton);
	}
	Scene::Render();
}

void MenuScene::Load() {
	//Loads font
	if (!font.loadFromFile("res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}

	//Loads music
	if (!titleMusic.openFromFile("res/Sounds/Music/TitleMusic.wav"))
	{
		cout << "Couldn't load title music\n";
	}

	//Starts music
	titleMusic.play();
	titleMusic.setVolume(50.0f);
	titleMusic.setLoop(true);
	//const string& fontName = "Mandalore";
	//Resources::load(fontName);

	//Assigns Font to Text
	GameName.setFont(font);
	PlayButton.setFont(font);
	ExitButton.setFont(font);
	ResChange.setFont(font);
	ResButton.setFont(font);
	ResText.setFont(font);
	OptionsButton.setFont(font);
	BackButton.setFont(font);

	//Sets values for text
	GameName.setString("Void Run()");
	GameName.setCharacterSize(100);
	GameName.setPosition(sf::Vector2f(GAMEX / 2.0f - (GameName.getGlobalBounds().width / 2), GAMEY / 5.0f));
	PlayButton.setString("PLAY - 1");
	PlayButton.setCharacterSize(60);
	PlayButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (PlayButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 150.0f));
	PlayButtonBox = PlayButton.getGlobalBounds(); //Creates the button boundaries
	ExitButton.setString("EXIT - ESC");
	ExitButton.setCharacterSize(60);
	ExitButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (ExitButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 350.0f));
	ExitButtonBox = ExitButton.getGlobalBounds(); //Button Boundaries
	OptionsButton.setString("OPTIONS - 2");
	OptionsButton.setCharacterSize(60);
	OptionsButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (OptionsButton.getGlobalBounds().width / 2), (GAMEY / 5.0f) + 250.0f));
	OptionsButtonBox = OptionsButton.getGlobalBounds(); //Options Boundaries
	ResChange.setString("720p"); //Starts at 720p
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

	//buttons.push_back(PlayButtonBox);
//	buttons.push_back(ExitButtonBox);
	buttons.push_back(ResButtonBox);
	//buttons.push_back(OptionsButtonBox);
	//buttons.push_back(BackButtonBox);

	xMultiply = 1.0f; //Initial values for variables
	yMultiply = 1.0f;
	inOptions = false;

	sceneChangeDelay = 1.0f;

	attackKey = Keyboard::Q;
	healKey = Keyboard::W;
	rechargeKey = Keyboard::E;
	runKey = Keyboard::R;
	pauseKey = Keyboard::Num2;
}

//Updates the bounding boxes of buttons
void MenuScene::UpdateButtons()
{
	UpdateButton(PlayButtonBox);
	UpdateButton(ExitButtonBox);
	UpdateButton(ResButtonBox);
	UpdateButton(OptionsButtonBox);
	UpdateButton(BackButtonBox);
}

void GameScene::Load() {

	LoadTextures();

	//Loads the settings icon stuff
	SettingSprite.setTexture(gameScene.tm.getTex("Settings"));
	SettingSprite.setPosition(1200.0f, 630.0f);
	SettingSprite.setScale(0.3f, 0.3f);
	SettingBox = SettingSprite.getGlobalBounds();

	font = tm.getFont();

	descText.setFont(font);
	descText.setCharacterSize(15);
	descText.setString("");


	PauseText.setFont(font);
	ResText.setFont(font);
	ResChange.setFont(font);
	ResButton.setFont(font);
	BackButton.setFont(font);
	PauseText.setString("PAUSED");
	PauseText.setCharacterSize(100);
	PauseText.setPosition(sf::Vector2f(GAMEX / 2 - (PauseText.getGlobalBounds().width / 2), 200.0f));

	cout << Engine::getWindowSize().y << "\n";
	ResChange.setString(to_string(Engine::getWindowSize().y) + "p"); //Starts at 720p
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
	BackButton.setPosition(sf::Vector2f(GAMEX / 2.0f - (BackButton.getGlobalBounds().width / 2), GAMEY / 2.0f - (BackButton.getGlobalBounds().height / 2) + 100.0f));
	BackButtonBox = BackButton.getGlobalBounds();

	//Creates Player and adds components
	pl = make_shared<Entity>(); 
	//auto s = pl->addComponent<ShapeComponent>();
	//pl->addComponent<PlayerMovementComponent>();
	player = pl->addComponent<BasePlayerComponent>(100.0f, 20.0f, 10.0f, 0.0f, 10, &combatUI, &gameUI);
	am = pl->addComponent<AbilityManager>(3);
	inv = pl->addComponent<Inventory>(2, &gameUI);
	inv->Load();
	playerSprite = pl->addComponent<PlayerSprite>();
	playerSprite->load();
	//s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	//s->getShape().setFillColor(Color::Yellow);
	//s->getShape().setOrigin(Vector2f(-200.0f, -200.0f));
	ents.list.push_back(pl);

	//Populates the item database with pre defined items
	itemDB.PopulateDB();
	player->load();

	//Calls load function of the UIs
	combatUI.Load(player);
	gameUI.Load(10, player);

	textBox.setTexture(gameScene.tm.getTex("TextBox"));
	textBox.setScale(sf::Vector2f(0.7f, 0.5f));
	textBox.setPosition(sf::Vector2f((GAMEX / 2) - (textBox.getGlobalBounds().width / 2), 50.0f));
	//ui.list.push_back(textBox);
	screenText.setFont(font);
	screenText.setString("Welcome to Void Run!");
	screenText.setCharacterSize(30);
	screenText.setFillColor(Color(255, 255, 255, 255));
	screenText.setPosition((textBox.getPosition().x + textBox.getGlobalBounds().width / 2) - (screenText.getGlobalBounds().width / 2),
		(textBox.getPosition().y + textBox.getGlobalBounds().height /2)- (screenText.getGlobalBounds().height));

	//Some initializing stuff
	alphaUpdate = 255;
	sceneChangeDelay = 0.5f;
	isPaused = false;

	std::shared_ptr<StatRoom> statRoom = std::make_shared<StatRoom>(pl);

	//Calls ChangeRoom to start the game with a random room
	ChangeRoom();
	
	//UNCOMMENT TO SEE LOADING IN ACTION
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//setLoaded(true);
}

void GameScene::Update(const double& dt) {
	//Gets Mouse position in an int format
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);
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
		if (Keyboard::isKeyPressed(Keyboard::Num3) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
		/*	auto tempItem = itemDB.randomSpecialItem();
			UpdateTextBox(tempItem->description);
			inv->add(tempItem);*/
			scene_clock.restart();
			std::cout << "\nshould play attack\n";

		}

		//Removes an item from the inventory
		if (Keyboard::isKeyPressed(Keyboard::R) && inv->getItems().size() != 0 && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			inv->remove(0);
			scene_clock.restart();
		}

		//Adds random common item
		if (Keyboard::isKeyPressed(Keyboard::Num4) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();
			auto randItem = itemDB.randomCommonItem();
			UpdateTextBox(randItem->description);
			inv->add(randItem);
		}

		//Changes to a new room
		if (Keyboard::isKeyPressed(Keyboard::Space) && scene_delay.asSeconds() >= sceneChangeDelay)
		{
			scene_clock.restart();
			ChangeRoom();
		}

		if (Keyboard::isKeyPressed(Keyboard::Num2) && pause_delay.asSeconds() >= pauseDelay)
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
		//Update from base class
		Scene::Update(dt);
	}
	else
	{
		if (Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (ResButtonBox.contains(cursPos))
			{
				if (Engine::getWindowSize().y != 1080)
				{
					ResChange.setString("1080p");
					ChangeResolution(1920, 1080, GAMEX, GAMEY);
					UpdateButtons();
				}
				else
				{
					ResChange.setString("720p");
					ChangeResolution(1280, 720, GAMEX, GAMEY);
					UpdateButtons();
				}
			}
			if (BackButtonBox.contains(cursPos))
			{
				isPaused = false;
			}
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (Engine::getWindowSize().y != 1080)
			{
				ResChange.setString("1080p");
				ChangeResolution(1920, 1080, GAMEX, GAMEY);
				UpdateButtons();
			}
			else
			{
				ResChange.setString("720p");
				ChangeResolution(1280, 720, GAMEX, GAMEY);
				UpdateButtons();
			}
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Num2) && pause_delay.asSeconds() >= pauseDelay)
		{
			pauseClock.restart();
			isPaused = false;
		}

		if (BackButtonBox.contains(cursPos))
		{
			BackButton.setFillColor(green);
		}
		else
		{
			BackButton.setFillColor(white);
		}
		if (ResButtonBox.contains(cursPos))
		{
			ResButton.setFillColor(green);
		}
		else
		{
			ResButton.setFillColor(white);
		}
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
		Renderer::queue(&screenText);
		Renderer::queue(&SettingSprite);
		Scene::Render();
		Renderer::queue(&descRect);
		Renderer::queue(&descText);
	}
	else // if paused
	{
		Renderer::queue(&PauseText);
		Renderer::queue(&ResButton);
		Renderer::queue(&ResChange);
		Renderer::queue(&ResText);
		Renderer::queue(&BackButton);
	}
}

//Does all the things needed when we change rooms
void GameScene::ChangeRoom() {
	player->expGained = false;

	if(ents.list.size() > 1)
	{
		ents.list[ents.list.size() - 1]->setForDelete();
	}
	//srand to ensure the random number is actually random
	srand(time(0));
	int roomType = rand() % 2;
	if (roomType == 0) //Combat Room
	{
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
		UpdateTextBox("Entered Combat Room");
	}
	else if(roomType == 1) //Treasure Room
	{
		std::shared_ptr<TreasureRoom> newRoom = make_shared<TreasureRoom>(pl);
		newRoom->Load();
		rooms.push_back(newRoom);
		currentRoom = newRoom;
		UpdateTextBox("Entered Treasure Room");
	}
	
}

//Updates the bounding boxes of all Buttons
void GameScene::UpdateButtons()
{
	UpdateButton(ResButtonBox);
	UpdateButton(BackButtonBox);
	UpdateButton(SettingBox);
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
	tm.loadFont("mandalore.ttf");

	tm.loadTexture("Settings", "Icons/Settings.png");
	tm.loadTexture("TextBox", "Sprites/TextBox.png");
	tm.loadTexture("Attack", "Icons/Attack.png");
	tm.loadTexture("Heal", "Icons/Heal.png");
	tm.loadTexture("Recharge", "Icons/Recharge.png");
	tm.loadTexture("Run", "Icons/Run.png");
	tm.loadTexture("Charge", "Icons/Charge.png");
	tm.loadTexture("StatUp", "Icons/Arrow.png");
	tm.loadTexture("Player", "Sprites/Player.png");
	tm.loadTexture("Background1", "Sprites/BGspace1.jpg");
	tm.loadTexture("LaserBurst", "Icons/LaserBurst.png");
	tm.loadTexture("ChargedAttack", "Icons/ChargedAttack.png");
	tm.loadTexture("Curse", "Icons/Curse.png");
	tm.loadTexture("Dodge", "Icons/Dodge.png");
	tm.loadTexture("DoubleSlice", "Icons/DoubleSlice.png");
	tm.loadTexture("Enrage", "Icons/Enrage.png");
	tm.loadTexture("Excruciate", "Icons/Excruciate.png");
	tm.loadTexture("Bullseye", "Icons/Bullseye.png");
	tm.loadTexture("OverloadWeapon", "Icons/OverloadWeapon.png");
	tm.loadTexture("PainShare", "Icons/PainShare.png");
	tm.loadTexture("Regeneration", "Icons/Regeneration.png");
	tm.loadTexture("SuicideCharge", "Icons/SuicideCharge.png");
	tm.loadTexture("PlayerAttack", "Sprites/SpriteSheets/PlayerAttack.png");
	tm.loadTexture("PlayerHit", "Sprites/SpriteSheets/PlayerHit.png");
	tm.loadTexture("PlayerDie", "Sprites/SpriteSheets/PlayerDie.png");
	tm.loadTexture("Alien1Attack", "Sprites/SpriteSheets/Alien1Attack.png");
	tm.loadTexture("Alien1Hit", "Sprites/SpriteSheets/Alien1Hit.png");
	tm.loadTexture("Alien1Die", "Sprites/SpriteSheets/Alien1Die.png");
	tm.loadTexture("Alien2Attack", "Sprites/SpriteSheets/Alien2Attack.png");
	tm.loadTexture("Alien2Hit", "Sprites/SpriteSheets/Alien2Hit.png");
	tm.loadTexture("Alien2Die", "Sprites/SpriteSheets/Alien2Die.png");
	tm.loadTexture("Alien3Attack", "Sprites/SpriteSheets/Alien3Attack.png");
	tm.loadTexture("Alien3Hit", "Sprites/SpriteSheets/Alien3Hit.png");
	tm.loadTexture("Alien3Die", "Sprites/SpriteSheets/Alien3Die.png");
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