/*#include "Ghost.h"
#include "Game.h"
#include <iostream>
using namespace sf;

void Ghost::Update(double dt) {
	//Move in four directions based on keys
	//...
	static Clock clock1;

	elapsed_time += clock1.restart().asSeconds();

	if (elapsed_time >= deltatime)
	{
		cout << "should be random";
		auto dir = rand() % 4;
		if (dir == 0)
		{
			//north
			cout << "north";
			directionH = 0;
			directionV = 1;
		}
		else if (dir == 1)
		{
			//east
			cout << "east";
			directionH = 1;
			directionV = 0;
		}
		else if (dir == 2)
		{
			//south
			cout << "south";
			directionH = 0;
			directionV = -1;
		}
		else if (dir == 3)
		{
			//west
			cout << "west";
			directionH = -1;
			directionV = 0;
		}

		elapsed_time -= deltatime;
	}

	move(Vector2f(directionH * _speed * dt, directionV * _speed * dt));
	cout << "ghost pos = " << getPosition().x;


	Entity::Update(dt);
};

Ghost::Ghost()
	: _speed(100.0f), deltatime(2), directionH(0), directionV(0), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Red);
	_shape->setOrigin(Vector2f(25.f, 25.f));
};

void Ghost::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
};*/