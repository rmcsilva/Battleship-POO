#include "stdafx.h"
#include "ShipModel.h"
#include <iomanip>

ShipModel::ShipModel(int maxCapacity, int maxSoldiers, int maxWater, int maxMoves, ShipOwner owner, CellModel* position) : maxCapacity(maxCapacity), maxSoldiers(maxSoldiers), maxWater(maxWater), maxMoves(maxMoves), owner(owner), position(position)
{
	//TODO: Change navigation to auto later
	navigation = Navigation::LOST;
	water = maxWater;
	soldiers = maxSoldiers;
	capacity = merch = fish = 0;
}

int ShipModel::getID() const {return id;}
int ShipModel::getNumOfMoves() const {return numOfMoves;}
int ShipModel::getMaxMoves() const {return maxMoves;}
ShipOwner ShipModel::getOwner() const {return owner;}
Navigation ShipModel::getNavigation() const {return navigation;}
CellModel* ShipModel::getPosition() const {return position;}
CellModel* ShipModel::getGoTo() const {return goTo;}

void ShipModel::setID(int id) {this->id = id;}
void ShipModel::setOwner(ShipOwner owner) {this->owner = owner;}
void ShipModel::setNavigation(Navigation navigation) {this->navigation = navigation;}
void ShipModel::setPosition(CellModel* position) {this->position = position;}
void ShipModel::setGoTo(CellModel* goTo) {this->goTo = goTo;}

void ShipModel::refillWater() {water = maxWater;}

void ShipModel::moveShip(CellModel* position)
{
	this->position = position;
	if (goTo==position) {goTo = nullptr;}
}

void ShipModel::resetNumOfMoves() {numOfMoves = 0;}

bool ShipModel::operator==(ShipModel const& ship) const {return this->id == ship.getID();}

std::ostream& operator<<(std::ostream& os, const ShipModel& ship)
{
	switch (ship.getType())
	{
		case ShipModel::Type::FRIGATE: os << "F "; break;
		case ShipModel::Type::GALLEON: os << "G "; break;
		case ShipModel::Type::GHOST: os << "S "; break;
		case ShipModel::Type::SAILBOAT: os << "V "; break;
		case ShipModel::Type::SCHOONER: os << "E "; break;
	}
	os << ship.getID();
	return os;
}
