#include "CombatRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "AlienSprites.h"
#include "enemy_easy.h"
#include "enemy_medium.h"
#include "enemy_tough.h"

#define GAMEX 1280
#define GAMEY 720

std::shared_ptr<BaseEnemyComponent> enemy;

bool playerTurn;

sf::Time turn_delay;
sf::Clock turn_clock;
float turnDelayValue;

CombatRoom::CombatRoom(std::shared_ptr <Entity> p)
	: Room(p) {};

void CombatRoom::Update(const double& dt) {

	turn_delay = turn_clock.getElapsedTime();
	enemy->update(dt);

	if (enemy->getCurrentHealth() != 0)
	{
		if (playerTurn)
		{
			if (!p->isTurn && turn_delay.asSeconds() >= turnDelayValue)
			{
				p->isTurn = true;
				p->gainAP(2);
			}
			if (p->isFinishedTurn)
			{
				turn_clock.restart();
				playerTurn = false;
				p->isTurn = false;
				//enemy->isTurn = true;
				p->isFinishedTurn = false;
			}
		}
		else
		{
			if (!enemy->isTurn && turn_delay.asSeconds() >= turnDelayValue)
			{
				enemy->isTurn = true;
			}
			if (enemy->isFinishedTurn)
			{
				turn_clock.restart();
				playerTurn = true;
				enemy->isTurn = false;
				//p->isTurn = true;
				enemy->isFinishedTurn = false;
			}
		}
	}
	else
	{
		if (!gameScene.gameUI.updateStatOptions())
		{
			active = false;
		}

	}

	Room::Update(dt);
}

void CombatRoom::Render() {
	gameScene.combatUI.Render();
	Renderer::queue(&experienceCounter);
	enemy->render();

	Room::Render();
}

void CombatRoom::Load() {
	std::cout << "Entered a Combat Room!\n";
	Room::Load();

	//Creates Enemy and adds components
	auto enemy1 = make_shared<Entity>();
	//auto s = enemy1->addComponent<ShapeComponent>();
	srand(time(0));
	int enemyType = rand() % 5; //Random number from 0-2. 0 is easy, 1 is medium, 2 is tough.
	enemyType = 0;
	if (enemyType < 3)
	{
		enemy = enemy1->addComponent<EasyEnemy>(50, 10, 5, 5, (rand() % 3)); //Random number from 0-2. 0 is Debuff, 1 is Enrage, 2 is Double-Slice.
		auto sm = enemy1->addComponent<AlienSprite1>();
		sm->load();
	}
	else if (enemyType == 3)
	{	enemy = enemy1->addComponent<MediumEnemy>(180, 15, 15, 15, (rand() % 4));
		auto sm = enemy1->addComponent<AlienSprite3>();
		sm->load();
	} //Random number from 0-3. 0 is Pain Share, 1 is Regeneration, 2 is Orbital Attack, 3 is Curse.
	else if (enemyType == 4)
	{	enemy = enemy1->addComponent<ToughEnemy>(250, 20, 20, 20, (rand() % 3));
		auto sm = enemy1->addComponent<AlienSprite2>();
		sm->load();
	} //Random number from 0-2. 0 is Excruciate, 1 is Charged Shot, 2 is Suicide Shot.
	enemy->load();

	ents.list.push_back(enemy1);

	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];
	enemy->updateEnemy(p);

	p->updateEnemy(enemy);

	playerTurn = true;
	p->isFinishedTurn = false;
	enemy->isTurn = false;
	enemy->isFinishedTurn = false;

	experienceCounter.setFont(Engine::tm.getFont());
	experienceCounter.setCharacterSize(100);
	experienceCounter.setPosition(sf::Vector2f(1200.0f, 0.0f));
	experienceCounter.setFillColor(sf::Color::Yellow);

	turnDelayValue = 2.0f;
}

//CombatRoom::CombatRoom(Entity* p) : Room() { player = p; };