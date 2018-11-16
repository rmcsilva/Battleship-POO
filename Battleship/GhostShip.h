#pragma once
#include "ShipModel.h"
class GhostShip : public ShipModel
{
public:
	GhostShip(CellModel* position);
	~GhostShip();

	Type getType() const override;
	bool stormAttack() override;
};

