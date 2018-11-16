#pragma once
#include "ShipModel.h"
class GalleonModel : public ShipModel
{
	const int MAX_SOLDIERS = 40;
	const int MAX_CAPACITY = 70;
	const int MAX_WATER = 400;
	const int MAX_MOVES = 1;
public:
	GalleonModel(CellModel* position);
	~GalleonModel();
};

