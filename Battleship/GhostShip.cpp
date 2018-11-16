#include "stdafx.h"
#include "GhostShip.h"


GhostShip::GhostShip(CellModel* position) : ShipModel(100, 100, 100, 100, ShipOwner::PLAYER, position)
{
}


GhostShip::~GhostShip()
{
}

ShipModel::Type GhostShip::getType() const {return ShipModel::Type::GHOST;}

bool GhostShip::stormAttack()
{
	return false;
}
