#include "Specials.h"
#include "Game.h"

void LaserBurst::update(double dt)
{
	SpecialAbility::update(dt);
}

void LaserBurst::load()
{
	texName = "LaserBurst";
	description = "A burst of energy that hits\nthe enemy for 2 x strength";
	name = "Laser Burst";
	APCost = 3;
}

void LaserBurst::doEffect()
{
			player->SpendAP(APCost);
			std::cout << "LASER BURST!\n";
			gameScene.UpdateTextBox("LASER BURST!");
			player->attack(player->getStrength() * 2, 0);
			player->EndTurn();
}

void LaserBurst::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}

void OverloadWeapon::update(double dt)
{
	SpecialAbility::update(dt);
}

void OverloadWeapon::load()
{
	texName = "OverloadWeapon";
	description = "Overload your weapons energy cells\n to give you +50 strength for \nthis combat";
	name = "Overload Weapon";
	APCost = 6;
	amount = 0;
}

void OverloadWeapon::doEffect()
{
			player->SpendAP(APCost);
			player->addStats(50, 0, 0);
			gameScene.UpdateTextBox("WEAPON OVERLOADED");
			player->EndTurn();
			amount++;
}

void OverloadWeapon::Reset()
{
	for (int i = 0; i < amount; i++)
	{
		player->addStats(-50, 0, 0);
	}
	amount = 0;
}

void OverloadWeapon::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}

void UncannySpeed::update(double dt)
{
	SpecialAbility::update(dt);
}

void UncannySpeed::load()
{
	texName = "UncannySpeed";
	description = "Activate your suits matrix function\nimproving your dexterity by 50 this combat";
	name = "Uncanny Speed";
	APCost = 5;
	amount = 0;
}

void UncannySpeed::doEffect()
{
			player->SpendAP(APCost);
			player->addStats(0, 0, 50);
			player->getSpriteComponent()->AddIcon(texName, "Improved Dexterity", false);
			gameScene.UpdateTextBox("UNCANNY SPEED ACTIVATED");
			player->EndTurn();
}

void UncannySpeed::Reset()
{
	for (int i = 0; i < amount; i++)
	{
		player->addStats(0, 0, -50);
	}
	amount = 0;
}

void UncannySpeed::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}

void PrimalInstincts::update(double dt)
{
	SpecialAbility::update(dt);
}

void PrimalInstincts::load()
{
	texName = "PrimalInstincts";
	description = "Temporarily tap into your primal\ninstincts, increasing all your stats\n for this combat";
	name = "Primal Instincts";
	APCost = 5;
	amount = 0;
}

void PrimalInstincts::doEffect()
{
			player->SpendAP(APCost);
			player->addStats(20, 50, 20);
			player->getSpriteComponent()->AddIcon(texName, "All stats improved", false);
			gameScene.UpdateTextBox("PRIMAL INSTICTS ACTIVATED");
			amount += 1;
			player->EndTurn();
}

void PrimalInstincts::Reset()
{
	for (int i = 0; i < amount; i++)
	{
		player->addStats(-20, -50, -20);
	}
	amount = 0;
}

void PrimalInstincts::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}

void DeadlyFumes::update(double dt)
{
	SpecialAbility::update(dt);
}

void DeadlyFumes::load()
{
	texName = "DeadlyFumes";
	description = "Spray the enemy with fumes\n that deal small damage over time\n and lowers their dexterity by 15";
	name = "Deadly Fumes";
	APCost = 4;
}

void DeadlyFumes::doEffect()
{
			player->SpendAP(APCost);
			player->getEnemy()->addStats(0, 0, -20);
			enemySprite = player->getEnemy()->getSprite();
			enemySprite->AddIcon(texName, "Lowered Dex and\n damage over time", true);
			gameScene.UpdateTextBox("DEADLY FUMES ACTIVATED");
			used = true;
			player->EndTurn();
}

void DeadlyFumes::turnStart()
{
	if (used)
	{
		player->getEnemy()->TakeDamage(5);
	}
}

void DeadlyFumes::Reset()
{
	used = false;
}

void DeadlyFumes::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key) && used == false)
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}

void MagmaGrenade::update(double dt)
{
	SpecialAbility::update(dt);
}

void MagmaGrenade::load()
{
	texName = "MagmaGrenade";
	description = "Launch a powerful grenade, dealing\nmedium damage and inflicting high\ndamage over time";
	name = "Magma Grenade";
	APCost = 7;
	used = false;
}

void MagmaGrenade::doEffect()
{
			player->SpendAP(APCost);
			player->getEnemy()->TakeDamage(player->getStrength());
			enemySprite = player->getEnemy()->getSprite();
			enemySprite->AddIcon(texName, "High Damage over Time", true);
			gameScene.UpdateTextBox("MAGMA GRENADE ACTIVATED");
			used = true;
			player->EndTurn();
}

void MagmaGrenade::turnStart()
{
	if (used)
	{
		player->getEnemy()->TakeDamage(5);
	}
}

void MagmaGrenade::Reset()
{
	used = false;
}

void MagmaGrenade::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key) && !used)
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}

void NanoBots::update(double dt)
{
	SpecialAbility::update(dt);
}

void NanoBots::load()
{
	texName = "NanoBots";
	description = "Release Nano bots into the\nair around you, healing you 10 every\nturn this combat";
	name = "Nano Bots";
	APCost = 7;
	used = false;
}

void NanoBots::doEffect()
{
	player->SpendAP(APCost);
	player->getSpriteComponent()->AddIcon(texName, "Healing every turn", false);
	gameScene.UpdateTextBox("NANO BOTS ACTIVATED");
	used = true;
	player->EndTurn();
}

void NanoBots::turnStart()
{
	if (used)
	{
		player->heal(10, false);
	}
}

void NanoBots::Reset()
{
	used = false;
}

void NanoBots::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key) && !used)
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}

void HoloGamble::update(double dt)
{
	SpecialAbility::update(dt);
}

void HoloGamble::load()
{
	texName = "HoloGamble";
	description = "Draw from the deck, granting\na random permanent amount of strength,\nHP, and dexterity. Mostly\ngood but can be bad";
	name = "Holo-Gamble";
	APCost = 10;
}

void HoloGamble::doEffect()
{
	player->SpendAP(APCost);
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger(-5, 15);

	int randStr = distributionInteger(generator);

	unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator2(seed2);

	int randDex = distributionInteger(generator2);

	// construct a trivial random generator engine from a time-based seed:
	unsigned seed3 = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator3(seed3);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger2(-10, 30);

	int randHP = distributionInteger2(generator3);

	std::cout << "\nHolo gamble: " << randStr << " , " << randDex << " , " << randHP << "\n";

	player->addStats(randStr, randHP, randDex);

	gameScene.UpdateTextBox("HOLO GAMBLE ACTIVATED");
	player->EndTurn();
}

void HoloGamble::Reset()
{
	
}

void HoloGamble::checkKey()
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (player->CheckAP(APCost))
		{
			doEffect();
		}
	}
}