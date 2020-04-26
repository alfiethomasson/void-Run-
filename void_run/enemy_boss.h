#pragma once
#include <iostream>
#include "ecm.h"
#include "cmp_enemy.h"

class BossEnemy : public BaseEnemyComponent {
protected:

public:
	BossEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove);
	void render() override {}
	void update(double dt) override;
	void load() override {}
};	