#include "Room.h"
#include "engine.h"
#include "Game.h"

using namespace sf;
using namespace std;

void Room::Update(const double& dt, sf::Vector2f cursPos) { //Empty update loop for future use

}

void Room::Load() //Load function
{
	active = true; //Make room active
	std::cout << "Entered a Treasure Room!\n";
	auto a = player->GetCompatibleComponent<BasePlayerComponent>(); //Get the player
	p = a[0];

	p->isTurn = false; //Not the player's turn
}

std::vector<std::shared_ptr<Entity>> Room::GetEnts() //Get Ents list
{
	return ents.list;
}

void Room::StatUp() //Stat up room for future use
{

}

bool Room::isActive() //Getter for the room's activity
{
	return active;
}

void Room::setInactive() //Setter for the room's activity
{
	active = false;
}