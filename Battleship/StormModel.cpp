#include "stdafx.h"
#include "StormModel.h"

const int StormModel::TURN_DURATION = 1;

StormModel::StormModel(std::vector<SeaModel*> affectedPositions) : EventModel(TURN_DURATION), affectedPositions(affectedPositions)
{
}


StormModel::~StormModel()
{
}

std::vector<ShipModel*> StormModel::getSinkShips() const {return sinkShips;}

void StormModel::addShipToSink(ShipModel* shipToSink)
{
	//Checks if sink survived in other rounds
	for (int i = 0; i < stormSurvivors.size(); ++i)
	{
		if (stormSurvivors.at(i)==shipToSink)
		{
			stormSurvivors.erase(stormSurvivors.begin() + i);
			break;
		}
	}

	sinkShips.push_back(shipToSink);
}

EventModel::Type StormModel::getType() {return Type::STORM;}

bool StormModel::executeEvent()
{
	if (isOver())  // NOLINT(readability-simplify-boolean-expr)
	{
		for (ShipModel* stormSurvivor : stormSurvivors) {
			stormSurvivor->refillWater();
		}
		return false;
	}

	for (SeaModel* affectedPosition : affectedPositions)
	{
		if (affectedPosition->hasShip())
		{
			ShipModel* affectedShip = affectedPosition->getShip();

			if (affectedShip->stormAttack())
				sinkShips.push_back(affectedShip);
			else
				addShipToSink(affectedShip);
		}
	}

	incrementTurn();
	return true;
}
