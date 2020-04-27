#include "Item.h"
#include "cmp_player.h"
#include "Game.h"

//Base Item constructor
Item::Item(int strength, int health, int dexterity, std::string name, std::string desc, std::string texName)
	: strengthMod{ strength },	healthMod{ health }, dexMod{ dexterity }, 
	name{ name }, description{ desc }, texName(texName) {}

//Base Equip for new items
void Item::Equip(Entity newUser, bool addStat)
{
	//Calls Load function
	Load();
	//Get Player component
	user = newUser;
	auto p = user.GetCompatibleComponent<BasePlayerComponent>();
	player = p[0];
	//If add stat is true it means that the player gains stats associated with item, if false they dont
	//Will be false if item is loaded from save file and true otherwise
	if (addStat)
	{
		player->addStats(strengthMod, healthMod, dexMod);
	}
}

//Remove stats that item gave
void Item::Unequip(int position)
{
	player->addStats(-strengthMod, -healthMod, -dexMod);
}

//Assigns texture and sets scale
void Item::Load()
{
	sprite.setTexture(Engine::tm.getTex(texName));
	sprite.setScale(0.4f, 0.4f);
}

//Returns Sprite for item
sf::Sprite& Item::getSprite()
{
	return sprite;
}

//Constructor for special items, items that give abilities
SpecialItem::SpecialItem(int strength, int health, int dexterity, std::string name,
	std::string desc, std::string texName, std::shared_ptr<SpecialAbility> sp)
	: special{ sp }, Item{ strength, health, dexterity, name, desc, texName } {}

//Equip for special items
void SpecialItem::Equip(Entity newUser, bool addStat)
{
	//calls base class equip
	Item::Equip(newUser, addStat);
	//gets players ability manager
	auto a = user.GetCompatibleComponent<AbilityManager>();
	auto m = a[0];

	//If item is newly equipped and not loaded from save
	if (addStat)
	{
		//if if player has room for more ability, adds ability to manager to be used
		if (m->addAbility(special))
		{
			//assigns player to special ability
			special->updatePlayer(player);
			//adds special ability to combat UI 
			gameScene.combatUI.addSpecial(special->getTexName(), special);
		}
	}
}

//When special item is unequiped
void SpecialItem::Unequip(int position)
{
	auto a = user.GetCompatibleComponent<AbilityManager>();
	auto m = a[0];

	//Removes ability from user
	m->removeAbility(position);
	gameScene.combatUI.resetSpecial();
	Item::Unequip(position);
}