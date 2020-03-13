#pragma once
#include "ecm.h"

class PlayerInfo : public Component {
protected:
	int _strength;
	int _health;
	int _dexterity;

public:
	PlayerInfo() = delete;
	explicit PlayerInfo(Entity* e);

	int getStrength();
	int getHealth();
	int getDexterity();

	//template<typename T, typename... Targs>
	void setStrength(int strength);

	void setHealth(int health);

	void setDexterity(int dexterity);

};