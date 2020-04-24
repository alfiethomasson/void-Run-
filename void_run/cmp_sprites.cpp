#include "cmp_sprites.h"
#include "system_renderer.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Entity* p) 
	: inAttack{ false }, inHit{ false }, inDie{ false }, inRun{ false }, Component(p) {}

void SpriteComponent::load()
{
	animCounter = 0;
	animRowCounter = 0;
	ResetAnim();
}

void SpriteComponent::render()
{
	Renderer::queue(&sprite);
	for (auto &i : icons)
	{
		Renderer::queue(&i.sprite);
	}
}

void SpriteComponent::update(double dt)
{
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	for (auto b : icons)
	{
		if (b.box.contains(cursPos))
		{
			gameScene.UpdateDesctext(b.description, sf::Vector2f(b.sprite.getPosition().x + (b.sprite.getGlobalBounds().width / 2),
				b.sprite.getPosition().y));
		}
	}

	if (inAttack)
	{
		if (animClock.getElapsedTime().asSeconds() > animDelay)
		{
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
	if (inRun)
	{
		if (animClock.getElapsedTime().asSeconds() > animDelay)
		{
			if (animCounter < runSpriteNum)
			{
				if (animRowCounter <= 3)
				{
					if (animRowCounter == 3)
					{
						sheetRect.top += runSize.y;
						sheetRect.left = 0;
						animRowCounter = 0;
					}
					else
					{
						sheetRect.left += runSize.x;
						animRowCounter++;
					}
				}
				sprite.setTextureRect(sheetRect);
				animClock.restart();
				animCounter++;
			}
			else
			{
				gameScene.getCurrentRoom().setInactive();
				ResetAnim();
			}
		}
		sprite.move(sf::Vector2f(-1, 0));
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

void SpriteComponent::playRun()
{
	inRun = true;
	hitClock.restart();
	sheetRect = sf::IntRect(0, 0, runSize.x, runSize.y);
	sprite = sf::Sprite(runSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	animDelay = 0.05f;
}

void SpriteComponent::ResetAnim()
{
	inAttack = false;
	inHit = false;
	inDie = false;
	inRun = false;
	sheetRect = sf::IntRect(0, 0, attackSize.x, attackSize.y);
	sprite = sf::Sprite(attackSheet, sheetRect);
	animRowCounter = 0;
	animCounter = 0;

	sprite.setPosition(defaultPos);
}

void SpriteComponent::AddIcon(std::string texName, std::string desc, bool leftright)
{
	Icon tempIcon;
	tempIcon.sprite.setTexture(Engine::tm.getTex(texName));
	tempIcon.sprite.setScale(0.15f, 0.15f);
	if (leftright)
	{
		tempIcon.sprite.setPosition(1150, 100.0f);
	}
	else
	{
		tempIcon.sprite.setPosition(800.0f, 300.0f);
	}
	tempIcon.box = tempIcon.sprite.getGlobalBounds();
	tempIcon.description = desc;
	icons.push_back(tempIcon);
}

void SpriteComponent::RemoveIcon(int position)
{
	icons.erase(icons.begin() + position);
}
