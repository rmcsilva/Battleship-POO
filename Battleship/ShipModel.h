#pragma once
#include "CellModel.h"
enum class Owner { PLAYER, ENEMY, LOST };
enum class Navigation { USER, AUTO, ORDER, LOST };

class ShipModel
{
	int price; //value TODO: Check if its still valid
	const int maxCapacity, maxSoldiers, maxWater, maxMoves;
protected:
	ShipModel(int maxCapacity, int maxSoldiers, int maxWater, int maxMoves, Owner owner, CellModel* position);
	int id; //Unique id generated according to the the amount of ships in game
	int capacity, soldiers, water, merch, fish;
	int numOfMoves = 0;
	Owner owner;
	Navigation navigation;
	CellModel* position;
	//TODO: Value when ship is on a order 
	CellModel* goTo;
public:
	//~ShipModel();
	enum class Type { FRIGATE, GALLEON, GHOST, SAILBOAT, SCHOONER };
	
	//TODO: Expand ships
	virtual Type getType() const = 0;
	int getID() const;
	int getNumOfMoves() const;
	int getMaxMoves() const;
	Owner getOwner() const;
	Navigation getNavigation() const;
	CellModel* getPosition() const;
	CellModel* getGoTo() const;

	void setID(int id);
	void setOwner(Owner owner);
	void setNavigation(Navigation navigation);
	void setPosition(CellModel* position);
	void setGoTo(CellModel* goTo);

	void refillWater();
	void navigationCost();
	void moveShip(CellModel* goToPosition);
	void resetMoves();
	virtual bool stormAttack() = 0;
	bool operator==(ShipModel const &ship) const;
};

std::ostream& operator<<(std::ostream& os, const ShipModel &ship);

