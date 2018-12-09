#pragma once
#include "EventModel.h"
#include "ShipModel.h"

class MermaidModel : public EventModel
{
	static const int TURN_DURATION;
	static const int SOLDIERS_LOST_PERCENTAGE;

	ShipModel* affectedShip = nullptr;

public:
	MermaidModel(ShipModel* affectedShip);

	~MermaidModel();

	ShipModel* getAffectedShip();

	Type getType() override;
	bool executeEvent() override;
};

