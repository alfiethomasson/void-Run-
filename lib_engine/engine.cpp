#include "engine.h"
#include "maths.h"
//#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

float Engine::xMultiply;
float Engine::yMultiply;
TextureManager Engine::tm;
float Engine::oldWinX;
float Engine::oldWinY;
bool Engine::isFullscreen;

void Loading_update(float dt, const Scene* const scn) {
	//  cout << "Eng: Loading Screen\n";
	if (scn->isLoaded()) {
		cout << "Eng: Exiting Loading Screen\n";
		loading = false;
	}
	else {
		loadingspinner += 220.0f * dt;
		loadingTime += dt;
	}
}
void Loading_render() {
	// cout << "Eng: Loading Screen Render\n";
	static CircleShape octagon(80, 8);
	octagon.setOrigin(80, 80);
	octagon.setRotation(loadingspinner);
	octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
	octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
	static Text t("Loading", *Resources::get<sf::Font>("mandalore.ttf"));
	t.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
	t.setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.0f - (t.getGlobalBounds().width / 2), Engine::getWindowSize().y / 3.5)) ;
	Renderer::queue(&t);
	Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
		frametimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 60 == 0) {
			double davg = 0;
			for (const auto t : frametimes) {
				davg += t;
			}
			davg = 1.0 / (davg / 255.0);
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	if (loading) {
		Loading_update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		//Physics::update(dt);
		_activeScene->Update(dt);
	}
}

void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn) {
	RenderWindow window(VideoMode(width, height), gameName, sf::Style::Titlebar);
	//window.setFramerateLimit(120);
	_gameName = gameName;
	_window = &window;
	Renderer::initialise(window);
	//Physics::initialise/();
	ChangeScene(scn);
	oldWinX = getWindowSize().x;
	oldWinY = getWindowSize().y;
	xMultiply = 1.0f;
	yMultiply = 1.0f;
	isFullscreen = false;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

	//	std::cout << "XMULTIPLY = " << xMultiply << " , " << "YMULTIPLY = " << yMultiply << "\n";
		window.clear();
		Update();
		Render(window);
		window.display();
	}
	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}
	window.close();
	//Physics::shutdown();
	// Render::shutdown();
}

void Engine::ChangeResolution(int x, int y, int GAMEX, int GAMEY)
{
	std::cout << "Should change Res\n";

	int oldX = Engine::getWindowSize().x;
	int oldY = Engine::getWindowSize().y;

	// All together now in a reusable solution.
	const sf::Vector2u screensize(x, y);
	const sf::Vector2u gamesize(GAMEX, GAMEY);
	//set View as normalx`
	Engine::GetWindow().setSize(screensize);
	sf::FloatRect visibleArea(0.f, 0.f, gamesize.x, gamesize.y);
	auto v = sf::View(visibleArea);
	// figure out how to scale and maintain aspect;
	auto viewport = CalculateViewport(screensize, gamesize);
	//Optionally Center it
	bool centered = true;
	if (centered) {
		viewport.left = (1.0 - viewport.width) * 0.5;
		viewport.top = (1.0 - viewport.height) * 0.5;
	}
	//set
	v.setViewport(viewport);
	Engine::GetWindow().setView(v);
	//ExitButtonBox = ExitButton.getGlobalBounds();
	//std::cout << PlayButtonBox.getPosition().x << " , " << PlayButtonBox.getPosition().y << "\n";
	float winX = Engine::getWindowSize().x;
	float winY = Engine::getWindowSize().y;
	std::cout << "view Size  X" << GetWindow().getViewport(v).width << ", " << "view size y " << GetWindow().getViewport(v).height << "\n";
	std::cout << "win Size  X" << winX << ", " << "win size y " << winY << "\n";
	float xView = GetWindow().getViewport(v).width;
	float yView = GetWindow().getViewport(v).height;
	float viewMultX = winX / xView;
	float viewMultY = winY / yView;
	float sizeMultX = winX / GAMEX;
	float sizeMultY = winY / GAMEY;
	xMultiply = winX / GAMEX;
	yMultiply = winY / GAMEY;
	std::cout << "XMultiply: " << xMultiply << "\n";
	std::cout << "YMultiply: " << yMultiply << "\n";
	oldWinX = winX;
	oldWinY = winY;
	//map<string, sf::FloatRect>::iterator it;
	//////std::cout << "SIZE OF BUTTON MAP IN ENGINE " << tm.getButtonMap().size() << "\n";
	////std::cout << "Button currently at : " << tm.getButton("attackBox").getPosition() << "\n";
	////for (auto& p : tm.getButtonMap())
	////{
	////	//std::cout << "BUTTON BEFORE UPDATE: " << tm.getButton("attackBox").getSize() << "\n";
	////	UpdateButton(p.second);
	////	std::cout << "BUTTON AFTER UPDATE: " << tm.getButton("attackBox").getSize() << "\n";
	////}//
}

sf::FloatRect Engine::CalculateViewport(const sf::Vector2u& screensize,
	const sf::Vector2u& gamesize) {

	const Vector2f screensf(screensize.x, screensize.y);
	const Vector2f gamesf(gamesize.x, gamesize.y);
	const float gameAspect = gamesf.x / gamesf.y;
	const float screenAspect = screensf.x / screensf.y;
	float scaledWidth;  // final size.x of game viewport in piels
	float scaledHeight; //final size.y of game viewport in piels
	bool scaleSide = false; // false = scale to screen.x, true = screen.y

	//Work out which way to scale
	if (gamesize.x > gamesize.y) { // game is wider than tall
	  // Can we use full width?
		if (screensf.y < (screensf.x / gameAspect)) {
			//no, not high enough to fit game height
			scaleSide = true;
		}
		else {
			//Yes, use all width available
			scaleSide = false;
		}
	}
	else { // Game is Square or Taller than Wide
   // Can we use full height?
		if (screensf.x < (screensf.y * gameAspect)) {
			// No, screensize not wide enough to fit game width
			scaleSide = false;
		}
		else {
			// Yes, use all height available
			scaleSide = true;
		}
	}

	if (scaleSide) { // use max screen height
		scaledHeight = screensf.y;
		scaledWidth = floor(scaledHeight * gameAspect);
	}
	else { //use max screen width
		scaledWidth = screensf.x;
		scaledHeight = floor(scaledWidth / gameAspect);
	}

	//calculate as percent of screen
	const float widthPercent = (scaledWidth / screensf.x);
	const float heightPercent = (scaledHeight / screensf.y);

	return sf::FloatRect(0, 0, widthPercent, heightPercent);
}

void Engine::SetFullScreen(sf::RenderWindow& window, bool tf)
{
	if (tf)
	{
		isFullscreen = true;
		window.create(VideoMode(1920, 1080), "Void Run", sf::Style::Fullscreen);
	}
	else
	{
		isFullscreen = false;
		window.create(VideoMode(1920, 1080), "Void Run", sf::Style::Titlebar);
	}
}

bool Engine::getFullscreen()
{
	return isFullscreen;
}

void Engine::UpdateButton(sf::FloatRect& button)
{
	button.left = button.left * Engine::xMultiply;
	button.top = button.top * Engine::yMultiply;
	button.width = button.width * Engine::xMultiply;
	button.height = button.height * Engine::yMultiply;
}

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>();
	ents.list.push_back(e);
	return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
	cout << "Eng: changing scene: " << s << endl;
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad(); // todo: Unload Async
	}

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0;
		_activeScene->LoadAsync();
		//_activeScene->Load();
		loading = true;
	}
}

void Scene::Update(const double& dt) { ents.Update(dt); }

void Scene::Render() { ents.Render(); }

bool Scene::isLoaded() const {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		// Are we already loading asynchronously?
		if (_loaded_future.valid() // yes
			&&                     // Has it finished?
			_loaded_future.wait_for(chrono::seconds(0)) ==
			future_status::ready) {
			// Yes
			_loaded_future.get();
			_loaded = true;
		}
		return _loaded;
	}
}
void Scene::setLoaded(bool b) {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		_loaded = b;
	}
}

void Scene::UnLoad() {
	ui.list.clear();
	ents.list.clear();
	setLoaded(false);
}

//void Scene::ChangeResolution(int x, int y, int GAMEX, int GAMEY)
//{
//	std::cout << "Should change Res\n";
//
//	int oldX = Engine::getWindowSize().x;
//	int oldY = Engine::getWindowSize().y;
//
//	// All together now in a reusable solution.
//	const sf::Vector2u screensize(x, y);
//	const sf::Vector2u gamesize(GAMEX, GAMEY);
//	//set View as normalx`
//	Engine::GetWindow().setSize(screensize);
//	sf::FloatRect visibleArea(0.f, 0.f, gamesize.x, gamesize.y);
//	auto v = sf::View(visibleArea);
//	// figure out how to scale and maintain aspect;
//	auto viewport = CalculateViewport(screensize, gamesize);
//	//Optionally Center it
//	bool centered = true;
//	if (centered) {
//		viewport.left = (1.0 - viewport.width) * 0.5;
//		viewport.top = (1.0 - viewport.height) * 0.5;
//	}
//	//set
//	v.setViewport(viewport);
//	Engine::GetWindow().setView(v);
//	//ExitButtonBox = ExitButton.getGlobalBounds();
//	//std::cout << PlayButtonBox.getPosition().x << " , " << PlayButtonBox.getPosition().y << "\n";
//	float winX = Engine::getWindowSize().x;
//	float winY = Engine::getWindowSize().y;
//	//xMultiply = winX / oldX;
//	//yMultiply = winY / oldY;
//}
//
//sf::FloatRect Scene::CalculateViewport(const sf::Vector2u& screensize,
//	const sf::Vector2u& gamesize) {
//
//	const Vector2f screensf(screensize.x, screensize.y);
//	const Vector2f gamesf(gamesize.x, gamesize.y);
//	const float gameAspect = gamesf.x / gamesf.y;
//	const float screenAspect = screensf.x / screensf.y;
//	float scaledWidth;  // final size.x of game viewport in piels
//	float scaledHeight; //final size.y of game viewport in piels
//	bool scaleSide = false; // false = scale to screen.x, true = screen.y
//
//	//Work out which way to scale
//	if (gamesize.x > gamesize.y) { // game is wider than tall
//	  // Can we use full width?
//		if (screensf.y < (screensf.x / gameAspect)) {
//			//no, not high enough to fit game height
//			scaleSide = true;
//		}
//		else {
//			//Yes, use all width available
//			scaleSide = false;
//		}
//	}
//	else { // Game is Square or Taller than Wide
//   // Can we use full height?
//		if (screensf.x < (screensf.y * gameAspect)) {
//			// No, screensize not wide enough to fit game width
//			scaleSide = false;
//		}
//		else {
//			// Yes, use all height available
//			scaleSide = true;
//		}
//	}
//
//	if (scaleSide) { // use max screen height
//		scaledHeight = screensf.y;
//		scaledWidth = floor(scaledHeight * gameAspect);
//	}
//	else { //use max screen width
//		scaledWidth = screensf.x;
//		scaledHeight = floor(scaledWidth / gameAspect);
//	}
//
//	//calculate as percent of screen
//	const float widthPercent = (scaledWidth / screensf.x);
//	const float heightPercent = (scaledHeight / screensf.y);
//
//	return sf::FloatRect(0, 0, widthPercent, heightPercent);
//}

//void Scene::UpdateButton(sf::FloatRect& button)
//{
//	button.width = button.width * xMultiply;
//	button.height = button.height * yMultiply;
//	button.left = button.left * xMultiply;
//	button.top = button.top * yMultiply;
//}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing

Scene::~Scene() { UnLoad(); }

std::string Engine::keyToString(const sf::Keyboard::Key& key) {
	string ret;
	switch (key) {

	case sf::Keyboard::A:

		ret = "A";
		break;
	case sf::Keyboard::B:

		ret = "B";
		break;
	case sf::Keyboard::C:

		ret = "C";
		break;
	case sf::Keyboard::D:

		ret = "D";
		break;
	case sf::Keyboard::E:

		ret = "E";
		break;
	case sf::Keyboard::F:

		ret = "F";
		break;
	case sf::Keyboard::G:

		ret = "G";
		break;
	case sf::Keyboard::H:

		ret = "H";
		break;
	case sf::Keyboard::I:

		ret = "I";
		break;
	case sf::Keyboard::J:

		ret = "J";
		break;
	case sf::Keyboard::K:

		ret = "K";
		break;
	case sf::Keyboard::L:

		ret = "L";
		break;
	case sf::Keyboard::M:

		ret = "M";
		break;
	case sf::Keyboard::N:

		ret = "N";
		break;
	case sf::Keyboard::O:

		ret = "O";
		break;
	case sf::Keyboard::P:

		ret = "P";
		break;
	case sf::Keyboard::Q:

		ret = "Q";
		break;
	case sf::Keyboard::R:

		ret = "R";
		break;
	case sf::Keyboard::S:

		ret = "S";
		break;
	case sf::Keyboard::T:

		ret = "T";
		break;
	case sf::Keyboard::U:

		ret = "U";
		break;
	case sf::Keyboard::V:

		ret = "V";
		break;
	case sf::Keyboard::W:

		ret = "W";
		break;
	case sf::Keyboard::X:

		ret = "X";
		break;
	case sf::Keyboard::Y:

		ret = "Y";
		break;
	case sf::Keyboard::Z:

		ret = "Z";
		break;
	case sf::Keyboard::Num0:

		ret = "0";
		break;
	case sf::Keyboard::Num1:

		ret = "1";
		break;
	case sf::Keyboard::Num2:

		ret = "2";
		break;
	case sf::Keyboard::Num3:

		ret = "3";
		break;
	case sf::Keyboard::Num4:

		ret = "4";
		break;
	case sf::Keyboard::Num5:

		ret = "5";
		break;
	case sf::Keyboard::Num6:

		ret = "6";
		break;
	case sf::Keyboard::Num7:

		ret = "7";
		break;
	case sf::Keyboard::Num8:

		ret = "8";
		break;
	case sf::Keyboard::Num9:

		ret = "9";
		break;
	case sf::Keyboard::Escape:

		ret = "Escape";
		break;
	case sf::Keyboard::LControl:

		ret = "LControl";
		break;
	case sf::Keyboard::LShift:

		ret = "LShift";
		break;
	case sf::Keyboard::LAlt:

		ret = "LAlt";
		break;
	case sf::Keyboard::LSystem:

		ret = "LSystem";
		break;
	case sf::Keyboard::RControl:

		ret = "RControl";
		break;
	case sf::Keyboard::RShift:

		ret = "RShift";
		break;
	case sf::Keyboard::RAlt:

		ret = "RAlt";
		break;
	case sf::Keyboard::RSystem:

		ret = "RSystem";
		break;
	case sf::Keyboard::Menu:

		ret = "Menu";
		break;
	case sf::Keyboard::LBracket:

		ret = "LBracket";
		break;
	case sf::Keyboard::RBracket:

		ret = "RBracket";
		break;
	case sf::Keyboard::SemiColon:

		ret = "SemiColon";
		break;
	case sf::Keyboard::Comma:

		ret = "Comma";
		break;
	case sf::Keyboard::Period:

		ret = "Period";
		break;
	case sf::Keyboard::Quote:

		ret = "Quote";
		break;
	case sf::Keyboard::Slash:

		ret = "Slash";
		break;
	case sf::Keyboard::BackSlash:

		ret = "BackSlash";
		break;
	case sf::Keyboard::Tilde:

		ret = "Tilde";
		break;
	case sf::Keyboard::Equal:

		ret = "Equal";
		break;
	case sf::Keyboard::Dash:

		ret = "Dash";
		break;
	case sf::Keyboard::Space:

		ret = "Space";
		break;
	case sf::Keyboard::Return:

		ret = "Return";
		break;
	case sf::Keyboard::BackSpace:

		ret = "BackSpace";
		break;
	case sf::Keyboard::Tab:

		ret = "Tab";
		break;
	case sf::Keyboard::PageUp:

		ret = "PageUp";
		break;
	case sf::Keyboard::PageDown:

		ret = "PageDown";
		break;
	case sf::Keyboard::End:

		ret = "End";
		break;
	case sf::Keyboard::Home:

		ret = "Home";
		break;
	case sf::Keyboard::Insert:

		ret = "Insert";
		break;
	case sf::Keyboard::Delete:

		ret = "Delete";
		break;
	case sf::Keyboard::Add:

		ret = "Add";
		break;
	case sf::Keyboard::Subtract:

		ret = "Subtract";
		break;
	case sf::Keyboard::Multiply:

		ret = "Multiply";
		break;
	case sf::Keyboard::Divide:

		ret = "Divide";
		break;
	case sf::Keyboard::Left:

		ret = "Left";
		break;
	case sf::Keyboard::Right:

		ret = "Right";
		break;
	case sf::Keyboard::Up:

		ret = "Up";
		break;
	case sf::Keyboard::Down:

		ret = "Down";
		break;
	case sf::Keyboard::Numpad0:

		ret = "Numpad0";
		break;
	case sf::Keyboard::Numpad1:

		ret = "Numpad1";
		break;
	case sf::Keyboard::Numpad2:

		ret = "Numpad2";
		break;
	case sf::Keyboard::Numpad3:

		ret = "Numpad3";
		break;
	case sf::Keyboard::Numpad4:

		ret = "Numpad4";
		break;
	case sf::Keyboard::Numpad5:

		ret = "Numpad5";
		break;
	case sf::Keyboard::Numpad6:

		ret = "Numpad6";
		break;
	case sf::Keyboard::Numpad7:

		ret = "Numpad7";
		break;
	case sf::Keyboard::Numpad8:

		ret = "Numpad8";
		break;
	case sf::Keyboard::Numpad9:

		ret = "Numpad9";
		break;
	case sf::Keyboard::F1:

		ret = "F1";
		break;
	case sf::Keyboard::F2:

		ret = "F2";
		break;
	case sf::Keyboard::F3:

		ret = "F3";
		break;
	case sf::Keyboard::F4:

		ret = "F4";
		break;
	case sf::Keyboard::F5:

		ret = "F5";
		break;
	case sf::Keyboard::F6:

		ret = "F6";
		break;
	case sf::Keyboard::F7:

		ret = "F7";
		break;
	case sf::Keyboard::F8:

		ret = "F8";
		break;
	case sf::Keyboard::F9:

		ret = "F9";
		break;
	case sf::Keyboard::F10:

		ret = "F10";
		break;
	case sf::Keyboard::F11:

		ret = "F11";
		break;
	case sf::Keyboard::F12:

		ret = "F12";
		break;
	case sf::Keyboard::F13:

		ret = "F13";
		break;
	case sf::Keyboard::F14:

		ret = "F14";
		break;
	case sf::Keyboard::F15:

		ret = "F15";
		break;
	case sf::Keyboard::Pause:

		ret = "Pause";
		break;
	case sf::Keyboard::KeyCount:

		ret = "KeyCount";
		break;


	default:
		ret = "Unknow";
		break;
	}
	return ret;
}
