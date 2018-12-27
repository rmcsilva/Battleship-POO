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
	int id; //TODO:Unique id generated according to the the amount of ships in game
protected:
	ShipModel(int maxCapacity, int maxSoldiers, int maxWater, int maxMoves, Owner owner, CellModel* position);
	
	int capacity, soldiers, water, merch, fish;
	int numOfMoves = 0;
	Owner owner;
	Navigation navigation;
	CellModel* position;
	CellModel* goTo;
public:
	virtual ~ShipModel();
	enum class Type { FRIGATE, GALLEON, GHOST, SAILBOAT, SCHOONER };
	
	virtual Type getType() const = 0;
	virtual ShipModel* clone() = 0;
	int getID() const;
	int getNumOfMoves() const;
	int getMaxMoves() const;
	int getMaxWater() const;
	int getCapacity() const;
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

	void blockShipMovement();

	bool canAddToShipCargo(int amount);
	void addMerchToShip(int amount);
	void empyShipCargo();
	void emptyFish();
	bool canAddSoldiersToShip(int amount);
	void addSoldiersToShip(int amount);
	void addWaterToShip(int amount);
	void refillWater();
	void navigationCost();
	void moveShip(CellModel* position);
	void resetMoves();

	int combatVictory();
	void combatDefeat(int damage);
	void portCombat();
	void lootShip(ShipModel* ship);
	void conquerShip(ShipModel* lostShip);
	void transferFish(ShipModel* schooner);

	void mermaidAttack(int percentage);
	virtual bool stormAttack() = 0;

	virtual std::string getAsString() const = 0;
	bool operator==(ShipModel const &ship) const;
};

std::ostream& operator<<(std::ostream& os, const ShipModel &ship);

