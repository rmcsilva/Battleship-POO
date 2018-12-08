#pragma once
#include "EventModel.h"
#include "ShipModel.h"
#include "SeaModel.h"

class StormModel : public EventModel
{
	static const int TURN_DURATION;

	std::vector<SeaModel*> affectedPositions;
	std::vector<ShipModel*> stormSurvivors;
	std::vector<ShipModel*> sinkShips;

public:
	StormModel(std::vector<SeaModel*> affectedPositions);
	~StormModel();

	std::vector<ShipModel*> getSinkShips() const;

	void addShipToSink(ShipModel* shipToSink);

	Type getType() override;
	bool executeEvent() override;


};

