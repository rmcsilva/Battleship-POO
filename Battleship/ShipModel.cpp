#include "stdafx.h"
#include "ShipModel.h"
#include <iomanip>



ShipModel::ShipModel(int maxCapacity, int maxSoldiers, int maxWater, int maxMoves, Owner owner, CellModel* position) : maxCapacity(maxCapacity), maxSoldiers(maxSoldiers), maxWater(maxWater), maxMoves(maxMoves), owner(owner), position(position)
{
	//TODO: Change to auto later
	navigation = Navigation::LOST;
	water = maxWater;
	soldiers = maxSoldiers;
	capacity = merch = fish = 0;
}

int ShipModel::getID() const {return id;}
Owner ShipModel::getOwner() const {return owner;}
Navigation ShipModel::getNavigation() const {return navigation;}

void ShipModel::setOwner(Owner owner) {this->owner = owner;}
void ShipModel::setNavigation(Navigation navigation) {this->navigation = navigation;}

void ShipModel::refillWater() {water = maxWater;}

std::ostream& operator<<(std::ostream& os, const ShipModel& ship)
{

	os << ship.getID();
	return os;
}
