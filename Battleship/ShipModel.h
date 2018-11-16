#pragma once
#include "CellModel.h"
enum class ShipOwner { PLAYER, ENEMY, LOST };
enum class Navigation { USER, AUTO, ORDER, LOST };

class ShipModel
{
	int price; //value TODO: Check if its still valid
	const int maxCapacity, maxSoldiers, maxWater, maxMoves;
	//TODO: Constantes para as tempestades
protected:
	int id; //Unique id generated according to the the amount of ships in game
	int capacity, soldiers, water, merch, fish;
	int numOfMoves = 0;
	ShipOwner owner;
	Navigation navigation;
	//TODO: Remove ship position its already on the map?
	CellModel* position;
	//TODO: Value when ship is on a order 
	CellModel* goTo;
public:
	ShipModel(int maxCapacity, int maxSoldiers, int maxWater, int maxMoves, ShipOwner owner, CellModel* position);
	//~ShipModel();
	enum class Type { FRIGATE, GALLEON, GHOST, SAILBOAT, SCHOONER };
	
	//TODO: Expand ships
	virtual Type getType() const = 0;
	int getID() const;
	int getNumOfMoves() const;
	int getMaxMoves() const;
	ShipOwner getOwner() const;
	Navigation getNavigation() const;
	CellModel* getPosition() const;
	CellModel* getGoTo() const;

	void setID(int id);
	void setOwner(ShipOwner owner);
	void setNavigation(Navigation navigation);
	void setPosition(CellModel* position);
	void setGoTo(CellModel* goTo);

	void refillWater();
	void moveShip(CellModel* goToPosition);
	void resetNumOfMoves();
	virtual bool stormAttack() = 0;
	//TODO: Movimentacao do navio no controlador
	bool operator==(ShipModel const &ship) const;
};

std::ostream& operator<<(std::ostream& os, const ShipModel &ship);

