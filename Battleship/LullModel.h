#pragma once
#include "EventModel.h"
#include "SeaModel.h"

class LullModel : public EventModel
{
	static const int TURN_DURATION;
	static const int GOLD_BONUS;
	std::vector<SeaModel*> affectedPositions;
	std::vector<ShipModel*> affectedShips;

public:
	LullModel(std::vector<SeaModel*> affectedPositions);
	~LullModel();

	std::vector<SeaModel*> getAffectedPositions() const;

	int getTotalGoldBonus();

	void addAffectedShip(ShipModel* ship);
	Type getType() override;
	bool executeEvent() override;
};

