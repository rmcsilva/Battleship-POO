#pragma once
#include "CellModel.h"

#define COMBAT_WON_AFFECTED_SOLDIERS_PERCENTAGE 20
#define PORT_BATTLE_AFFECTED_SOLDIERS_PERCENTAGE 20

enum class Owner { PLAYER, ENEMY, LOST };
enum class Navigation { USER, AUTO, ORDER, LOST };

class ShipModel
{
	static int shipCount;
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
	int getWater() const;
	int getFish() const;
	int getMerch() const;
	Owner getOwner() const;
	int getSoldiers() const;
	Navigation getNavigation() const;
	CellModel* getPosition() const;
	CellModel* getGoTo() const;

	//void setID(int id);
	void setOwner(Owner owner);
	void setNavigation(Navigation navigation);
	void setPosition(CellModel* position);
	void setGoTo(CellModel* goTo);

	bool canAddToShipCargo(int amount);
	void refillWater();
	void navigationCost();
	//TODO:Make pure virtual
	void autoShipMovement();
	void moveShip(CellModel* position);
	void resetMoves();

	int combatVictory();
	void combatDefeat(int damage);
	void portCombat();
	void lootShip(ShipModel* ship);

	virtual bool stormAttack() = 0;

	virtual std::string getAsString() const = 0;
	bool operator==(ShipModel const &ship) const;
};

std::ostream& operator<<(std::ostream& os, const ShipModel &ship);

