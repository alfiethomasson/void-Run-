#include "cmp_sprites.h"

class AlienSprite1 : SpriteComponent {
private:

public:

	AlienSprite1();
	~AlienSprite1() = default;

	void update(double dt) override;
	void render() override;
	void load();

};