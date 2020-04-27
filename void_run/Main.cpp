#include "engine.h"
#include "Game.h"

using namespace std; //Use namespace

MenuScene menuScene; //The main menu scene
GameScene gameScene; //The main game scene
VictoryScene victoryScene; //The victory scene, when the player wins

int main() {
	Engine::Start(1920, 1080, "void Run()", &menuScene); //Always start on the main menu
}
