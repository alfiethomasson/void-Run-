#pragma once
#include "ecm.h"
#include "cmp_player.h"

class BasePlayerComponent;

class SpecialItem : public Component
{
protected:
	std::shared_ptr<BasePlayerComponent> player;
public:

	explicit SpecialItem(Entity* p);
	SpecialItem() = delete;

	void update(double dt) override;
	void render() override {}
	virtual void doEffect() {}
	void load();

};