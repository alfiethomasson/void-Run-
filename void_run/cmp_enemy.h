#pragma once
#include "ecm.h"

class BaseEnemyComponent : public Component {
protected:
	float enemyDamage;
	std::shared_ptr<Entity> currentEnemy;
public:
	bool isTurn;
	bool isFinishedTurn;
	explicit BaseEnemyComponent(Entity* p);
	BaseEnemyComponent() = delete;

	void render() override {}
	void update(double dt) override;

	void updateEnemy(std::shared_ptr<Entity> e);

	void attackEnemy(float damage);
	void EndTurn();
};