#include "SpecialAbility.h"

//SpecialAbility::SpecialAbility(Entity* p)
//	: Component(p) {}

void SpecialAbility::update(double dt)
{

}

void SpecialAbility::updatePlayer(std::shared_ptr<BasePlayerComponent> pl)
{
	player = pl;
}
