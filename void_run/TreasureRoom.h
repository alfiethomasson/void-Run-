#pragma once
#include <iostream>
#include "Room.h"

class TreasureRoom : public Room {
private:
public:
	TreasureRoom() = default;
	~TreasureRoom() override = default;
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;

};