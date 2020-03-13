/*#include "Player.h"
#include "Game.h"
#include <iostream>
using namespace sf;

void Player::Update(double dt) {
	//Move in four directions based on keys
	//...

	float directionV = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		//	std::cout << "Up pressed";
		directionV--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		directionV++;
	}

	float directionH = 0.0f;
	if (Keyboard::isKeyPressed(controls[2])) {
		//std::cout << "Up pressed";
		directionH--;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		directionH++;
	}

	move(Vector2f(directionH * _speed * dt, directionV * _speed * dt));


	Entity::Update(dt);
};

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
};

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
};*/