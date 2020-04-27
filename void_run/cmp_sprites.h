#pragma once
#include "ecm.h"

struct Icon
{
	sf::Sprite sprite;
	sf::FloatRect box;
	std::string description;
};

class SpriteComponent : public Component {
protected:
	sf::Sprite sprite;
	sf::Texture attackSheet;
	sf::Texture hitSheet;
	sf::Texture dieSheet;
	sf::Texture runSheet;
	std::string attackName;
	std::string hitName;
	std::string dieName;
	std::string runName;

	sf::Vector2f attackSize;
	sf::Vector2f hitSize;
	sf::Vector2f dieSize;
	sf::Vector2f runSize;

	sf::IntRect sheetRect;

	sf::Vector2f defaultPos;

	int attackSpriteNum;
	int hitSpriteNum;
	int dieSpriteNum;
	int runSpriteNum;

	bool inAttack;
	bool inHit;
	bool inDie;
	bool inRun;
	float dieDelay;

	sf::Clock animClock;
	sf::Clock hitClock;
	float animDelay;
	float hitDelay;
	int animCounter;
	int animRowCounter;

	std::vector<Icon> icons;
	sf::Vector2f positionsRight[8];
	sf::Vector2f positionsLeft[8];

public:
	SpriteComponent() = delete;
	explicit SpriteComponent(Entity* p);

	void update(double dt) override;
	void render() override;
	void load();

	virtual void playAttack();
	virtual void playHit();
	virtual void playDie();
	virtual void playRun();
	virtual void ResetAnim();

	void AddIcon(std::string texName, std::string desc, bool leftright);
	void ChangeIcon(int position, std::string texname, std::string desc);
	void RemoveIcon(int position);
	void RemoveAllIcons();
};