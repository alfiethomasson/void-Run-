#include "cmp_special.h"
#include "Game.h"

class LaserBurst : public SpecialItem{
protected:

public:
	explicit LaserBurst(Entity* p);
	LaserBurst() = delete;

	void update(double dt) override;
	void load();
	void doEffect() override;

};