#pragma once
#include "PortModel.h"
#include "SeaModel.h"

enum class GameState { SETUP, GAME, END };

class GameModel
{
	//TODO: Change consts of the prices according to game difficulty
	int shipPrice, soldierPrice;
	int fishSellPrice, merchSellPrice;
	int merchBuyPrice;
	double coins;
	double score=0;
	//TODO: Main port is the first one
	std::vector<PortModel*> friendlyPorts;
	std::vector<PortModel*> enemyPorts;

	std::vector<ShipModel*> friendlyShips;
	std::vector<ShipModel*> enemyShips;

	std::vector<SeaModel*> seaCells;

	GameState state;

	static const int COINS_EASY;

public:
	GameModel();
	~GameModel();

	GameState getGameState() const;
	int getPlayerCoins() const;
	int getShipPrice() const;
	int getSoldierPrice() const;
	int getFishSellPrice() const;
	int getMerchSellPrice() const;
	int getMerchBuyPrice() const;
	std::vector<PortModel*> getFriendlyPorts() const;
	std::vector<ShipModel*> getFriendlyShips() const;
	std::vector<PortModel*> getEnemyPorts() const;
	std::vector<ShipModel*> getEnemyShips() const;
	std::vector<SeaModel*> getSeaCells() const;

	void setGameState(GameState state);
	void setPlayerCoins(int amount);
	void setShipPrice(int amount);
	void setSoldierPrice(int amount);
	void setFishSellPrice(int amount);
	void setMerchSellPrice(int amount);
	void setMerchBuyPrice(int amount);

	void addFriendlyPort(PortModel *port);
	void addPiratePort(PortModel *port);

	void addFriendlyShip(ShipModel* ship);
	void addPirateShip(ShipModel* ship);

	bool removeFriendlyShip(ShipModel* ship);
	bool removeEnemyShip(ShipModel* ship);

	void changePortOwner(PortModel* port);

	void addSeaCell(SeaModel* cell);

	void addCoins(double amount);
	bool removeCoins(int amount);

	bool canRemoveCoins(int amount);
};

