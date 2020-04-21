#pragma once
#include "VoidRun.h"

using namespace sf;
using namespace std;

constexpr uint16_t gameWidth = 1280;
constexpr uint16_t gameHeight = 720;

extern MenuScene menuScene;
extern GameScene gameScene;
extern std::shared_ptr<BasePlayerComponent> player;
extern bool isPaused;

extern Keyboard::Key attackKey;
extern Keyboard::Key healKey;
extern Keyboard::Key rechargeKey;
extern Keyboard::Key runKey;
extern Keyboard::Key pauseKey;
