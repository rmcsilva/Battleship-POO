#pragma once
class ShipModel
{
	int id; //Unique id
	int price; //value
	const int maxCapacity, maxSoldiers, maxWater;
	int capacity, soldiers, water, merch, fish;
	enum class Owner{PLAYER, ENEMY, LOST};
	//TODO: Constantes para as tempestades
public:
	//ShipModel();
	//~ShipModel();

	//TODO: Expand ships
	int getID() const;
	virtual Owner getOwner() const = 0;
	virtual void refillWater() = 0;
	//TODO: Movimentacao do navio
};

std::ostream& operator<<(std::ostream& os, const ShipModel &ship);

