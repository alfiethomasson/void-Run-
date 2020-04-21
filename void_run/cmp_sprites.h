#pragma once
#include "ecm.h"

class SpriteComponent : public Component {
protected:
	sf::Sprite sprite;
	sf::Texture attackSheet;
	sf::Texture hitSheet;
	sf::Texture dieSheet;

	std::string attackName;
	std::string hitName;
	std::string dieName;

	sf::Vector2f attackSize;
	sf::Vector2f hitSize;
	sf::Vector2f dieSize;

	sf::IntRect sheetRect;

	sf::Vector2f defaultPos;

	int attackSpriteNum;
	int hitSpriteNum;
	int dieSpriteNum;

	bool inAttack;
	bool inHit;
	bool inDie;
	float dieDelay;

	sf::Clock animClock;
	sf::Clock hitClock;
	float animDelay;
	float hitDelay;
	int animCounter;
	int animRowCounter;

	std::vector<sf::Sprite> icons;
public:
	SpriteComponent() = delete;
	explicit SpriteComponent(Entity* p);

	void update(double dt) override;
	void render() override;
	void load();

	virtual void playAttack();
	virtual void playHit();
	virtual void playDie();
	virtual void ResetAnim();

	void AddIcon(std::string texName, std::string desc, bool leftright);
	void RemoveIcon(int position);
};