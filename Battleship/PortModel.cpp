#include "stdafx.h"
#include "PortModel.h"

PortModel::PortModel(int x, int y, char id,CellModel::Owner owner) : CellModel(x, y), id(id), owner(owner) {}

CellModel::Type PortModel::getType() {return Type::PORT;}
CellModel::Owner PortModel::getOwner() const {return owner;}
char PortModel::getID() const {return id;}
std::vector<ShipModel*> PortModel::getShips() const {return ships;}

void PortModel::addShipToPort(ShipModel* ship) {ships.push_back(ship);}

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

