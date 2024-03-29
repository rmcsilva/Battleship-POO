#pragma once
#include "EventModel.h"
#include "ShipModel.h"
class ShipModel;

class RiotModel : public EventModel
{
	static const int TURN_DURATION;

	ShipModel* affectedShip;
	Navigation shipsNavigation;

public:
	RiotModel(ShipModel* affectedShip);
	~RiotModel();

	ShipModel* getAffectedShip();
	Navigation getShipsOldNavigation();

	void setAffectedShip(ShipModel* affectedShip);

	Type getType() override;
	bool executeEvent() override;

	RiotModel* clone() override;
};

