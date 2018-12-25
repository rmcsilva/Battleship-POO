#pragma once
#include "ShipModel.h"
class SchoonerModel : public ShipModel
{
	static const int MAX_SOLDIERS;
	static const int MAX_CAPACITY;
	static const int MAX_WATER;
	static const int MAX_MOVES;
	static const int STORM_LOSE_CARGO_PROB;
	static const int STORM_SINK_PROB;
public:
	SchoonerModel(CellModel* position);
	~SchoonerModel();
	//TODO: Get Fish from Map cells
	Type getType() const override;
	bool stormAttack() override;

	std::string getAsString() const override;

	SchoonerModel* clone() override;
};

