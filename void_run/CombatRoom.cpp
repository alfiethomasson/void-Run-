#include "CombatRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"
#include "cmp_enemy.h"

#define GAMEX 1280
#define GAMEY 720

std::shared_ptr<BaseEnemyComponent> enemy;

bool playerTurn;

void CombatRoom::Update(const double& dt) {

	if (playerTurn)
	{
		if (!p->isTurn)
		{
			p->isTurn = true;
		}
		if (p->isFinishedTurn)
		{
			sf::sleep(sf::seconds(1.0));
			playerTurn = false;
			p->isTurn = false;
			enemy->isTurn = true;
			p->isFinishedTurn = false;
		}
	}
	else
	{
		if (!enemy->isTurn)
		{
			enemy->isTurn = true;
		}
		if (enemy->isFinishedTurn)
		{
			sf::sleep(sf::seconds(1.0));
			playerTurn = true;
			enemy->isTurn = false;
			p->isTurn = true;
			enemy->isFinishedTurn = false;
		}
	}

	playerHP.setString(std::to_string(p->getCurrentHealth()));
	enemyHP.setString(std::to_string(enemy->getCurrentHealth()));
	Renderer::queue(&playerHP);
	Renderer::queue(&enemyHP);

	Room::Update(dt);
}

void CombatRoom::Render() {
	Renderer::queue(&playerHP);
	Renderer::queue(&enemyHP);

	Room::Render();
}

void CombatRoom::Load() {
	std::cout << "Entered a Combat Room!\n";

	//Creates Enemy and adds components
	auto enemy1 = make_shared<Entity>();
	auto s = enemy1->addComponent<ShapeComponent>();
	enemy = enemy1->addComponent<BaseEnemyComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(Vector2f(-500.0f, -200.0f));
	enemy->setMaxHealth(50);
	enemy->setDexterity(10);
	enemy->setStrength(5);
	ents.list.push_back(enemy1);

	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];

	playerTurn = true;
	p->isFinishedTurn = false;
	enemy->isTurn = false;

	//if (!font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/void-Run-/res/Fonts/mandalore.ttf"))
	if (!font.loadFromFile("C:/Users/Flat 48/Documents/GitHub/void-Run-/res/Fonts/mandalore.ttf"))
	{
		cout << "failed to load font";
	}
	playerHP.setFont(font);
	enemyHP.setFont(font);
	playerHP.setCharacterSize(100);
	playerHP.setPosition(sf::Vector2f(GAMEX / 2.0f - (playerHP.getGlobalBounds().width / 2), GAMEY / 5.0f));
	playerHP.setFillColor(sf::Color::Red);
	enemyHP.setCharacterSize(100);
	enemyHP.setPosition(sf::Vector2f(GAMEX / 2.0f - (enemyHP.getGlobalBounds().width / 2), GAMEY / 5.0f));
	enemyHP.setFillColor(sf::Color::Red);
}
//CombatRoom::CombatRoom(Entity* p) : Room() { player = p; };