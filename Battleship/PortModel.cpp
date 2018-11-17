#include "stdafx.h"
#include "PortModel.h"

PortModel::PortModel(int x, int y, char id,Owner owner) : CellModel(x, y), id(id), owner(owner) {}

CellModel::Type PortModel::getType() {return Type::PORT;}
Owner PortModel::getOwner() const {return owner;}
char PortModel::getID() const {return id;}
std::vector<ShipModel*> PortModel::getShips() const {return ships;}

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

