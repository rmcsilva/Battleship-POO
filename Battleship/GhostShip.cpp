#include "stdafx.h"
#include "GhostShip.h"

//TODO: Add values
GhostShip::GhostShip(CellModel* position) : ShipModel(100, 100, 100, 100, Owner::PLAYER, position)
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
