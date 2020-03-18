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

void EntityInfo::takeDamage(int dmgRecieved)
{
	_health -= dmgRecieved;
}

void EntityInfo::update(double dt) {
	//int curHealth = getHealth();
	//std::cout << curHealth << "\n";
}

EntityInfo::EntityInfo(Entity* e) : Component(e) {};