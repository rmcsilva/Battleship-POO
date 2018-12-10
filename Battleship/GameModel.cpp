#include "stdafx.h"
#include "GameModel.h"
#include "EventModel.h"

const int GameModel::COINS_EASY = 5000;

const int GameModel::EVENT_PROB_EASY = 20;
const int GameModel::STORM_EVENT_PROB_EASY = 30;
const int GameModel::MERMAID_EVENT_PROB_EASY = 30;
const int GameModel::LULL_EVENT_PROB_EASY = 20;
const int GameModel::RIOT_EVENT_PROB_EASY = 20;

GameModel::GameModel()
{
	state = GameState::SETUP;
	//TODO: Check game difficulty
	coins = COINS_EASY;

	eventProb = EVENT_PROB_EASY;
	stormProb = STORM_EVENT_PROB_EASY;
	mermaidProb = MERMAID_EVENT_PROB_EASY;
	lullProb = LULL_EVENT_PROB_EASY;
	riotProb = RIOT_EVENT_PROB_EASY;
}

GameModel::~GameModel()
{
	for (ShipModel* friendlyShip : friendlyShips)
		delete(friendlyShip);

	for (ShipModel* enemyShip : enemyShips)
		delete(enemyShip);
}

//Gets
GameState GameModel::getGameState() const {return state;}
double GameModel::getPlayerCoins() const {return coins;}
int GameModel::getShipPrice() const {return shipPrice;}
int GameModel::getSoldierPrice() const {return soldierPrice;}
int GameModel::getFishSellPrice() const {return fishSellPrice;}
int GameModel::getMerchSellPrice() const {return merchSellPrice;}
int GameModel::getMerchBuyPrice() const {return merchBuyPrice;}
std::vector<PortModel*> GameModel::getFriendlyPorts() const {return friendlyPorts;}
std::vector<ShipModel*> GameModel::getFriendlyShips() const {return friendlyShips;}
std::vector<PortModel*> GameModel::getEnemyPorts() const {return enemyPorts;}
std::vector<ShipModel*> GameModel::getEnemyShips() const {return enemyShips;}

int GameModel::getEventProbability() const { return eventProb; }
int GameModel::getStormEventProbability() const { return stormProb; }
int GameModel::getMermaidEventProbability() const { return mermaidProb; }
int GameModel::getLullEventProbability() const { return lullProb; }
int GameModel::getRiotEventProbability() const { return riotProb; }

//Sets
void GameModel::setGameState(GameState state) {this->state = state;}
void GameModel::setPlayerCoins(int amount) {this->coins = amount;}
void GameModel::setShipPrice(int amount) {this->shipPrice = amount;}
void GameModel::setSoldierPrice(int amount) {this->soldierPrice = amount;}
void GameModel::setFishSellPrice(int amount) {this->fishSellPrice = amount;}
void GameModel::setMerchSellPrice(int amount) {this->merchSellPrice = amount;}
void GameModel::setMerchBuyPrice(int amount) {this->merchBuyPrice = amount;}
void GameModel::setEventProbability(int prob) { this->eventProb = prob; }
void GameModel::setStormEventProbability(int prob) { this->stormProb = prob; }
void GameModel::setMermaidEventProbability(int prob) { this->mermaidProb = prob; }
void GameModel::setCalmEventProbability(int prob) { this->lullProb = prob; }
void GameModel::setRiotEventProbability(int prob) { this->riotProb = prob; }

//Add Ports
void GameModel::addFriendlyPort(PortModel *port) {friendlyPorts.push_back(port);}
void GameModel::addPiratePort(PortModel* port) {enemyPorts.push_back(port);}

//Add Ships
void GameModel::addFriendlyShip(ShipModel* ship)
{
	//TODO:Implement dynamic ID
	//ship->setID(friendlyShips.size() + 1);
	friendlyShips.push_back(ship);
}
void GameModel::addPirateShip(ShipModel* ship) {enemyShips.push_back(ship);}

bool GameModel::removeFriendlyShip(ShipModel* ship)
{
	for (int i=0; i < friendlyShips.size(); i++)
	{
		if (friendlyShips.at(i)==ship)
		{
			CellModel *shipPosition = friendlyShips.at(i)->getPosition();
			if (shipPosition->getType() == CellModel::Type::SEA)
			{
				SeaModel* seaCell = (SeaModel*)shipPosition;
				seaCell->removeShip();
			}
			friendlyShips.erase(friendlyShips.begin() + i);
			delete ship;
			ship = nullptr;
			return true;
		}
	}
	return false;
}

bool GameModel::removeEnemyShip(ShipModel* ship)
{
	for (int i = 0; i < enemyShips.size(); i++)
	{
		if (enemyShips.at(i) == ship)
		{
			CellModel *shipPosition = enemyShips.at(i)->getPosition();
			if(shipPosition->getType()==CellModel::Type::SEA)
			{
				SeaModel* seaCell = (SeaModel*)shipPosition;
				seaCell->removeShip();
			}
			enemyShips.erase(enemyShips.begin() + i);
			delete ship;
			ship = nullptr;
			return true;
		}
	}
	return false;
}

void GameModel::changePortOwner(PortModel* port)
{
	if (port->getOwner() == Owner::PLAYER)
	{
		for (int i = 0; i < friendlyPorts.size(); i++)
		{
			if (friendlyPorts.at(i)==port)
			{
				//Removes from player puts in pirate vector
				friendlyPorts.erase(friendlyPorts.begin() + i);
				enemyPorts.push_back(port);
			}
		}
	}
	else
	{
		for (int i = 0; i < enemyPorts.size(); i++)
		{
			if (enemyPorts.at(i) == port)
			{
				//Removes from pirate puts in player vector
				enemyPorts.erase(enemyPorts.begin() + i);
				friendlyPorts.push_back(port);
			}
		}
	}

	port->changeOwner();
}

void GameModel::changeShipOwner(ShipModel* ship, Navigation navigation)
{
	if (ship->getOwner() == Owner::PLAYER)
	{
		ship->setOwner(Owner::ENEMY);
		ship->setNavigation(navigation);
		enemyShips.push_back(ship);
		for (int i = 0; i < friendlyShips.size(); i++)
		{
			if (friendlyShips.at(i)==ship)
			{
				friendlyShips.erase(friendlyShips.begin() + i);
				break;
			}
		}
	}
	else
	{
		ship->setOwner(Owner::PLAYER);
		ship->setNavigation(navigation);
		friendlyShips.push_back(ship);
		for (int i = 0; i < enemyShips.size(); i++)
		{
			if (enemyShips.at(i) == ship)
			{
				enemyShips.erase(enemyShips.begin() + i);
				break;
			}
		}
	}
}

//Player Coins
void GameModel::addCoins(double amount) {coins += amount;}

bool GameModel::removeCoins(int amount) {
	if (canRemoveCoins(amount)) {
		coins -= amount;
		return true;
	}
	else {
		return false;
	}
}

bool GameModel::canRemoveCoins(int amount) {return coins >= amount;}
