#include "stdafx.h"
#include "GameModel.h"


GameModel::GameModel()
{
	state = GameState::SETUP;
}

GameModel::~GameModel()
{
	for (ShipModel* friendlyShip : friendlyShips)
		delete(friendlyShip);

	for (ShipModel* pirateShip : pirateShips)
		delete(pirateShip);
}

//Gets
GameState GameModel::getGameState() const {return state;}
int GameModel::getPlayerCoins() const {return player.getCoins();}
int GameModel::getShipPrice() const {return shipPrice;}
int GameModel::getSoldierPrice() const {return soldierPrice;}
int GameModel::getFishSellPrice() const {return fishSellPrice;}
int GameModel::getMerchSellPrice() const {return merchSellPrice;}
int GameModel::getMerchBuyPrice() const {return merchBuyPrice;}
std::vector<PortModel*> GameModel::getFriendlyPorts() const {return friendlyPorts;}
std::vector<ShipModel*> GameModel::getFriendlyShips() const {return friendlyShips;}
std::vector<SeaModel*> GameModel::getSeaCells() const {return seaCells;}

//Sets
void GameModel::setGameState(GameState state) {this->state = state;}
void GameModel::setPlayerCoins(int amount) {this->player.setCoins(amount);}
void GameModel::setShipPrice(int amount) {this->shipPrice = amount;}
void GameModel::setSoldierPrice(int amount) {this->soldierPrice = amount;}
void GameModel::setFishSellPrice(int amount) {this->fishSellPrice = amount;}
void GameModel::setMerchSellPrice(int amount) {this->merchSellPrice = amount;}
void GameModel::setMerchBuyPrice(int amount) {this->merchBuyPrice = amount;}

//Add Ports
void GameModel::addFriendlyPort(PortModel *port) {friendlyPorts.push_back(port);}
void GameModel::addPiratePort(PortModel* port) {piratePorts.push_back(port);}

//Add Ships
void GameModel::addFriendlyShip(ShipModel* ship)
{
	ship->setID(friendlyShips.size() + 1);
	friendlyShips.push_back(ship);
}
void GameModel::addPirateShip(ShipModel* ship) {pirateShips.push_back(ship);}

void GameModel::addSeaCell(SeaModel * cell) { seaCells.push_back(cell); }

//Player Coins
void GameModel::addCoins(double amount) {player.addCoins(amount);}
bool GameModel::canRemoveCoins(int amount) {return player.canRemoveCoins(amount);}
bool GameModel::removeCoins(int amount) {return player.removeCoins(amount);}
