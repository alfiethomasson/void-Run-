#include "engine.h"
#include "Game.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;
VictoryScene victoryScene;

int main() {
	Engine::Start(1920, 1080, "void Run()", &menuScene);
}
