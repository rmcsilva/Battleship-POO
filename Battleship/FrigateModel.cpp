#include "stdafx.h"
#include "FrigateModel.h"


FrigateModel::FrigateModel(Owner owner, CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, owner, position)
{
}


FrigateModel::~FrigateModel()
{
}
