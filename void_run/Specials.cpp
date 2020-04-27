#include "Specials.h"
#include "Game.h"

void LaserBurst::update(double dt)
{
	SpecialAbility::update(dt);
}

//
void LaserBurst::load() //Sets default values!
{
	texName = "LaserBurst";
	description = "A burst of energy that hits\nthe enemy for 2 x strength";
	name = "Laser Burst";
	APCost = 3;
}

void LaserBurst::doEffect()
{
	//Spends AP 
	player->SpendAP(APCost);
	//Updates text box to show Laser Burst has been used
	gameScene.UpdateTextBox("LASER BURST!");
	//Uses Laser Burst, like a normal attack but double damage
	player->attack(player->getStrength() * 2, 0, "LaserBurst");
	player->EndTurn();
}

//Checks if key assigned to laserburst is pressed, and does effect if so
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
	SpecialAbility::update(dt); // base update
}

void OverloadWeapon::load() //Sets default values!
{
	texName = "OverloadWeapon";
	description = "Overload your weapons energy cells\n to give you +50 strength for \nthis combat";
	name = "Overload Weapon";
	APCost = 6;
	amount = 0;
}

void OverloadWeapon::doEffect()
{
	//Spends AP
	player->SpendAP(APCost);
	//Gives player bonus stats as per effect
	player->addStats(50, 0, 0);
	gameScene.UpdateTextBox("WEAPON OVERLOADED");
	//plays sound of eff
	gameScene.gameUI.playSound("OverloadWeapon", 100);
	player->EndTurn();
	amount++;
}

//Removes stats given to player by effect
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

void UncannySpeed::load() //Sets default values!
{
	texName = "UncannySpeed";
	description = "Activate your suits matrix function\nimproving your dexterity by 50 this combat";
	name = "Uncanny Speed";
	APCost = 5;
	amount = 0;
}

void UncannySpeed::doEffect()
{
	//Adds dex to uncanny 
	player->SpendAP(APCost);
	player->addStats(0, 0, 50);
	player->getSpriteComponent()->AddIcon(texName, "Improved Dexterity", false);
	gameScene.UpdateTextBox("UNCANNY SPEED ACTIVATED");
	gameScene.gameUI.playSound("UncannySpeed", 100);
	player->EndTurn();
}

//Removes stats given to player by effect
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

void PrimalInstincts::load() //Sets default values!
{
	texName = "PrimalInstincts";
	description = "Temporarily tap into your primal\ninstincts, increasing all your stats\n for this combat";
	name = "Primal Instincts";
	APCost = 5;
	amount = 0;
}

void PrimalInstincts::doEffect()
{
	//Spend AP, add Stats, play sound etc
	player->SpendAP(APCost);
	player->addStats(20, 50, 20);
	player->getSpriteComponent()->AddIcon(texName, "All stats improved", false);
	gameScene.UpdateTextBox("PRIMAL INSTICTS ACTIVATED");
	gameScene.gameUI.playSound("PrimalInstincts", 100);
	amount += 1;
	player->EndTurn();
}

//Removes player stats given by effect
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

void DeadlyFumes::load() //Sets default values!
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
	gameScene.gameUI.playSound("DeadlyFumes", 100);
	used = true;
	player->EndTurn();
}

void DeadlyFumes::turnStart()
{
	//If deadly fumes is active, deal small damage at beginning of player turn
	if (used)
	{
		player->getEnemy()->TakeDamage(5);
	}
}

//resets deadly fumes
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

void MagmaGrenade::load() //Sets default values!
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
	player->getEnemy()->TakeDamage(50.0f);
	enemySprite = player->getEnemy()->getSprite();
	enemySprite->AddIcon(texName, "High Damage over Time", true);
	gameScene.gameUI.playSound("MagmaGrenade", 100);
	gameScene.UpdateTextBox("MAGMA GRENADE ACTIVATED");
	used = true;
	player->EndTurn();
}

void MagmaGrenade::turnStart()
{
	//same as deadly fumes
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

void NanoBots::load() //Sets default values!
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
	gameScene.gameUI.playSound("NanoBots", 100);
	gameScene.UpdateTextBox("NANO BOTS ACTIVATED");
	used = true;
	player->EndTurn();
}

void NanoBots::turnStart()
{
	//heal player if used
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

void HoloGamble::load() //Sets default values!
{
	texName = "HoloGamble";
	description = "Draw from the deck, granting\na random permanent amount of strength,\nHP, and dexterity. Mostly\ngood but can be bad";
	name = "Holo-Gamble";
	APCost = 10;
}

void HoloGamble::doEffect()
{
	player->SpendAP(APCost);

	//Gets 3 random values, and gives player random stats depending on what they are

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

	gameScene.gameUI.playSound("HoloGamble", 100);

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