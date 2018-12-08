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

EventModel::Type RiotModel::getType() {return Type::RIOT;}

bool RiotModel::executeEvent()
{
	if (isOver())
	{
		affectedShip->setOwner(Owner::PLAYER);
		affectedShip->setNavigation(shipsNavigation);
		return false;
	}

	if (affectedShip->getOwner() == Owner::PLAYER)
	{
		affectedShip->setOwner(Owner::ENEMY);
		affectedShip->setNavigation(Navigation::AUTO);
	}

	incrementTurn();
	return true;
}
