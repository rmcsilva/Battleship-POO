#include "stdafx.h"
#include "RiotModel.h"

const int RiotModel::TURN_DURATION = 4;

RiotModel::RiotModel(ShipModel* affectedShip) : EventModel(TURN_DURATION), affectedShip(affectedShip)
{
	shipsNavigation = affectedShip->getNavigation();
}


RiotModel::~RiotModel()
{
}

ShipModel* RiotModel::getAffectedShip() {return affectedShip;}

Navigation RiotModel::getShipsOldNavigation() {return shipsNavigation;}

void RiotModel::setAffectedShip(ShipModel* affectedShip) {this->affectedShip = affectedShip;}

EventModel::Type RiotModel::getType() {return Type::RIOT;}

bool RiotModel::executeEvent()
{
	if (isOver())
		return false;

	if (affectedShip==nullptr) return false;

	incrementTurn();
	return true;
}

RiotModel* RiotModel::clone() {
	return new RiotModel(*this);
}
