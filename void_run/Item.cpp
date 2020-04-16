#include "Item.h"
#include "cmp_player.h"

Item::Item(int strength, int health, int dexterity, std::string desc, std::string texName)
	: strengthMod{ strength },
	healthMod{ health }, dexMod{ dexterity }, description{ desc }, texName(texName) {}

void Item::Equip(Entity newUser)
{
	Load();
	user = newUser;
	auto p = user.GetCompatibleComponent<BasePlayerComponent>();
	auto s = p[0];

	s->addStats(strengthMod, healthMod, dexMod);
}

void Item::Unequip()
{
	auto p = user.GetCompatibleComponent<BasePlayerComponent>();
	auto s = p[0];

	s->addStats(-strengthMod, -healthMod, -dexMod);
}

void Item::Load()
{
	if (!tex.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/void-Run-/res/Icons/" + texName + ".png"))
	{
		std::cout << "Failed to load Texture: " << texName << "\n";
	}
	sprite.setTexture(tex);
	sprite.setScale(0.4f, 0.4f);
}

sf::Sprite& Item::getSprite()
{
	return sprite;
}