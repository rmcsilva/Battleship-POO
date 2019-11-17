#pragma once
#include "ShipModel.h"
class GhostShipModel : public ShipModel
{
	static const int MAX_SOLDIERS;
	static const int MAX_CAPACITY;
	static const int MAX_WATER;
	static const int MAX_MOVES;
	static const int STORM_SOLDIERS_AFFECTED_PERCENTAGE;
	static const int STORM_SINK_PROB;
	static const int COUNTDOWN;
	int countdown;
public:
	GhostShipModel(CellModel* position);
	~GhostShipModel();

	bool canAttack();
	void updateCountdown();

	Type getType() const override;
	bool stormAttack() override;
	std::string getAsString() const override;

	GhostShipModel* clone() override;

	void shipsAutoMovement(GameController* gameController) override;
};

