#pragma once
#include "SpecialAbility.h"
#include "cmp_sprites.h"

class LaserBurst : public SpecialAbility {
public:
	void update(double dt);
	void load();
	void doEffect() override;
	void checkKey() override;
};

class OverloadWeapon : public SpecialAbility
{
private:
	int amount;
public:
	void update(double dt);
	void load();
	void doEffect() override;
	void turnStart() override;
	void checkKey() override;
	void Reset() override;
};

class UncannySpeed : public SpecialAbility
{
private:
	int amount;
public:
	void update(double dt);
	void load();
	void doEffect() override;
	void turnStart() override;
	void checkKey() override;
	void Reset() override;
};

class PrimalInstincts : public SpecialAbility
{
private:
	int amount;
public:
	void update(double dt);
	void load();
	void doEffect() override;
	void turnStart() override;
	void checkKey() override;
	void Reset() override;
};

class DeadlyFumes : public SpecialAbility
{
private:
	bool used;
	std::shared_ptr<SpriteComponent> enemySprite;
public:
	void update(double dt);
	void load();
	void doEffect() override;
	void turnStart() override;
	void checkKey() override;
	void Reset() override;
};

class MagmaGrenade : public SpecialAbility
{
private:
	bool used;
	std::shared_ptr<SpriteComponent> enemySprite;
public:
	void update(double dt);
	void load();
	void doEffect() override;
	void turnStart() override;
	void checkKey() override;
	void Reset() override;
};