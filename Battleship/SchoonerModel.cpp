#include "stdafx.h"
#include "SchoonerModel.h"

const int SchoonerModel::MAX_SOLDIERS = 10;
const int SchoonerModel::MAX_CAPACITY = 20;
const int SchoonerModel::MAX_WATER = 100;
const int SchoonerModel::MAX_MOVES = 1;
const int SchoonerModel::STORM_LOSE_CARGO_PROB = 20;
const int SchoonerModel::STORM_SINK_PROB = 35;

SchoonerModel::SchoonerModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, Owner::PLAYER, position)
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
