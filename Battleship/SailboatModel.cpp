#include "stdafx.h"
#include "SailboatModel.h"

const int SailboatModel::MAX_SOLDIERS = 20;
const int SailboatModel::MAX_CAPACITY = 40;
const int SailboatModel::MAX_WATER = 200;
//TODO: Change to 1 depending on difficulty
const int SailboatModel::MAX_MOVES = 2;
const int SailboatModel::STORM_SINK_PROB_ABOVE_CAPACITY = 35;
const int SailboatModel::STORM_SINK_PROB_BELOW_CAPACITY = 20;

SailboatModel::SailboatModel(Owner owner, CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, owner, position)
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

std::string SailboatModel::getAsString() const {return "V";}
