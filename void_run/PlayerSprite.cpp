#include "PlayerSprite.h"
#include "Game.h"

PlayerSprite::PlayerSprite(Entity* p)
	: SpriteComponent{ p } {}

void PlayerSprite::load()
{
	defaultPos = sf::Vector2f(700.0f, 250.0f);

	attackSize = sf::Vector2f(919, 821);
	hitSize = sf::Vector2f(620, 893);
	dieSize = sf::Vector2f(639, 1031);
	runSize = sf::Vector2f(864, 764);

	attackSpriteNum = 16;
	hitSpriteNum = 7;
	dieSpriteNum = 20;
	runSpriteNum = 23;

	hitDelay = 0.5f;
	attackSheet = Engine::tm.getTex("PlayerAttack");
	hitSheet = Engine::tm.getTex("PlayerHit");
	dieSheet = Engine::tm.getTex("PlayerDie");
	runSheet = Engine::tm.getTex("PlayerRun");

	sheetRect = sf::IntRect(0, 0, 460, 411);
	sprite = sf::Sprite(attackSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);
	sprite.setScale(-0.6f, 0.6f);

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
	sprite.setPosition(412.0f, 205.0f);
	sprite.setScale(-0.6f, 0.6f);

}

void PlayerSprite::playDie()
{
	SpriteComponent::playDie();
	sprite.setPosition(412.0f, 230.0f);
	sprite.setScale(-0.6f, 0.6f);
}

void PlayerSprite::playRun()
{
	SpriteComponent::playRun();
	sprite.setPosition(360.0f, 300.0f);
	sprite.setScale(0.6f, 0.6f);

}

void PlayerSprite::ResetAnim()
{
	SpriteComponent::ResetAnim();
	sprite.setScale(-0.6f, 0.6f);
}