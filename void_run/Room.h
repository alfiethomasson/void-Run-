#pragma once
#include "ecm.h"
#include "cmp_player.h"

class Room {
protected:
	EntityManager ents;
public:
	Room() = default;
	virtual ~Room() = default;

	virtual void Update(const double& dt);
	virtual void Render() {};
	virtual void Load();
	std::vector<std::shared_ptr<Entity>> GetEnts();


};