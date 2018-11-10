#pragma once
class ShipModel
{
	int id; //Unique id
	int price; //value
	const int maxCapacity, maxSoldiers, maxWater;
	int capacity, soldiers, water;
public:
	ShipModel();
	~ShipModel();

	//TODO: Expand ships
	void refillWater();
};

