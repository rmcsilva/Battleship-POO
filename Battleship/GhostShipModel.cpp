#include "stdafx.h"
#include "GhostShipModel.h"

//TODO: Add values
GhostShipModel::GhostShipModel(CellModel* position) : ShipModel(100, 100, 100, 20, Owner::PLAYER, position)
{
}


GhostShipModel::~GhostShipModel()
{
}

ShipModel::Type GhostShipModel::getType() const {return ShipModel::Type::GHOST;}

bool GhostShipModel::stormAttack() {return false;}

std::string GhostShipModel::getAsString() const {return "S";}
