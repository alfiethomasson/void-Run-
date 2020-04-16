#include "cmp_actor_movement.h"
#include <LevelSystem.h>

using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	//if (validMove(pp)) {
		_parent->setPosition(pp);
	//}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }

 PlayerMovementComponent::PlayerMovementComponent(Entity *p) : ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {
	int xdir = 0, ydir = 0;

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		move(Vector2f(0, -_speed * dt));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		move(Vector2f(0, _speed * dt));	
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		move(Vector2f(-_speed * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		move(Vector2f(_speed * dt, 0));
	}

	ActorMovementComponent::update(dt);
}

void PlayerMovementComponent::render() {
	ActorMovementComponent::render();
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
	_state = ROAMING;
	_speed = 100.0f;
//	_direction = Vector2f(directions[rand() % 4]);
}

void EnemyAIComponent::update(double dt) { }

void EnemyAIComponent::render() {
//	ActorMovementComponent::render();
}