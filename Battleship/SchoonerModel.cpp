#include "stdafx.h"
#include "SchoonerModel.h"


SchoonerModel::SchoonerModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, ShipOwner::PLAYER, position)
{
}


SchoonerModel::~SchoonerModel()
{
}

ShipModel::Type SchoonerModel::getType() const {return ShipModel::Type::SCHOONER;}

bool SchoonerModel::stormAttack()
{
	//TODO: Complete, generete two random numbers check conditions for each
	//STORM_LOSE_CARGO_PROB
	//STORM_SINK_PROB
	return false;
}
