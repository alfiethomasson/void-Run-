#include "cmp_entityinfo.h"

int PlayerInfo::getStrength() {
	return _strength;
}

int PlayerInfo::getHealth() {
	return _health;
}

int PlayerInfo::getDexterity() {
	return _dexterity;
}

void PlayerInfo::setStrength(int strength) {
	_strength = strength;
}

void PlayerInfo::setHealth(int health) {
	_health = health;
}

void PlayerInfo::setDexterity(int dexterity)
{
	_dexterity = dexterity;
}

PlayerInfo::PlayerInfo(Entity* e) : Component(e) {};