#include "cmp_entityinfo.h"

int EntityInfo::getStrength() {
	return _strength;
}

int EntityInfo::getHealth() {
	return _health;
}

int EntityInfo::getDexterity() {
	return _dexterity;
}

void EntityInfo::setStrength(int strength) {
	_strength = strength;
}

void EntityInfo::setHealth(int health) {
	_health = health;
}

void EntityInfo::setDexterity(int dexterity)
{
	_dexterity = dexterity;
}

EntityInfo::EntityInfo(Entity* e) : Component(e) {};