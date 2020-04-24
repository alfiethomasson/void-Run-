#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>

class TextureManager
{
private:
	/* Array of textures used */
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::FloatRect> buttons;
	std::map<std::string, sf::SoundBuffer> sounds;
	sf::Font font;

public:
	/* Add a texture from a file */
	void loadTexture(const std::string& name, const std::string& filename);
	void loadSound(const std::string& name, const std::string& filename);
	void addButton(const std::string& name, const sf::FloatRect& button);

	/* Translate an id into a reference */
	sf::Texture& getTex(const std::string& texture);
	sf::SoundBuffer& getSound(const std::string& sound);

	void loadFont(const std::string& name);
	sf::Font& getFont();
	sf::FloatRect getButton(const std::string& name);
	std::map<std::string, sf::FloatRect>& getButtonMap();

	/* Constructor */
	TextureManager() {}
};
