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
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			cout << "GAME PAUSED\n";

			isPaused = true;
		}
	}
}

void Room::Load()
{
	
}

std::vector<std::shared_ptr<Entity>> Room::GetEnts()
{
	return ents.list;
}
