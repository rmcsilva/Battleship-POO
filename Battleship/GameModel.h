#pragma once
#include "PlayerModel.h"
#include "PortModel.h"
class GameModel
{
	PlayerModel player;
	int shipPrice, soldierPrice;
	int fishSellPrice, merchSellPrice;
	int merchBuyPrice;
	//TODO: Main port is the first one
	std::vector<PortModel*> friendlyPorts;

public:
	GameModel();

	int getPlayerCoins() const;
	int getShipPrice() const;
	int getSoldierPrice() const;
	int getFishSellPrice() const;
	int getMerchSellPrice() const;
	int getMerchBuyPrice() const;
	std::vector<PortModel*> getFriendlyPorts() const;

	void setPlayerCoins(int amount);
	void setShipPrice(int amount);
	void setSoldierPrice(int amount);
	void setFishSellPrice(int amount);
	void setMerchSellPrice(int amount);
	void setMerchBuyPrice(int amount);

	void addFriendlyPort(PortModel *port);
};

