#include "stdafx.h"
#include "GhostShipModel.h"

//TODO: Add values
GhostShipModel::GhostShipModel(CellModel* position) : ShipModel(100, 100, 100, 80, Owner::PLAYER, position)
{
}


GhostShipModel::~GhostShipModel()
{
}

ShipModel::Type GhostShipModel::getType() const {return ShipModel::Type::GHOST;}

bool GhostShipModel::stormAttack() {return true;}

std::string GhostShipModel::getAsString() const {return "S";}

GhostShipModel* GhostShipModel::clone() {
	return new GhostShipModel(*this);
}
