#pragma once
#include "CellModel.h"
#include "ShipModel.h"

class SeaModel : public CellModel{
	ShipModel* ship = nullptr;
public:
    SeaModel(int x, int y);

    Type getType() override;

	bool hasShip() const;
	ShipModel* getShip() const;
	ShipModel::Type getShipType() const;
	ShipOwner getShipOwner() const;
	void setShip(ShipModel* ship);
	void removeShip();
};
