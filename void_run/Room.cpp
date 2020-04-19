#include "Room.h"
#include "engine.h"
#include "Game.h"

using namespace sf;
using namespace std;

void Room::Update(const double& dt) {
	if (!isPaused)
	{
		//Changes scene to Menu ****TO REMOVE****
		if (Keyboard::isKeyPressed(Keyboard::Tab)) {
			Engine::ChangeScene(&menuScene);
		}
	}
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