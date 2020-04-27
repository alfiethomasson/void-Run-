#include "CombatRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_player.h"
#include "AlienSprites.h"
#include "enemy_easy.h"
#include "enemy_medium.h"
#include "enemy_tough.h"
#include "enemy_boss.h"
#include "VoidRun.h"

bool playerTurn;

sf::Time turn_delay;
sf::Clock turn_clock;
float turnDelayValue;

CombatRoom::CombatRoom(std::shared_ptr <Entity> p, CombatUI *combUI)
	: combatUI{ *combUI }, Room(p) {};

void CombatRoom::Update(const double& dt, sf::Vector2f cursPos) {

	turn_delay = turn_clock.getElapsedTime(); //Delay so that things don't happen once per frame
	enemy->update(dt); //Update the enemy
	combatUI.Update(dt, cursPos); //Update the UK

	if (enemy->getCurrentHealth() != 0) //If the enemy is alive...
	{
		if (playerTurn) //...and it's the player's turn...
		{
			if (!p->isTurn && turn_delay.asSeconds() >= turnDelayValue) //Delay, then start their turn
			{
				p->StartTurn();
			}
			if (p->isFinishedTurn) //...if they finished their turn, we stop it being their turn
			{
				turn_clock.restart();
				playerTurn = false;
				p->isTurn = false;
				p->isFinishedTurn = false;
			}
		}
		else //...but it's not the player's turn...
		{
			if (!enemy->isTurn && turn_delay.asSeconds() >= turnDelayValue) //Make it the enemy's turn!
			{
				enemy->isTurn = true;
			}
			if (enemy->isFinishedTurn) //...and the enemy's finished their turn...
			{
				turn_clock.restart(); //Make it the player's turn
				playerTurn = true;
				enemy->isTurn = false;
				enemy->isFinishedTurn = false;
			}
		}
	}
	else if (bossFightStarted == true) //If the boss fight has been started, and the enemy is not alive........
	{
		gameScene.gameMusic.stop();
		Engine::ChangeScene(&victoryScene); //...they win the game!
	}
	else //If the enemy is not alive
	{
		if (!gameScene.gameUI.updateStatOptions()) //Once they pick stats, it goes away
		{
			active = false;
		}
		p->expGet(); //Gain EXP
	}

	Room::Update(dt, cursPos); //Update the room
}

void CombatRoom::Render() { //Render the individual parts of the UI, enemy, room, etc
	combatUI.Render();
	Renderer::queue(&experienceCounter);
	enemy->render();

	Room::Render();
}

void CombatRoom::Load() {
	std::cout << "Entered a Combat Room!\n";
	Room::Load(); 

	bossFightStarted = false; //bossFightStarted is false - Only becomes true when fighting the boss.

	//Creates Enemy and adds components
	auto enemy1 = make_shared<Entity>();
	srand(time(0));
<<<<<<< Updated upstream
	int enemyType = rand() % 10; //Random number from 0-2. 0 is easy, 1 is medium, 2 is tough.
	if(p->level >= 5)
=======
	int enemyType = rand() % 10; //Random number from 0-9. 0-5 is easy, 6-8 is medium, 9 is tough.

	if(p->level >= 5) //If the player is Level 5, then enemyType becomes 10: Spawning the boss.
>>>>>>> Stashed changes
	{
		enemyType = 10;
	}

	if (enemyType < 6) //6/9 chance of spawning a weak enemy
	{
		enemy = enemy1->addComponent<EasyEnemy>(50, 10, 5, 5, (rand() % 3)); //Random value passed in to determine random ability
		auto sm = enemy1->addComponent<AlienSprite1>();
		sm->load();
	}
	else if (enemyType >= 6 && enemyType < 9) //2/9 chance of spawning a medium enemy
	{
		enemy = enemy1->addComponent<MediumEnemy>(180, 15, 15, 15, (rand() % 4));
		auto sm = enemy1->addComponent<AlienSprite3>();
		sm->load();
	} //Random number from 0-3. 0 is Pain Share, 1 is Regeneration, 2 is Orbital Attack, 3 is Curse.
	else if (enemyType == 9)//1/9 chance of spawning a tough enemy
	{
		enemy = enemy1->addComponent<ToughEnemy>(250, 20, 20, 20, (rand() % 3));
		auto sm = enemy1->addComponent<AlienSprite2>();
		sm->load();
	} //Random number from 0-2. 0 is Excruciate, 1 is Charged Shot, 2 is Suicide Shot.
	else if (enemyType == 10) //If they're level 5, this became 10, so they will fight the boss
	{
		bossFightStarted = true; //Boolean turns true so that game knows the player is on the verge of winning
		enemy = enemy1->addComponent<BossEnemy>(500, 30, 30, 0, 0);
		auto sm = enemy1->addComponent<BossSprite>();
		sm->load();
		gameScene.gameMusic.stop();
		gameScene.gameMusic.openFromFile("res/Sounds/Music/BossMusic.wav");
		gameScene.gameMusic.setVolume(musicVolume);
		gameScene.gameMusic.setLoop(true);
		gameScene.gameMusic.play();
	}
	enemy->load();

	ents.list.push_back(enemy1);

	auto a = player->GetCompatibleComponent<BasePlayerComponent>(); //Get player
	p = a[0];
	enemy->updateEnemy(p);

	p->updateEnemy(enemy);

	playerTurn = true; //Booleans used to check whose turn it is
	p->isFinishedTurn = false;
	enemy->isTurn = false;
	enemy->isFinishedTurn = false;

	experienceCounter.setFont(Engine::tm.getFont()); //Experience counter visible at all times
	experienceCounter.setCharacterSize(100);
	experienceCounter.setPosition(sf::Vector2f(1200.0f, 0.0f));
	experienceCounter.setFillColor(sf::Color::Yellow);

	turnDelayValue = 2.0f;
}

//CombatRoom::CombatRoom(Entity* p) : Room() { player = p; };