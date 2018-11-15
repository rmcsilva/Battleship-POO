#include "stdafx.h"
#include "ShipModel.h"
#include <iomanip>

int ShipModel::getID() const {return id;}

std::ostream& operator<<(std::ostream& os, const ShipModel& ship)
{
	os << ship.getID();
	return os;
}
