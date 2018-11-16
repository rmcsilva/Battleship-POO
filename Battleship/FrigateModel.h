#pragma once
#include "ShipModel.h"
class FrigateModel : public ShipModel
{
	const int MAX_SOLDIERS = 50;
	const int MAX_CAPACITY = 0;
	const int MAX_WATER = 500;
	//TODO: Change to 2 
	const int MAX_MOVES = 1;
public:
	FrigateModel(Owner owner, CellModel* position);
	~FrigateModel();
};

