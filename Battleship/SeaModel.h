#pragma once
#include "CellModel.h"
#include "ShipModel.h"
#include "FishModel.h"

class SeaModel : public CellModel{
	ShipModel* ship = nullptr;
	FishModel fish;
public:
    SeaModel(int x, int y);

    Type getType() override;

	bool hasShip() const;
	ShipModel* getShip() const;
	ShipModel::Type getShipType() const;
	Owner getShipOwner() const;
	void setShip(ShipModel* ship);
	void removeShip();

	//Fish methods
	bool hasFish();
	void catchFish();
	void updateCountdown();


	SeaModel* clone() override;
};
