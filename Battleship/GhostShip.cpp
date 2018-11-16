#include "stdafx.h"
#include "GhostShip.h"


GhostShip::GhostShip(CellModel* position) : ShipModel(100, 100, 100, 100, Owner::PLAYER, position)
{
}


GhostShip::~GhostShip()
{
}
