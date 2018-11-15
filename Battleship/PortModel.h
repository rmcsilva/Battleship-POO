#pragma once
#include "CellModel.h"
#include "ShipModel.h"

class PortModel : public CellModel{
	char id;
	CellModel::Owner owner;
	int numSoldiers = 100;
	std::vector<ShipModel*> ships;
public:
    PortModel(int x, int y, char id,CellModel::Owner owner);

    Type getType() override;
	Owner getOwner() const;
	char getID() const;
	std::vector<ShipModel*> getShips() const;

	void addShipToPort(ShipModel* ship);
};

std::ostream& operator<<(std::ostream& os, const PortModel &port);
