#include "stdafx.h"
#include "ShipModel.h"

int ShipModel::shipCount = 1;

ShipModel::ShipModel(int maxCapacity, int maxSoldiers, int maxWater, int maxMoves, Owner owner, CellModel* position) : maxCapacity(maxCapacity), maxSoldiers(maxSoldiers), maxWater(maxWater), maxMoves(maxMoves), owner(owner), position(position)
{
	//TODO: Change navigation to auto later
	navigation = Navigation::AUTO;
	water = maxWater;
	soldiers = maxSoldiers;
	capacity = merch = fish = 0;
	id = shipCount++;
}

ShipModel::~ShipModel()
{
}

int ShipModel::getID() const {return id;}
int ShipModel::getNumOfMoves() const {return numOfMoves;}
int ShipModel::getMaxMoves() const {return maxMoves;}
int ShipModel::getMaxWater() const {return maxWater;}
int ShipModel::getCapacity() const {return capacity;}
int ShipModel::getWater() const {return water;}
int ShipModel::getFish() const{return fish;}
int ShipModel::getMerch() const {return merch;}
Owner ShipModel::getOwner() const {return owner;}
int ShipModel::getSoldiers() const {return soldiers;}
Navigation ShipModel::getNavigation() const {return navigation;}
CellModel* ShipModel::getPosition() const {return position;}
CellModel* ShipModel::getGoTo() const {return goTo;}

//void ShipModel::setID(int id) {this->id = id;}
void ShipModel::setOwner(Owner owner) {this->owner = owner;}
void ShipModel::setNavigation(Navigation navigation) {this->navigation = navigation;}
void ShipModel::setPosition(CellModel* position) {this->position = position;}
void ShipModel::setGoTo(CellModel* goTo) {this->goTo = goTo;}

void ShipModel::blockShipMovement() {numOfMoves = maxMoves;}

bool ShipModel::canAddToShipCargo(int amount) {return capacity + amount <= maxCapacity;}

void ShipModel::addMerchToShip(int amount)
{
	if (canAddToShipCargo(amount)) {
		capacity += amount;
		merch += amount;
	}
}

void ShipModel::empyShipCargo()
{
	capacity = 0;
	merch = 0;
	fish = 0;
}

void ShipModel::emptyFish()
{
	capacity -= fish;
	fish = 0;
}

bool ShipModel::canAddSoldiersToShip(int amount)
{
	return soldiers + amount <= maxSoldiers;
}

void ShipModel::addSoldiersToShip(int amount)
{
	if (canAddSoldiersToShip(amount)) {
		soldiers += amount;
	}
}

void ShipModel::addWaterToShip(int amount)
{
	water += amount;
	if (water>maxWater) {
		water = maxWater;
	}
}

void ShipModel::removeSoldiers(int soldiersLost)
{
	soldiers -= soldiersLost;
	if (soldiers < 0) {
		soldiers = 0;
	}
}

void ShipModel::catchFish()
{
	capacity += 1;
	fish += 1;
}

void ShipModel::refillWater() {water = maxWater;}

void ShipModel::navigationCost()
{
	if (owner == Owner::ENEMY || owner == Owner::LOST) return;

	if (soldiers > 0)
	{
		if (water >= soldiers)
		{
			water -= soldiers;
			return;
		} 
		
		water = 0;
		
		soldiers--;

		if (soldiers==0) {
			owner = Owner::LOST;
			navigation = Navigation::LOST;
		}
	}
}

void ShipModel::moveShip(CellModel* position)
{
	this->position = position;
	if (goTo==position) {
		goTo = nullptr;
		navigation = Navigation::AUTO;
	}
	numOfMoves++;
}

void ShipModel::resetMoves() {numOfMoves = 0;}

int ShipModel::combatVictory()
{
	int soldiersLost = soldiers * COMBAT_WON_AFFECTED_SOLDIERS_PERCENTAGE / 100;
	soldiers -= soldiersLost;

	if (soldiers < 0) soldiers = 0;

	return soldiersLost;
}

void ShipModel::combatDefeat(int damage)
{
	soldiers -= damage * 2;

	if (soldiers < 0) soldiers = 0;
}

void ShipModel::portCombat()
{
	int soldiersLost = soldiers * PORT_BATTLE_AFFECTED_SOLDIERS_PERCENTAGE / 100;
	soldiers -= soldiersLost;

	if (soldiers < 0) soldiers = 0;
}

void ShipModel::lootShip(ShipModel* ship)
{
	water += ship->getWater();
	if (water > maxWater) water = maxWater;

	if (capacity != maxCapacity)
	{
		int shipMerch = ship->getMerch();
		if (shipMerch > 0)
		{
			shipMerch /= 2;
			if (canAddToShipCargo(shipMerch)) {
				merch += shipMerch;
				capacity += shipMerch;
			}
		}

		int shipFish = ship->getFish();
		if (shipFish > 0)
		{
			shipFish /= 2;
			if (canAddToShipCargo(shipMerch)) {
				fish += shipFish;
				capacity += shipFish;
			}
		}
	}
}

void ShipModel::conquerShip(ShipModel* lostShip)
{
	water /= 2;
	soldiers /= 2;

	lostShip->addSoldiersToShip(soldiers);
	lostShip->addWaterToShip(water);

	lostShip->setNavigation(Navigation::AUTO);
}

void ShipModel::transferFish(ShipModel* schooner)
{
	int schoonersFish = schooner->getFish();

	if (canAddToShipCargo(schoonersFish)) {
		fish += schoonersFish;
		schooner->emptyFish();
	}
}

void ShipModel::mermaidAttack(int percentage)
{
	int affectedSoldiers = soldiers * percentage / 100;
	soldiers -= affectedSoldiers;

	if (soldiers < 0) soldiers = 0;
}


bool ShipModel::operator==(ShipModel const& ship) const {return this->id == ship.getID();}

std::ostream& operator<<(std::ostream& os, const ShipModel& ship)
{
	os << ship.getAsString();
	os << ship.getID();
	return os;
}
