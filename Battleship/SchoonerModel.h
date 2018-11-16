#pragma once
#include "ShipModel.h"
class SchoonerModel : public ShipModel
{
	const int MAX_SOLDIERS = 10;
	const int MAX_CAPACITY = 20;
	const int MAX_WATER = 100;
	const int MAX_MOVES = 1;
public:
	SchoonerModel(CellModel* position);
	~SchoonerModel();
	//TODO: Get Fish from Map cells
};

