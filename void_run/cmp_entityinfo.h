#pragma once
#include "ecm.h"

class EntityInfo : public Component {
protected:
	int _strength;
	int _health;
	int _dexterity;

public:
	EntityInfo() = delete;
	explicit EntityInfo(Entity* e);

	void render() override {}
	void update(double dt) override;

	int getStrength();
	int getHealth();
	int getDexterity();

	void setStrength(int strength);
	void setHealth(int health);
	void setDexterity(int dexterity);

	void takeDamage(int dmgRecieved);
};