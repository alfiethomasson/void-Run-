/*#pragma once
#include "Entity.h"

using namespace sf;

class Ghost : public Entity {
private:
	float _speed;
	double elapsed_time;
	Clock clock1;

	double deltatime;

	float directionH;
	float directionV;

public:
	void Update(double dt) override;
	Ghost();
	void Render(sf::RenderWindow& window) const override;
};*/