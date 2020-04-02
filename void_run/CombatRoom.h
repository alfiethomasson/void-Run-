#pragma once
#include <iostream>
#include "Room.h"
#include "cmp_player.h"

class CombatRoom : public Room {
protected:
	std::shared_ptr<Entity> player;
public:
	CombatRoom(std::shared_ptr<Entity> p) : player(p) {};
	~CombatRoom() override = default;
	//explicit CombatRoom(Entity* p);
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad();
	
}; 