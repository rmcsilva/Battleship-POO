#pragma once
#include "PlayerModel.h"
#include "PortModel.h"

enum class GameState { SETUP, GAME, END };

class GameModel
{
	PlayerModel player;
	int shipPrice, soldierPrice;
	int fishSellPrice, merchSellPrice;
	int merchBuyPrice;
	int score=0;
	//TODO: Main port is the first one
	std::vector<PortModel*> friendlyPorts;
	//TODO: Add enemy ports
	//TODO: Add list of friendly and enemy ships
	//TODO: If if by doing so its easy to update map
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
};

