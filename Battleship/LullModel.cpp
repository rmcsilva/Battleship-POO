#include "stdafx.h"
#include "LullModel.h"

const int LullModel::TURN_DURATION = 3;
const int LullModel::GOLD_BONUS = 100;

LullModel::LullModel(std::vector<SeaModel*> affectedPositions) : EventModel(TURN_DURATION), affectedPositions(affectedPositions)
{
}


LullModel::~LullModel()
{
}

std::vector<SeaModel*> LullModel::getAffectedPositions() const {return affectedPositions;}

int LullModel::getTotalGoldBonus() {return affectedShips.size() * GOLD_BONUS;}

void LullModel::addAffectedShip(ShipModel* ship)
{
	if (ship->getOwner()==Owner::ENEMY)
	 return;

	for (auto affectedShip : affectedShips)
	{
		if (ship==affectedShip)
			return;
	}
	affectedShips.push_back(ship);
}

EventModel::Type LullModel::getType() {return Type::LULL;}

bool LullModel::executeEvent()
{
	if (isOver())
	{
		return false;
	}

	for (SeaModel* seaCell : affectedPositions)
	{
		if (seaCell->hasShip())
		{
			ShipModel* affectedShip = seaCell->getShip();
			//Blocks ship movement and consumes water
			affectedShip->blockShipMovement();
			affectedShip->navigationCost();

			addAffectedShip(affectedShip);
			
			if (seaCell->hasFish()) seaCell->catchFish();
		}
	}

	incrementTurn();
	return true;
}
