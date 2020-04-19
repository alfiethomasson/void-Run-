#include "TreasureRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"

TreasureRoom::TreasureRoom(std::shared_ptr <Entity> p)
	: Room(p) {};

void TreasureRoom::Update(const double& dt) {
	Room::Update(dt);
}

void TreasureRoom::Render() {

}

void TreasureRoom::Load() {
	std::cout << "Entered a Treasure Room!\n";
	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];

	p->isTurn = false;
}
