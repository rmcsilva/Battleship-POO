#include "stdafx.h"
#include "SchoonerModel.h"


SchoonerModel::SchoonerModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, Owner::PLAYER, position)
{
}


SchoonerModel::~SchoonerModel()
{
}
