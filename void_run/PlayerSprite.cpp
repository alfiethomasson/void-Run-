#include "PlayerSprite.h"
#include "Game.h"

PlayerSprite::PlayerSprite(Entity* p)
	: SpriteComponent{ p } {}

void PlayerSprite::load()
{
	defaultPos = sf::Vector2f(600.0f, 120.0f);

	attackSize = sf::Vector2f(460, 411);
	hitSize = sf::Vector2f(310, 447);
	dieSize = sf::Vector2f(320, 516);

	attackSpriteNum = 16;
	hitSpriteNum = 7;
	dieSpriteNum = 20;

	hitDelay = 0.5f;
	attackSheet = gameScene.tm.getTex("PlayerAttack");
	hitSheet = gameScene.tm.getTex("PlayerHit");
	dieSheet = gameScene.tm.getTex("PlayerDie");

	sheetRect = sf::IntRect(0, 0, 460, 411);
	sprite = sf::Sprite(attackSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);
	sprite.setScale(-1.0f, 1.0f);

	SpriteComponent::load();
}

void PlayerSprite::render()
{
	SpriteComponent::render();
}

void PlayerSprite::update(double dt)
{
	//std::cout << "PLAYER - " << animDelay;
	SpriteComponent::update(dt);
}

void PlayerSprite::playAttack()
{
	SpriteComponent::playAttack();
}

void PlayerSprite::playHit()
{
	SpriteComponent::playHit();
	sprite.setPosition(360.0f, 80.0f);
	sprite.setScale(-1.0f, 1.0f);

}

void PlayerSprite::playDie()
{
	SpriteComponent::playDie();
	sprite.setPosition(360.0f, 100.0f);
	sprite.setScale(-1.0f, 1.0f);
}

void PlayerSprite::ResetAnim()
{
	SpriteComponent::ResetAnim();
	sprite.setScale(-1.0f, 1.0f);
}