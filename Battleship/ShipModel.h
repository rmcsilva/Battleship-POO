#pragma once
#include "CellModel.h"
enum class Owner { PLAYER, ENEMY, LOST };
enum class Navigation { USER, AUTO, ORDER, LOST };

class ShipModel
{
	int price; //value TODO: Check if its still valid
	const int maxCapacity, maxSoldiers, maxWater, maxMoves;
	//TODO: Constantes para as tempestades
protected:
	int id; //Unique id
	int capacity, soldiers, water, merch, fish;
	Owner owner;
	Navigation navigation;
	CellModel* position;
	//TODO: Value when ship is on a order 
	int goX, goY;
public:
	ShipModel(int maxCapacity, int maxSoldiers, int maxWater, int maxMoves, Owner owner, CellModel* position);
	//~ShipModel();
	
	//TODO: Expand ships
	int getID() const;
	Owner getOwner() const;
	Navigation getNavigation() const;

	void setOwner(Owner owner);
	void setNavigation(Navigation navigation);

	void refillWater();
	virtual bool stormAttack() = 0;
	//TODO: Movimentacao do navio
};

std::ostream& operator<<(std::ostream& os, const ShipModel &ship);

