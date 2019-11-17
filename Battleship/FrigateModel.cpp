#include "stdafx.h"
#include "FrigateModel.h"
#include "GameController.h"

const int FrigateModel::MAX_SOLDIERS = 50;
const int FrigateModel::MAX_CAPACITY = 0;
const int FrigateModel::MAX_WATER = 500;
const int FrigateModel::MAX_MOVES = 2;
const int FrigateModel::STORM_SOLDIERS_AFFECTED_PERCENTAGE = 15;
const int FrigateModel::STORM_SINK_PROB = 20;

FrigateModel::FrigateModel(Owner owner, CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, owner, position)
{
}


FrigateModel::~FrigateModel()
{
}

ShipModel::Type FrigateModel::getType() const {return ShipModel::Type::FRIGATE;}

bool FrigateModel::stormAttack()
{
	int soldiersLost = (getSoldiers() * STORM_SOLDIERS_AFFECTED_PERCENTAGE) / 100;
	removeSoldiers(soldiersLost);

	int random = rand() % 100;

	if(random < 20) return false;

	return true;
}

std::string FrigateModel::getAsString() const {return "F";}

FrigateModel* FrigateModel::clone() {
	return new FrigateModel(*this);
}

void FrigateModel::shipsAutoMovement(GameController* gameController)
{
	if (getOwner() == Owner::PLAYER)
	{
		for (auto enemyShip : gameController->getEnemyShips()) {
			setGoTo(enemyShip->getPosition());
			gameController->orderShipMovement(this);
			return;
		}
		for (auto friendlyShip : gameController->getFriendlyShips()) {
			if (friendlyShip->getType() == ShipModel::Type::SCHOONER || friendlyShip->getType() == ShipModel::Type::GALLEON) {
				setGoTo(friendlyShip->getPosition());
				gameController->orderShipMovement(this);
				return;
			}
		}
	}
	else {
		for (auto friendlyShip : gameController->getFriendlyShips()) {
			setGoTo(friendlyShip->getPosition());
			gameController->orderShipMovement(this);
			return;
		}
		gameController->lostShipMovement(this);
	}
}
