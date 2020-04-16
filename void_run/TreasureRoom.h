#pragma once
#include <iostream>
#include "Room.h"

class TreasureRoom : public Room {
private:
	std::shared_ptr<Entity> player;
	std::shared_ptr<BasePlayerComponent> p;
public:
	TreasureRoom(std::shared_ptr<Entity> p) : player(p) {};
	~TreasureRoom() override = default;

	void Update(const double& dt) override;
	void Render() override;
	void Load() override;

};