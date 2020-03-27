#include "engine.h"
#include "Game.h"
#include "VoidRun.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;

int main() {
	Engine::Start(1280, 720, "void Run()", &gameScene);
}
