#pragma once
#include "ShipModel.h"
class FrigateModel : public ShipModel
{
	const int MAX_SOLDIERS = 50;
	const int MAX_CAPACITY = 0;
	const int MAX_WATER = 500;
	//TODO: Change to 2 
	const int MAX_MOVES = 1;
	const int STORM_SOLDIERS_AFFECTED_PERCENTAGE = 15;
	const int STORM_SINK_PROB = 20;
public:
	FrigateModel(ShipOwner owner, CellModel* position);
	~FrigateModel();

	Type getType() const override;
	bool stormAttack() override;
};

