#include "stdafx.h"
#include "SeaModel.h"

SeaModel::SeaModel(int x, int y) : CellModel(x, y) {}

CellModel::Type SeaModel::getType() {
    return Type::SEA;
}

bool SeaModel::hasShip() const {return ship != nullptr;}

ShipModel* SeaModel::getShip() const {return ship;}

ShipModel::Type SeaModel::getShipType() const
{
	if (ship!=nullptr) {return ship->getType();}
}

Owner SeaModel::getShipOwner() const {if (ship!=nullptr) return ship->getOwner();}

void SeaModel::setShip(ShipModel* ship) {this->ship = ship;}
void SeaModel::removeShip() {ship = nullptr;}

bool SeaModel::hasFish() {return fish.hasFish();}
void SeaModel::catchFish() {return fish.catchFish();}
void SeaModel::updateCountdown() {return fish.updateCountdown();}