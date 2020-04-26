#include "Item.h"
#include "cmp_player.h"
#include "Game.h"

Item::Item(int strength, int health, int dexterity, std::string name, std::string desc, std::string texName)
	: strengthMod{ strength },	healthMod{ health }, dexMod{ dexterity }, 
	name{ name }, description{ desc }, texName(texName) {}

void Item::Equip(Entity newUser, bool addStat)
{
	Load();
	user = newUser;
	auto p = user.GetCompatibleComponent<BasePlayerComponent>();
	player = p[0];
	if (addStat)
	{
		player->addStats(strengthMod, healthMod, dexMod);
	}
}

void Item::Unequip(int position)
{
	player->addStats(-strengthMod, -healthMod, -dexMod);
}

void Item::Load()
{
	sprite.setTexture(Engine::tm.getTex(texName));
	sprite.setScale(0.4f, 0.4f);
}

sf::Sprite& Item::getSprite()
{
	return sprite;
}

SpecialItem::SpecialItem(int strength, int health, int dexterity, std::string name,
	std::string desc, std::string texName, std::shared_ptr<SpecialAbility> sp)
	: special{ sp }, Item{ strength, health, dexterity, name, desc, texName } {}

void SpecialItem::Equip(Entity newUser, bool addStat)
{
	Item::Equip(newUser, addStat);
	auto a = user.GetCompatibleComponent<AbilityManager>();
	auto m = a[0];

	if (addStat)
	{
		if (m->addAbility(special))
		{
			special->updatePlayer(player);
			gameScene.combatUI.addSpecial(special->getTexName(), special);
		}
	}
}

void SpecialItem::Unequip(int position)
{
	auto a = user.GetCompatibleComponent<AbilityManager>();
	auto m = a[0];

	m->removeAbility(position);
	gameScene.combatUI.resetSpecial();
	Item::Unequip(position);
}