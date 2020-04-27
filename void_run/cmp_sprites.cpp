#include "cmp_sprites.h"
#include "system_renderer.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Entity* p) 
	: inAttack{ false }, inHit{ false }, inDie{ false }, inRun{ false }, Component(p) {}

//Sets positions for icons and resets anim counters
void SpriteComponent::load()
{
	animCounter = 0;
	animRowCounter = 0;
	positionsRight[0] = sf::Vector2f(1600.0f, 200.0f);
	positionsRight[1] = sf::Vector2f(1650.0f, 200.0f);
	positionsRight[2] = sf::Vector2f(1700.0f, 200.0f);
	positionsRight[3] = sf::Vector2f(1600.0f, 250.0f);
	positionsRight[4] = sf::Vector2f(1650.0f, 250.0f);
	positionsRight[5] = sf::Vector2f(1700.0f, 250.0f);
	positionsRight[6] = sf::Vector2f(1600.0f, 300.0f);
	positionsRight[7] = sf::Vector2f(1650.0f, 300.0f);

	positionsLeft[0] = sf::Vector2f(150.0f, 200.0f);
	positionsLeft[1] = sf::Vector2f(200.0f, 200.0f);
	positionsLeft[2] = sf::Vector2f(250.0f, 200.0f);
	positionsLeft[3] = sf::Vector2f(150.0f, 250.0f);
	positionsLeft[4] = sf::Vector2f(200.0f, 250.0f);
	positionsLeft[5] = sf::Vector2f(250.0f, 250.0f);
	positionsLeft[6] = sf::Vector2f(150.0f, 300.0f);
	positionsLeft[7] = sf::Vector2f(200.0f, 300.0f);

	ResetAnim();
}


//Renders the main sprite and any icons
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
	//Gets curs pos in relation to window size
	Vector2i tempPos = sf::Mouse::getPosition(Engine::GetWindow());
	Vector2f cursPos = sf::Vector2f(tempPos);
	cursPos.x /= Engine::xMultiply;
	cursPos.y /= Engine::yMultiply;

	//Loops throuhg all icons, if any contains cursor then update tooltip to display what the icon is for
	for (auto b : icons)
	{
		if (b.box.contains(cursPos))
		{
			gameScene.UpdateDesctext(b.description, sf::Vector2f(b.sprite.getPosition().x + (b.sprite.getGlobalBounds().width / 2),
				b.sprite.getPosition().y));
		}
	}

	//If in attack animation
	if (inAttack)
	{
		if (animClock.getElapsedTime().asSeconds() > animDelay) // so the animation doesnt play super fast
		{
			if (animCounter < attackSpriteNum) // if there are still more animations before end of spritesheet
			{
				//Loops in rows of 4 to set sprite to each part of spritesheet, "playing" the animation
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
				//sets sprite to have texturerect
				sprite.setTextureRect(sheetRect);
				animClock.restart();
				animCounter++;
			}
			else
			{
				//Sets sprite to default position resets all other animation stuff
				ResetAnim();
			}
		}
	}
	if (inHit) // Same as Attack
	{
		if (hitClock.getElapsedTime().asSeconds() > hitDelay) //Checks if small hit delay has passed
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
	if (inRun) // same as attack
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
		sprite.move(sf::Vector2f(dt*100, 0));
	}
	if (inDie) // same as attack
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
					//Doesnt reset as player is dead
				}
			}
		}
	}
}

//starts to play attack by setting inAttack to true
void SpriteComponent::playAttack()
{
	inAttack = true;
	animDelay = 0.05f;
}

//Starts to play Hit animation by setting spritesheet to hit spritesheet and moving to appropriate place
void SpriteComponent::playHit()
{
	inHit = true;
	sheetRect = sf::IntRect(0, 0, hitSize.x, hitSize.y);
	sprite = sf::Sprite(hitSheet, sheetRect);
	hitClock.restart();

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	animDelay = 0.05f;
}

//Starts to play Die animation by setting spritesheet to death spritesheet and moving to appropriate place
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

//Starts to play Run animation by setting spritesheet to run spritesheet and moving to appropriate place
void SpriteComponent::playRun()
{
	inRun = true;
	hitClock.restart();
	sheetRect = sf::IntRect(0, 0, runSize.x, runSize.y);
	sprite = sf::Sprite(runSheet, sheetRect);

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	animDelay = 0.05f;
}

//Resets variables and sets sprite to default 
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

//Adds icon to the icon vector
void SpriteComponent::AddIcon(std::string texName, std::string desc, bool leftright)
{
	//Creates temp Icon using passed through texture
	Icon tempIcon;
	tempIcon.sprite.setTexture(Engine::tm.getTex(texName));
	tempIcon.sprite.setScale(0.15f, 0.15f);
	//if leftright = true then put icon on right of sprite
	if (leftright)
	{
		if (icons.size() == 0)
		{
			tempIcon.sprite.setPosition(positionsRight[0]);
		}
		else
		{
			tempIcon.sprite.setPosition(positionsRight[icons.size()]);
		}
	}
	else // put icon on left of sprite
	{
		if (icons.size() == 0)
		{
			tempIcon.sprite.setPosition(positionsLeft[0]);
		}
		else
		{
			tempIcon.sprite.setPosition(positionsLeft[icons.size()]);
		}
	}
	//updates icon box
	tempIcon.box = tempIcon.sprite.getGlobalBounds();
	tempIcon.description = desc;
	icons.push_back(tempIcon);
}

//Removes icon at specific position
void SpriteComponent::RemoveIcon(int position)
{
	icons.erase(icons.begin() + position);
}

//Removes all icons
void SpriteComponent::RemoveAllIcons()
{
	icons.clear();
}

//Changes the icon at certain position to new texture and description
void SpriteComponent::ChangeIcon(int position, std::string texname, std::string desc)
{
	icons.at(position).sprite.setTexture(Engine::tm.getTex(texname));
	icons.at(position).description = desc;
}