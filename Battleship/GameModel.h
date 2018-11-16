#pragma once
#include "PlayerModel.h"
#include "PortModel.h"

enum class GameState { SETUP, GAME, END };

class GameModel
{
	PlayerModel player;
	//TODO: Arranjar constantes para os precos de acordo com a difuculdade
	int shipPrice, soldierPrice;
	int fishSellPrice, merchSellPrice;
	int merchBuyPrice;
	int score=0;
	//TODO: Main port is the first one
	std::vector<PortModel*> friendlyPorts;
	std::vector<PortModel*> piratePorts;
	//TODO: Add list of friendly and enemy ships
	std::vector<ShipModel*> friendlyShips;
	std::vector<ShipModel*> pirateShips;
	//TODO: If if by doing so its easy to update map
	//TODO: Maybe add a list of all the sea cells to add random pirate ships
	std::vector<CellModel*> seaCells;
	GameState state;

public:
	GameModel();

	GameState getGameState() const;
	int getPlayerCoins() const;
	int getShipPrice() const;
	int getSoldierPrice() const;
	int getFishSellPrice() const;
	int getMerchSellPrice() const;
	int getMerchBuyPrice() const;
	std::vector<PortModel*> getFriendlyPorts() const;

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

	void addSeaCell(CellModel* cell);

	void addCoins(int amount);
	bool removeCoins(int amount);
};

