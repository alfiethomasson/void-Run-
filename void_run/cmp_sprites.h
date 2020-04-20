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
public:
	SpriteComponent() = delete;
	explicit SpriteComponent(Entity* p, sf::Vector2f pos,
		std::string attack, int attacknum, sf::Vector2f attackS,
		std::string hit, int hitNum, sf::Vector2f hitS, 
		std::string die, int dieNum, sf::Vector2f dieS);

	void update(double dt) override;
	void render() override;
	void load();

	void playAttack();
	void playHit();
	void playDie();
	void ResetAnim();

};