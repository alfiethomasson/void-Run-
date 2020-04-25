#pragma once
#include "SpecialAbility.h"

class SpecialAbility;

class AbilityManager : public Component {
protected:
	std::vector<std::shared_ptr<SpecialAbility>> specials;
	int maxSpecials;
public:

	explicit AbilityManager(Entity* p, int maxSpecial);
	AbilityManager() = delete;

	void update(double dt) override;
	void render() override {};
	void Load();

	void combatCheck();
	bool addAbility(std::shared_ptr<SpecialAbility> ability);
	void removeAbility(int position);

	std::vector<std::shared_ptr<SpecialAbility>> getSpecials();

};