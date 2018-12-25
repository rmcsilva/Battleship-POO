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

	std::vector<SeaModel*> getAffectedPositions();
	std::vector<ShipModel*> getSinkShips();
	std::vector<ShipModel*> getStormSurvivors();

	void setAffectedPositions(std::vector<SeaModel*> affectedPositions);
	void setSinkShips(std::vector<ShipModel*> sinkShips);
	void setStormSurvivors(std::vector<ShipModel*> stormSurvivors);

	void addShipToSink(ShipModel* shipToSink);

	Type getType() override;
	bool executeEvent() override;

	StormModel* clone() override;
};

