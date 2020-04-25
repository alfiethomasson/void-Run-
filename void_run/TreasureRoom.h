#pragma once
#include <iostream>
#include "Room.h"
#include "cmp_inventory.h"
#include "ItemDB.h"

class TreasureRoom : public Room {
private:
	std::shared_ptr<Inventory> inv;
	ItemDB itemDB;
public:
	TreasureRoom(std::shared_ptr<Entity> p, ItemDB &iDB);
	~TreasureRoom() override = default;

	void Update(const double& dt) override;
	void Render() override;
	void Load() override;

};