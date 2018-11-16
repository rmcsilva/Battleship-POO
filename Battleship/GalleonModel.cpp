#include "stdafx.h"
#include "GalleonModel.h"


GalleonModel::GalleonModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, Owner::PLAYER, position)
{
}


GalleonModel::~GalleonModel()
{
}
