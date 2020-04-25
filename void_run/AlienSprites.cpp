#include "AlienSprites.h"
#include "Game.h"

AlienSprite1::AlienSprite1(Entity* p)
	: SpriteComponent{ p } {}

void AlienSprite1::load()
{
	defaultPos = sf::Vector2f(1420.0f, 290.0f);

	attackSize = sf::Vector2f(573, 700);
	hitSize = sf::Vector2f(371, 556);
	dieSize = sf::Vector2f(851, 577);

	attackSpriteNum = 9;
	hitSpriteNum = 10;
	dieSpriteNum = 17;

	dieDelay = 0.5f;
	hitDelay = 0.5f;

	attackSheet = Engine::tm.getTex("Alien1Attack");
	hitSheet = Engine::tm.getTex("Alien1Hit");
	dieSheet = Engine::tm.getTex("Alien1Die");

	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);

	SpriteComponent::load();
}

void AlienSprite1::render()
{
	SpriteComponent::render();
}

void AlienSprite1::update(double dt)
{
	SpriteComponent::update(dt);
}

void AlienSprite1::playAttack()
{
	SpriteComponent::playAttack();
	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(1450.0f, 140.0f);
	sprite.setScale(0.8f, 0.8f);
}

void AlienSprite1::playHit()
{
	SpriteComponent::playHit();
	sprite.setPosition(1570.0f, 290.0f);
	sprite.setScale(0.8f, 0.8f);

}

void AlienSprite1::playDie()
{
	SpriteComponent::playDie();
	sprite.setPosition(1795.0f, 305.0f);
	sprite.setScale(0.8f, 0.8f);
}

void AlienSprite1::ResetAnim()
{
	SpriteComponent::ResetAnim();
	sheetRect = sf::IntRect(0, 0, hitSize.x, hitSize.y);
	sprite = sf::Sprite(hitSheet, sheetRect);
	sprite.setPosition(defaultPos);
	sprite.setScale(0.8f, 0.8f);
}

AlienSprite2::AlienSprite2(Entity* p)
	: SpriteComponent{ p } {}

void AlienSprite2::load()
{
	defaultPos = sf::Vector2f(850.0f, 200.0f);

	attackSize = sf::Vector2f(625, 384);
	hitSize = sf::Vector2f(430, 327);
	dieSize = sf::Vector2f(591, 352);

	attackSpriteNum = 12;
	hitSpriteNum = 12;
	dieSpriteNum = 12;

	dieDelay = 0.5f;

	attackSheet = Engine::tm.getTex("Alien2Attack");
	hitSheet = Engine::tm.getTex("Alien2Hit");
	dieSheet = Engine::tm.getTex("Alien2Die");

	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);

	SpriteComponent::load();
}

void AlienSprite2::render()
{
	SpriteComponent::render();
}

void AlienSprite2::update(double dt)
{
	SpriteComponent::update(dt);
}

void AlienSprite2::playAttack()
{
	SpriteComponent::playAttack();
	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(940.0f, 160.0f);
	//sprite.setScale(0.6f, 0.6f);
}

void AlienSprite2::playHit()
{
	SpriteComponent::playHit();
	hitDelay = 0.5f;
	sprite.setPosition(1060.0f, 200.0f);
	//sprite.setScale(0.6f, 0.6f);

}

void AlienSprite2::playDie()
{
	SpriteComponent::playDie();
	sprite.setPosition(1080.0f, 207.0f);
	//sprite.setScale(0.6f, 0.6f);
}

void AlienSprite2::ResetAnim()
{
	SpriteComponent::ResetAnim();
	sheetRect = sf::IntRect(0, 0, hitSize.x, hitSize.y);
	sprite = sf::Sprite(hitSheet, sheetRect);
	sprite.setPosition(defaultPos);
	//sprite.setScale(0.6f, 0.6f);
}

AlienSprite3::AlienSprite3(Entity* p)
	: SpriteComponent{ p } {}

void AlienSprite3::load()
{
	defaultPos = sf::Vector2f(850.0f, 150.0f);

	attackSize = sf::Vector2f(532, 385);
	hitSize = sf::Vector2f(349, 390);
	dieSize = sf::Vector2f(392, 478);

	attackSpriteNum = 12;
	hitSpriteNum = 10;
	dieSpriteNum = 20;

	dieDelay = 0.5f;

	attackSheet = Engine::tm.getTex("Alien3Attack");
	hitSheet = Engine::tm.getTex("Alien3Hit");
	dieSheet = Engine::tm.getTex("Alien3Die");

	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);

	SpriteComponent::load();
}

void AlienSprite3::render()
{
	SpriteComponent::render();
}

void AlienSprite3::update(double dt)
{
	SpriteComponent::update(dt);
}

void AlienSprite3::playAttack()
{
	SpriteComponent::playAttack();
	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(880.0f, 150.0f);
	//sprite.setScale(0.6f, 0.6f);
}

void AlienSprite3::playHit()
{
	SpriteComponent::playHit();
	hitDelay = 0.5f;
	sprite.setPosition(1025.0f, 150.0f);
	//sprite.setScale(0.6f, 0.6f);

}

void AlienSprite3::playDie()
{
	SpriteComponent::playDie();
	sprite.setPosition(1080.0f, 150.0f);
	//sprite.setScale(0.6f, 0.6f);
}

void AlienSprite3::ResetAnim()
{
	SpriteComponent::ResetAnim();
	sheetRect = sf::IntRect(0, 0, hitSize.x, hitSize.y);
	sprite = sf::Sprite(hitSheet, sheetRect);
	sprite.setPosition(defaultPos);
	//sprite.setScale(0.6f, 0.6f);
}