#include "Scene.h"
#include "ecm.h"
#include <iostream>

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text GameName;
	sf::Text PlayButton;
	sf::Text ExitButton;
	sf::Font font;
	sf::FloatRect PlayButtonBox;
	sf::FloatRect ExitButtonBox;

public:
	MenuScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
	void ChangeRoom();
	bool playerTurn;
};
