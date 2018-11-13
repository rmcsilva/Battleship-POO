#include "stdafx.h"
#include "GameModel.h"


GameModel::GameModel()
{
	state = GameState::SETUP;
}

GameState GameModel::getGameState() const
{
	return state;
}

int GameModel::getPlayerCoins() const
{
	return player.getCoins();
}

int GameModel::getShipPrice() const
{
	return shipPrice;
}

int GameModel::getSoldierPrice() const
{
	return soldierPrice;
}

int GameModel::getFishSellPrice() const
{
	return fishSellPrice;
}

int GameModel::getMerchSellPrice() const
{
	return merchSellPrice;
}

int GameModel::getMerchBuyPrice() const
{
	return merchBuyPrice;
}

std::vector<PortModel*> GameModel::getFriendlyPorts() const
{
	return friendlyPorts;
}

void GameModel::setGameState(GameState state)
{
	this->state = state;
}

void GameModel::setPlayerCoins(int amount)
{
	this->player.setCoins(amount);
}

void GameModel::setShipPrice(int amount)
{
	this->shipPrice = amount;
}

void GameModel::setSoldierPrice(int amount)
{
	this->soldierPrice = amount;
}

void GameModel::setFishSellPrice(int amount)
{
	this->fishSellPrice = amount;
}

void GameModel::setMerchSellPrice(int amount)
{
	this->merchSellPrice = amount;
}

void GameModel::setMerchBuyPrice(int amount)
{
	this->merchBuyPrice = amount;
}

void GameModel::addFriendlyPort(PortModel *port)
{
	friendlyPorts.push_back(port);
}

void GameModel::addPiratePort(PortModel* port)
{
	piratePorts.push_back(port);
}