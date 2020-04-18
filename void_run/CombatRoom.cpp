#include "CombatRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"
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

void CombatRoom::Update(const double& dt) {

	turn_delay = turn_clock.getElapsedTime();

//	gameScene.combatUI.Update(dt);

	if (playerTurn)
	{
		if (!p->isTurn && turn_delay.asSeconds() >= turnDelayValue)
		{
			p->isTurn = true;
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

	playerHP.setString(std::to_string(p->getCurrentHealth()));
	enemyHP.setString(std::to_string(enemy->getCurrentHealth()));
	experienceCounter.setString(std::to_string(p->getExperience()));

	Room::Update(dt);
}

void CombatRoom::Render() {
	gameScene.combatUI.Render();
	Renderer::queue(&playerHP);
	Renderer::queue(&enemyHP);
	Renderer::queue(&experienceCounter);

	Room::Render();
}

void CombatRoom::Load() {
	std::cout << "Entered a Combat Room!\n";

	//Creates Enemy and adds components
	auto enemy1 = make_shared<Entity>();
	auto s = enemy1->addComponent<ShapeComponent>();

	srand(time(0));
	int enemyType = rand() % 3; //Random number from 0-2. 0 is easy, 1 is medium, 2 is tough.
	if (enemyType == 0)
	{	enemy = enemy1->addComponent<EasyEnemy>(50, 10, 5, 5, (rand() % 3));} //Random number from 0-2. 0 is Debuff, 1 is Enrage, 2 is Double-Slice.
	else if (enemyType == 1)
	{	enemy = enemy1->addComponent<MediumEnemy>(180, 15, 15, 15, (rand() % 4));} //Random number from 0-3. 0 is Pain Share, 1 is Regeneration, 2 is Orbital Attack, 3 is Curse.
	else if (enemyType == 2)
	{	enemy = enemy1->addComponent<ToughEnemy>(250, 20, 20, 20, (rand() % 3));} //Random number from 0-2. 0 is Excruciate, 1 is Charged Shot, 2 is Suicide Shot.

	s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(Vector2f(-500.0f, -200.0f));

	ents.list.push_back(enemy1);

	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];
	enemy->updateEnemy(p);

	p->updateEnemy(enemy);

	playerTurn = true;
	p->isFinishedTurn = false;
	enemy->isTurn = false;
	enemy->isFinishedTurn = false;

	if (!font.loadFromFile("res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}
	playerHP.setFont(font);
	enemyHP.setFont(font);
	experienceCounter.setFont(font);
	playerHP.setCharacterSize(100);
	playerHP.setPosition(sf::Vector2f(GAMEX / 4 - (playerHP.getGlobalBounds().width / 2), GAMEY / 5.0f));
	playerHP.setFillColor(sf::Color::Red);
	enemyHP.setCharacterSize(100);
	enemyHP.setPosition(sf::Vector2f((GAMEX / 4 * 3) - (enemyHP.getGlobalBounds().width / 2), GAMEY / 5.0f));
	enemyHP.setFillColor(sf::Color::Red);
	experienceCounter.setCharacterSize(101);
	experienceCounter.setPosition(sf::Vector2f(GAMEX / 4 - (experienceCounter.getGlobalBounds().width / 4), GAMEY / 5.0f));
	experienceCounter.setFillColor(sf::Color::Yellow);

	turnDelayValue = 1.0f;

	Room::Load();
}
//CombatRoom::CombatRoom(Entity* p) : Room() { player = p; };