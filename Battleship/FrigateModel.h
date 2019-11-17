#pragma once
#include "ShipModel.h"
class FrigateModel : public ShipModel
{
	static const int MAX_SOLDIERS;
	static const int MAX_CAPACITY;
	static const int MAX_WATER;
	static const int MAX_MOVES;
	static const int STORM_SOLDIERS_AFFECTED_PERCENTAGE;
	static const int STORM_SINK_PROB;
public:
	FrigateModel(Owner owner, CellModel* position);
	~FrigateModel();

	Type getType() const override;
	bool stormAttack() override;
	std::string getAsString() const override;

	FrigateModel* clone() override;


	void shipsAutoMovement(GameController* gameController) override;
};

