#pragma once
#include "VoidRun.h"

#define GAMEX 1920
#define GAMEY 1080

using namespace sf;
using namespace std;

constexpr uint16_t gameWidth = 1920;
constexpr uint16_t gameHeight = 1080;

extern MenuScene menuScene;
extern GameScene gameScene;
extern std::shared_ptr<BasePlayerComponent> player;
extern bool isPaused;

extern Keyboard::Key attackKey;
extern Keyboard::Key healKey;
extern Keyboard::Key rechargeKey;
extern Keyboard::Key runKey;
extern Keyboard::Key special1Key;
extern Keyboard::Key special2Key;
extern Keyboard::Key special3Key;
extern Keyboard::Key special4Key;
extern Keyboard::Key pauseKey;
