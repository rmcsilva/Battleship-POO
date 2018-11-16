#include "stdafx.h"
#include "SailboatModel.h"

//TODO: Lacks details
SailboatModel::SailboatModel(ShipOwner owner, CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, owner, position)
{
	
}


SailboatModel::~SailboatModel()
{
}

ShipModel::Type SailboatModel::getType() const {return ShipModel::Type::SAILBOAT;}

bool SailboatModel::stormAttack()
{
	//TODO: Complete
	int capacityThreshold = MAX_CAPACITY / 2;
	if (capacity > capacityThreshold)
	{
		//STORM_SINK_PROB_ABOVE_CAPACITY
	}else
	{
		//STORM_SINK_PROB_BELOW_CAPACITY
	}
	return false;
}
