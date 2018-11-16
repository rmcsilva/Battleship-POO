#pragma once
#include "ShipModel.h"
class SailboatModel : public ShipModel
{
	const int MAX_SOLDIERS = 20;
	const int MAX_CAPACITY = 40;
	const int MAX_WATER = 200;
	//TODO: Change to 2 moves to test
	const int MAX_MOVES = 1;
	const int STORM_SINK_PROB_ABOVE_CAPACITY = 35;
	const int STORM_SINK_PROB_BELOW_CAPACITY = 20;

public:
	SailboatModel(ShipOwner owner, CellModel* position);
	~SailboatModel();

	Type getType() const override;
	bool stormAttack() override;
};

