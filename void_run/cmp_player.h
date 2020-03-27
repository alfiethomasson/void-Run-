#pragma once
#include "ecm.h"

class BasePlayerComponent : public Component {
protected:
	float playerDamage;
	float playerHealQuantity;
	std::shared_ptr<Entity> currentEnemy;
public:
	bool isTurn;
	bool isFinishedTurn;
	explicit BasePlayerComponent(Entity* p);
	BasePlayerComponent() = delete;

	void render() override {}
	void update(double dt) override;

	void updateEnemy(std::shared_ptr<Entity> e);

	void attack(float damage);
	void heal(float heal);
	void EndTurn();
};