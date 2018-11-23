#pragma once
#include "ShipModel.h"
class GhostShipModel : public ShipModel
{
public:
	GhostShipModel(CellModel* position);
	~GhostShipModel();

	Type getType() const override;
	bool stormAttack() override;
};

