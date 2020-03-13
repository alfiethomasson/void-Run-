#pragma once
#include <SFML/Graphics.hpp>
//#include "ecm.h"
//#include "Entity.h"
//#include "Player.h"
//#include "Ghost.h"

using namespace sf;
using namespace std;

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

//extern vector<Entity*> entities;
//extern EntityManager em;

const Keyboard::Key controls[4] = {

	Keyboard::Up,
	Keyboard::Down,
	Keyboard::Left,
	Keyboard::Right

};