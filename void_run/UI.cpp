#include "UI.h"

void CombatUI::Render()
{
	Renderer::queue(&attackSprite);
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

	specialSprite.setPosition(sf::Vector2f(600.0f, 700.0f));
	specialBox = specialSprite.getGlobalBounds();
}

sf::FloatRect& CombatUI::getAttackBox()
{
	return attackBox;
}

void CombatUI::addSpecial(sf::Sprite special)
{
	specialSprite = special;
}

void CombatUI::resetSpecial()
{
	specialSprite = sf::Sprite();
}