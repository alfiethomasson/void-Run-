#include "TreasureRoom.h"
#include "Game.h"

void TreasureRoom::Update(const double& dt) {
	Room::Update(dt);
}

void TreasureRoom::Render() {

}

void TreasureRoom::Load() {
	std::cout << "Entered a Treasure Room!\n";
}
