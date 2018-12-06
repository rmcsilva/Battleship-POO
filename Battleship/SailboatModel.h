#pragma once
#include "ShipModel.h"
class SailboatModel : public ShipModel
{
	static const int MAX_SOLDIERS;
	static const int MAX_CAPACITY;
	static const int MAX_WATER;
	static const int MAX_MOVES;
	static const int STORM_SINK_PROB_ABOVE_CAPACITY;
	static const int STORM_SINK_PROB_BELOW_CAPACITY;

public:
	SailboatModel(Owner owner, CellModel* position);
	~SailboatModel();

	Type getType() const override;
	bool stormAttack() override;
	std::string getAsString() const override;
};

