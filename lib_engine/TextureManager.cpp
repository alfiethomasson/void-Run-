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