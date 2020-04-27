#include "PlayerSprite.h"
#include "Game.h"

PlayerSprite::PlayerSprite(Entity* p)
	: SpriteComponent{ p } {}

void PlayerSprite::load()
{
	//Sets default position
	defaultPos = sf::Vector2f(700.0f, 250.0f);

	//Sets size of sliced sprites in spritesheet
	attackSize = sf::Vector2f(919, 821);
	hitSize = sf::Vector2f(620, 893);
	dieSize = sf::Vector2f(639, 1031);
	runSize = sf::Vector2f(864, 764);

	//sets number of sprites in spritesheet
	attackSpriteNum = 16;
	hitSpriteNum = 7;
	dieSpriteNum = 20;
	runSpriteNum = 23;

	//sets hit delay
	hitDelay = 0.5f;
	//assigns spritesheets
	attackSheet = Engine::tm.getTex("PlayerAttack");
	hitSheet = Engine::tm.getTex("PlayerHit");
	dieSheet = Engine::tm.getTex("PlayerDie");
	runSheet = Engine::tm.getTex("PlayerRun");

	//sets default sheet
	sheetRect = sf::IntRect(0, 0, 460, 411);
	sprite = sf::Sprite(attackSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);
	sprite.setScale(-0.6f, 0.6f);

	SpriteComponent::load();
}

//calls base render
void PlayerSprite::render()
{
	SpriteComponent::render();
}

//calls base update
void PlayerSprite::update(double dt)
{
	SpriteComponent::update(dt);
}

//calls base attack
void PlayerSprite::playAttack()
{
	SpriteComponent::playAttack();
}

//updates position and calls base hit
void PlayerSprite::playHit()
{
	SpriteComponent::playHit();
	sprite.setPosition(412.0f, 205.0f);
	sprite.setScale(-0.6f, 0.6f);

}

//updates position and calls base die
void PlayerSprite::playDie()
{
	SpriteComponent::playDie();
	sprite.setPosition(412.0f, 230.0f);
	sprite.setScale(-0.6f, 0.6f);
}

//updates position and calls base run
void PlayerSprite::playRun()
{
	SpriteComponent::playRun();
	sprite.setPosition(360.0f, 300.0f);
	sprite.setScale(0.6f, 0.6f);

}

//resets sprite by calling base resetanim
void PlayerSprite::ResetAnim()
{
	SpriteComponent::ResetAnim();
	sprite.setScale(-0.6f, 0.6f);
}