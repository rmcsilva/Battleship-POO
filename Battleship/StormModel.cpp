#include "stdafx.h"
#include "StormModel.h"

const int StormModel::TURN_DURATION = 1;

StormModel::StormModel(std::vector<SeaModel*> affectedPositions) : EventModel(TURN_DURATION), affectedPositions(affectedPositions)
{
}


StormModel::~StormModel()
{
}

std::vector<SeaModel*> StormModel::getAffectedPositions() {return affectedPositions;}
std::vector<ShipModel*> StormModel::getSinkShips() {return sinkShips;}
std::vector<ShipModel*> StormModel::getStormSurvivors() { return stormSurvivors;}

void StormModel::setAffectedPositions(std::vector<SeaModel*> affectedPositions) {
	this->affectedPositions = affectedPositions;
}

void StormModel::setSinkShips(std::vector<ShipModel*> sinkShips) {
	this->sinkShips = sinkShips;
}

void StormModel::setStormSurvivors(std::vector<ShipModel*> stormSurvivors) {
	this->stormSurvivors = stormSurvivors;
}


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
	if (isOver())
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

StormModel* StormModel::clone(){
	return new StormModel(*this);
}
