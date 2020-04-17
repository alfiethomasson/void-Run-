#include "UI.h"

void CombatUI::Render()
{
 	Renderer::queue(&attackSprite);
	Renderer::queue(&specialSprite);
}

void CombatUI::turnUpdate()
{

}

void CombatUI::Load()
{
	if (!attackTex.loadFromFile("res/Icons/Attack.png"))
	{
		std::cout << "Couldn't load attack icon\n";
	}
	attackSprite.setTexture(attackTex);
	attackSprite.setScale(0.3f, 0.3f);
	attackSprite.setPosition(sf::Vector2f(500.0f, 600.0f));
	attackBox = attackSprite.getGlobalBounds();

	specialSprite.setPosition(sf::Vector2f(600.0f, 600.0f));
	specialBox = specialSprite.getGlobalBounds();
}

sf::FloatRect& CombatUI::getAttackBox()
{
	return attackBox;
}

void CombatUI::addSpecial(std::string texName)
{
	if (!specialTex.loadFromFile("res/icons/" + texName + ".png"))
	{
		std::cout << "Failed to load " << texName << " combat icon\n";
	}
	specialSprite.setTexture(specialTex);
	specialSprite.setPosition(sf::Vector2f(600.0f, 600.0f));
	specialSprite.setScale(0.3f, 0.3f);
}

void CombatUI::resetSpecial()
{
	specialSprite = sf::Sprite();
}