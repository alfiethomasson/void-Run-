#include "cmp_sprites.h"

class PlayerSprite : public SpriteComponent {
private:

public:

	explicit PlayerSprite(Entity* p);
	PlayerSprite() = default;

	void update(double dt) override;
	void render() override;
	void load();

	void playAttack() override;
	void playHit() override;
	void playDie() override;

	void ResetAnim() override; 

};