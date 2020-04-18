#pragma once
#include "SpecialAbility.h"

class LaserBurst : public SpecialAbility {
protected:

public:
	//explicit LaserBurst(Entity* p);
	//LaserBurst() = delete;

	void update(double dt);
	void load();
	void doEffect() override;

};

class OverloadWeapon : public SpecialAbility
{
public:
	//explicit OverloadWeapon(Entity* p);
	//OverloadWeapon() = delete;

	void update(double dt);
	void load();
	void doEffect() override;
};