#pragma once
#include "SpecialAbility.h"

class LaserBurst : public SpecialAbility {
public:
	LaserBurst();
	~LaserBurst() = default;
	void update(double dt);
	void load();
	void doEffect() override;

};

class OverloadWeapon : public SpecialAbility
{
public:
	void update(double dt);
	void load();
	void doEffect() override;
};

class UncannySpeed : public SpecialAbility
{
public:
	void update(double dt);
	void load();
	void doEffect() override;
};

class PrimalInstincts : public SpecialAbility
{
public:
	void update(double dt);
	void load();
	void doEffect() override;
};

class DeadlyFumes : public SpecialAbility
{
public:
	void update(double dt);
	void load();
	void doEffect() override;
};

class MagmaGrenade : public SpecialAbility
{
public:
	void update(double dt);
	void load();
	void doEffect() override;
};