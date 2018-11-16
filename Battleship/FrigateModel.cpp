#include "stdafx.h"
#include "FrigateModel.h"


FrigateModel::FrigateModel(ShipOwner owner, CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, owner, position)
{
}


FrigateModel::~FrigateModel()
{
}

ShipModel::Type FrigateModel::getType() const {return ShipModel::Type::FRIGATE;}

bool FrigateModel::stormAttack()
{
	int soldiersLost = (soldiers * STORM_SOLDIERS_AFFECTED_PERCENTAGE) / 100;
	soldiers -= soldiersLost;
	return false;
}
