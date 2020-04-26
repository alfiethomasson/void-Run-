#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	/* Load the texture */
	sf::Texture tempTex;
	tempTex.loadFromFile("res/" + filename );

	/* Add it to the list of textures */
	textures[name] = tempTex;
}

sf::Texture& TextureManager::getTex(const std::string& texture)
{
	return textures.at(texture);
}

void TextureManager::loadFont(const std::string& name)
{
	font.loadFromFile("res/Fonts/" + name);
}

sf::Font& TextureManager::getFont()
{
	return font;
}

void TextureManager::addButton(const std::string& name, const sf::FloatRect& button)
{
	buttons[name] = button;
}

sf::FloatRect TextureManager::getButton(const std::string& name)
{
	return buttons.at(name);
}

std::map<std::string, sf::FloatRect>& TextureManager::getButtonMap()
{
	return buttons;
}

void TextureManager::loadSound(const std::string& name, const std::string& filename)
{
	sf::SoundBuffer buf;
	if (!buf.loadFromFile("res/" + filename))
	{
		std::cout << "Couldn't load " << filename << "\n";
	}
	sounds[name] = buf;
}

sf::SoundBuffer& TextureManager::getSound(const std::string& sound)
{
	return sounds[sound];
}