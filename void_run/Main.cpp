#include "engine.h"
#include "Game.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;

int main() {
	Engine::Start(1280, 720, "void Run()", &menuScene);
}
