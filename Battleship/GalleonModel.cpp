#include "stdafx.h"
#include "GalleonModel.h"


GalleonModel::GalleonModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, ShipOwner::PLAYER, position)
{
}


GalleonModel::~GalleonModel()
{
}

ShipModel::Type GalleonModel::getType() const {return ShipModel::Type::GALLEON;}

bool GalleonModel::stormAttack()
{
	int soldiersLost = (soldiers * STORM_SOLDIERS_AFFECTED_PERCENTAGE) / 100;
	soldiers -= soldiersLost;

	//TODO: Sink probability
	return false;
}
