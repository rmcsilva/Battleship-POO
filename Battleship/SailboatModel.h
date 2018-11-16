#pragma once
#include "ShipModel.h"
class SailboatModel : public ShipModel
{
	const int MAX_SOLDIERS = 20;
	const int MAX_CAPACITY = 40;
	const int MAX_WATER = 200;
	//TODO: Change to 2 moves to test
	const int MAX_MOVES = 1;

public:
	SailboatModel(Owner owner, CellModel* position);
	~SailboatModel();
};

