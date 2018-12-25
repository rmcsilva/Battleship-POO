#pragma once
#include "ShipModel.h"

class GalleonModel : public ShipModel
{
	static const int MAX_SOLDIERS;
	static const int MAX_CAPACITY;
	static const int MAX_WATER;
	static const int MAX_MOVES;
	static const int STORM_SOLDIERS_AFFECTED_PERCENTAGE;
	static const int STORM_SINK_PROB;

public:
	GalleonModel(CellModel* position);
	~GalleonModel();

	Type getType() const override;
	bool stormAttack() override;
	std::string getAsString() const override;

	GalleonModel* clone() override;
};

