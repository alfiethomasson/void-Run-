#include "cmp_sprites.h"
#include "system_renderer.h"

SpriteComponent::SpriteComponent(Entity* p) 
	: inAttack{ false }, inHit{ false }, inDie{ false }, Component(p) {}

void SpriteComponent::load()
{
	animCounter = 0;
	animRowCounter = 0;
	ResetAnim();
}

void SpriteComponent::render()
{
	Renderer::queue(&sprite);
}

void SpriteComponent::update(double dt)
{
	if (inAttack)
	{
		if (animClock.getElapsedTime().asSeconds() > animDelay)
		{
			std::cout << "In attack anim part: " << animCounter << "\n";
			if (animCounter < attackSpriteNum)
			{
				if (animRowCounter <= 3)
				{
					if (animRowCounter == 3)
					{
						sheetRect.top += attackSize.y;
						sheetRect.left = 0;
						animRowCounter = 0;
					}
					else
					{
						sheetRect.left += attackSize.x;
						animRowCounter++;
					}
				}
				sprite.setTextureRect(sheetRect);
				animClock.restart();
				animCounter++;
			}
			else
			{
				ResetAnim();
			}
		}
	}
	if (inHit)
	{
		if (hitClock.getElapsedTime().asSeconds() > hitDelay)
		{
			if (animClock.getElapsedTime().asSeconds() > animDelay)
			{
				std::cout << "In hit anim part: " << animCounter << "\n";
				if (animCounter < hitSpriteNum)
				{
					if (animRowCounter <= 3)
					{
						if (animRowCounter == 3)
						{
							sheetRect.top += hitSize.y;
							sheetRect.left = 0;
							animRowCounter = 0;
						}
						else
						{
							sheetRect.left += hitSize.x;
							animRowCounter++;
						}
					}
					sprite.setTextureRect(sheetRect);
					animClock.restart();
					animCounter++;
				}
				else
				{
					ResetAnim();
				}
			}
		}
	}
	if (inDie)
	{
		if (hitClock.getElapsedTime().asSeconds() > dieDelay)
		{

			if (animClock.getElapsedTime().asSeconds() > animDelay)
			{
				if (animCounter < dieSpriteNum)
				{
					if (animRowCounter <= 3)
					{
						if (animRowCounter == 3)
						{
							sheetRect.top += dieSize.y;
							sheetRect.left = 0;
							animRowCounter = 0;
						}
						else
						{
							sheetRect.left += dieSize.x;
							animRowCounter++;
						}
					}
					sprite.setTextureRect(sheetRect);
					animClock.restart();
					animCounter++;
				}
				else
				{
					//	ResetAnim();
				}
			}
		}
	}
}

void SpriteComponent::playAttack()
{
	inAttack = true;
	animDelay = 0.05f;
}

void SpriteComponent::playHit()
{
	inHit = true;
	sheetRect = sf::IntRect(0, 0, hitSize.x, hitSize.y);
	sprite = sf::Sprite(hitSheet, sheetRect);
	hitClock.restart();

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	animDelay = 0.05f;
}

void SpriteComponent::playDie()
{
	inDie = true;
	hitClock.restart();
	//auto tempSprite = sprite.getPosition().x; //+ (sprite.getGlobalBounds().width / 2);
	sheetRect = sf::IntRect(0, 0, dieSize.x, dieSize.y);
	sprite = sf::Sprite(dieSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	animDelay = 0.05f;
}

void SpriteComponent::ResetAnim()
{
	inAttack = false;
	inHit = false;
	inDie = false;
	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);
	animRowCounter = 0;
	animCounter = 0;

	sprite.setPosition(defaultPos);
}
