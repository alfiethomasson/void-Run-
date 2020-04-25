#include "TreasureRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"

TreasureRoom::TreasureRoom(std::shared_ptr <Entity> p, ItemDB &iDB)
	: itemDB{ iDB }, Room(p) {};

void TreasureRoom::Update(const double& dt) {
	inv->add(itemDB.randomCommonItem(), true);
	Room::Update(dt);
	setInactive();
}

void TreasureRoom::Render() {

}

void TreasureRoom::Load() {
	std::cout << "Entered a Treasure Room!\n";
	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];

	auto i = player->GetCompatibleComponent<Inventory>();
	inv = i[0];

	p->isTurn = false;
}
