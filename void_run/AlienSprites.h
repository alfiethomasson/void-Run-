#pragma once;
#include "cmp_sprites.h"

class AlienSprite1 : public SpriteComponent {
private:
public:

	explicit AlienSprite1(Entity* p);
	AlienSprite1() = default;

	void update(double dt) override;
	void render() override;
	void load();

	void playAttack() override;
	void playHit() override;
	void playDie() override;

	void ResetAnim() override;

};