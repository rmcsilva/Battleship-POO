#include "stdafx.h"
#include "LullModel.h"

const int LullModel::TURN_DURATION = 3;
const int LullModel::GOLD_BONUS = 100;

LullModel::LullModel(std::vector<SeaModel*> affectedPositions, int *playerCoins) : EventModel(TURN_DURATION), playerCoins(playerCoins), affectedPositions(affectedPositions)
{
}


LullModel::~LullModel()
{
}

std::vector<SeaModel*> LullModel::getAffectedPositions() const {return affectedPositions;}

EventModel::Type LullModel::getType() {return Type::LULL;}

bool LullModel::executeEvent()
{
	if (isOver())
	{
		*playerCoins += GOLD_BONUS;
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
			
			if (seaCell->hasFish()) seaCell->catchFish();
		}
	}

	incrementTurn();

	return true;
}
