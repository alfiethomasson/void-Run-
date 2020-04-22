#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
private:
	/* Array of textures used */
	std::map<std::string, sf::Texture> textures;
	sf::Font font;

public:
	/* Add a texture from a file */
	void loadTexture(const std::string& name, const std::string& filename);

	/* Translate an id into a reference */
	sf::Texture& getTex(const std::string& texture);

	void loadFont(const std::string& name);
	sf::Font& getFont();

	/* Constructor */
	TextureManager() {}
};
