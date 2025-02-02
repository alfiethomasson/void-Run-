#pragma once
#include "ecm.h"
#include "cmp_player.h"

class Room {
protected:
	EntityManager ents;
	std::shared_ptr<Entity> player;
	std::shared_ptr<BasePlayerComponent> p;
	bool active;
public:
	Room(std::shared_ptr<Entity> p) : player(p) {};
	virtual ~Room() = default;

	virtual void Update(const double& dt, sf::Vector2f cursPos);
	virtual void Render() {};
	virtual void Load();
	std::vector<std::shared_ptr<Entity>> GetEnts();
	
	bool isActive();
	void setInactive();
	void StatUp();
};