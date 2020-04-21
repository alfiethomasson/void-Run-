#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

struct UIManager
{
	std::vector<sf::Sprite> list;
	void Update(double dt) {};
	void Render();
};

class Scene {
public:
	Scene() = default;
	virtual ~Scene();
	virtual void Load() = 0;
	virtual void LoadAsync();
	virtual void UnLoad();
	virtual void Update(const double& dt);
	virtual void Render();
	void ChangeResolution(int x, int y, int GAMEX, int GAMEY);
	sf::FloatRect CalculateViewport(const sf::Vector2u& screensize,
		const sf::Vector2u& gamesize);
	void UpdateButton(sf::FloatRect& button);
	bool isLoaded() const;
	std::shared_ptr<Entity> makeEntity();
	float xMultiply;
	float yMultiply;

	EntityManager ents;
	UIManager ui;
	std::vector<sf::FloatRect> buttons;

protected:
	void setLoaded(bool);
private:
	mutable bool _loaded;
	mutable std::future<void> _loaded_future;
	mutable std::mutex _loaded_mtx;
};

class Engine {
public:
	Engine() = delete;
	static void Start(unsigned int width, unsigned int height,
		const std::string& gameName, Scene* scn);
	static void ChangeScene(Scene*);
	static sf::RenderWindow& GetWindow();
	static sf::Vector2u getWindowSize();
	static void setVsync(bool b);
	static std::string keyToString(const sf::Keyboard::Key& key);

private:
	static Scene* _activeScene;
	static std::string _gameName;
	static void Update();
	static void Render(sf::RenderWindow& window);
};

namespace timing {
	// Return time since Epoc
	long long now();
	// Return time since last() was last called.
	long long last();
} // namespace timing
