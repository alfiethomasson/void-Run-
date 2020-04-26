#pragma once
#include "SpecialAbility.h"

class SpecialAbility;
class CombatUI;

class AbilityManager : public Component {
protected:
	std::vector<std::shared_ptr<SpecialAbility>> specials;
	std::shared_ptr<BasePlayerComponent> player;
	int maxSpecials;
	CombatUI& combatUI;
public:

	explicit AbilityManager(Entity* p, int maxSpecial, CombatUI *ui);
	AbilityManager() = delete;

	void update(double dt) override;
	void render() override {};
	void Load();

	void combatCheck(sf::Vector2f cursPos);
	void resetAbility();
	void StartTurnCheck();
	bool addAbility(std::shared_ptr<SpecialAbility> ability);
	void removeAbility(int position);

	std::vector<std::shared_ptr<SpecialAbility>> getSpecials();

};