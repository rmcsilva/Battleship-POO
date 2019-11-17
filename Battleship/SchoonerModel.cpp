#include "stdafx.h"
#include "SchoonerModel.h"
#include "GameController.h"

const int SchoonerModel::MAX_SOLDIERS = 10;
const int SchoonerModel::MAX_CAPACITY = 20;
const int SchoonerModel::MAX_WATER = 100;
const int SchoonerModel::MAX_MOVES = 1;
const int SchoonerModel::STORM_LOSE_CARGO_PROB = 20;
const int SchoonerModel::STORM_SINK_PROB = 35;

SchoonerModel::SchoonerModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, Owner::PLAYER, position)
{
}


SchoonerModel::~SchoonerModel()
{
}

ShipModel::Type SchoonerModel::getType() const {return ShipModel::Type::SCHOONER;}

bool SchoonerModel::stormAttack()
{
	int random = rand() % 100;

	if (random < 20) empyShipCargo();

	random = rand() % 100;

	if (random < 35) return false;

	return true;
}

std::string SchoonerModel::getAsString() const {return "E";}

SchoonerModel* SchoonerModel::clone() {
	return new SchoonerModel(*this);
}

void SchoonerModel::shipsAutoMovement(GameController* gameController)
{
	const int maxWater = getMaxWater();
	const int percentageWater = maxWater * getWater() / 100;

	//Checks if ships needs to go to port
	if (!canAddToShipCargo(1) || percentageWater <= 25) {
		if (!gameController->getFriendlyPorts().empty()) {
			setGoTo((CellModel*)gameController->getFriendlyPorts().at(0));
			gameController->orderShipMovement(this);
		}
	} else {
		//Checks surrouding sea cells for fish
		for (auto seaCell : gameController->getSurroundingSeaCellsInRange2(getPosition())) {
			if (seaCell->hasFish()) {
				if (gameController->canMoveToCell((CellModel*)seaCell)) {
					setGoTo((CellModel*)seaCell);
					gameController->orderShipMovement(this);
					return;
				}
			}
		}
		gameController->generateRandomMove(getPosition());
	}
}
