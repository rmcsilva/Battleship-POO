#include "stdafx.h"
#include "PortModel.h"

PortModel::PortModel(int x, int y, char id,Owner owner) : CellModel(x, y), id(id), owner(owner) {}

CellModel::Type PortModel::getType() {return Type::PORT;}
Owner PortModel::getOwner() const {return owner;}
char PortModel::getID() const {return id;}
int PortModel::getNumOfSoldiers() const {return numSoldiers;}
std::vector<ShipModel*> PortModel::getShips() const {return ships;}
int PortModel::getNumberOfShips() const {return ships.size();}

void PortModel::setNumberOfSoldiers(int numSoldiers) {this->numSoldiers = numSoldiers;}

void PortModel::addShipToPort(ShipModel* ship) {ships.push_back(ship);}

bool PortModel::removeShipFromPort(ShipModel* ship)
{
	for (int i = 0; i < ships.size(); i++)
	{
		if (ships.at(i)==ship)
		{
			ships.erase(ships.begin() + i);
			return true;
		}
	}
	return false;
}

void PortModel::changeOwner()
{
	if (owner == Owner::PLAYER)
		owner = Owner::ENEMY;
	else
		owner = Owner::PLAYER;
}

PortModel* PortModel::clone() {
	return new PortModel(*this);
}

std::ostream& operator<<(std::ostream& os, const PortModel& port)
{
	if (port.getShips().size()>0)
	{
		os << "Port " << port.getID() << " Ships ID: ";
		for (ShipModel* ship : port.getShips())
			os << *ship << " | ";
		os << '\n';
	} 
	else
	{
		os << "Port " << port.getID() << " has no ships!\n";
	}
	return os;
}

