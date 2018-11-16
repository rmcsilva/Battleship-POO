#pragma once
#include "ShipModel.h"
class GalleonModel : public ShipModel
{
	const int MAX_SOLDIERS = 40;
	const int MAX_CAPACITY = 70;
	const int MAX_WATER = 400;
	const int MAX_MOVES = 1;
	const int STORM_SOLDIERS_AFFECTED_PERCENTAGE = 10;
	const int STORM_SINK_PROB = 40;
public:
	GalleonModel(CellModel* position);
	~GalleonModel();

	Type getType() const override;
	bool stormAttack() override;
};

