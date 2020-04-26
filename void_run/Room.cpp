#include "Room.h"
#include "engine.h"
#include "Game.h"

using namespace sf;
using namespace std;

void Room::Update(const double& dt, sf::Vector2f cursPos) {

}

void Room::Load()
{
	active = true;
	std::cout << "Entered a Treasure Room!\n";
	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];

	p->isTurn = false;
}

std::vector<std::shared_ptr<Entity>> Room::GetEnts()
{
	return ents.list;
}

void Room::StatUp()
{

}

bool Room::isActive()
{
	return active;
}

void Room::setInactive()
{
	active = false;
}