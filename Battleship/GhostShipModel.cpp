#include "stdafx.h"
#include "GhostShipModel.h"

const int GhostShipModel::MAX_SOLDIERS = 300;
const int GhostShipModel::MAX_CAPACITY = 0;
const int GhostShipModel::MAX_WATER = 1;
const int GhostShipModel::MAX_MOVES = 1;
const int GhostShipModel::COUNTDOWN = 5;

GhostShipModel::GhostShipModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, Owner::PLAYER, position)
{
	countdown = COUNTDOWN;
}


GhostShipModel::~GhostShipModel()
{
}

bool GhostShipModel::canAttack()
{
	return countdown == COUNTDOWN;
}

void GhostShipModel::updateCountdown()
{
	countdown--;
	if (countdown == 0) countdown = COUNTDOWN;
}

ShipModel::Type GhostShipModel::getType() const {return ShipModel::Type::GHOST;}

bool GhostShipModel::stormAttack() {return true;}

std::string GhostShipModel::getAsString() const {return "S";}

GhostShipModel* GhostShipModel::clone() {
	return new GhostShipModel(*this);
}

void GhostShipModel::shipsAutoMovement(GameController* gameController)
{
}
