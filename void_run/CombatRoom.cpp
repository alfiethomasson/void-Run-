#include "CombatRoom.h"
#include "Game.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"
#include "cmp_enemy.h"

std::shared_ptr<BaseEnemyComponent> enemy;

bool playerTurn = true;

void CombatRoom::Update(const double& dt) {
	//std::cout << "HEY";
	Room::Update(dt);
}

void CombatRoom::Render() {

}

void CombatRoom::Load() {
	std::cout << "Entered a Combat Room!\n";
	//Creates Enemy and adds components
	auto enemy1 = make_shared<Entity>();
	auto s = enemy1->addComponent<ShapeComponent>();
	auto i = enemy1->addComponent<EntityInfo>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(75.0f, 200.0f));
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(Vector2f(-500.0f, -200.0f));
	i->setStrength(10);
	i->setHealth(50);
	i->setDexterity(10);

	ents.list.push_back(enemy1);

	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];
	
	playerTurn = true;
	
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
			enemy->isFinishedTurn = false;
		}
	}
	
	
}
//CombatRoom::CombatRoom(Entity* p) : Room() { player = p; };