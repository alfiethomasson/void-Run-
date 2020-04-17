#include "cmp_special.h"

SpecialItem::SpecialItem(Entity* p)
	: Component(p) {}

void SpecialItem::update(double dt)
{

}

void SpecialItem::load()
{
	auto pl = _parent->GetCompatibleComponent<BasePlayerComponent>();
	player = pl[0];
}
