#include "stdafx.h"
#include "GameModel.h"
#include "GameUtil.h"
#include "PortModel.h"

GameModel::GameModel()
{
	state = GameState::SETUP;
	coins = COINS_EASY;

	eventProb = EVENT_PROB_EASY;
	stormProb = STORM_EVENT_PROB_EASY;
	mermaidProb = MERMAID_EVENT_PROB_EASY;
	lullProb = LULL_EVENT_PROB_EASY;
	riotProb = RIOT_EVENT_PROB_EASY;

	shipPrice = SHIP_PRICE_EASY;
	soldierPrice = SOLDIER_PRICE_EASY;
	fishSellPrice = FISH_SELL_PRICE_EASY;
	merchSellPrice = MERCH_SELL_PRICE_EASY;
	merchBuyPrice = MERCH_BUY_PRICE_EASY;
}

GameModel::~GameModel()
{
	for (ShipModel* friendlyShip : friendlyShips)
		delete(friendlyShip);

	for (ShipModel* enemyShip : enemyShips)
		delete(enemyShip);
}

GameModel::GameModel(const GameModel& game)
{
	for (auto friendlyShip : game.getFriendlyShips())
		friendlyShips.push_back(friendlyShip->clone());
	
	for (auto enemyShip : game.getEnemyShips())
		enemyShips.push_back(enemyShip->clone());

	eventProb = game.getEventProbability();
	stormProb = game.getStormEventProbability();
	mermaidProb = game.getMermaidEventProbability();
	lullProb = game.getLullEventProbability();
	riotProb = game.getRiotEventProbability();

	shipPrice = game.getShipPrice();
	soldierPrice = game.getSoldierPrice();
	fishSellPrice = game.getFishSellPrice();
	merchSellPrice = game.getMerchSellPrice();
	merchBuyPrice = game.getMerchBuyPrice();

	coins = game.getPlayerCoins();
	score = game.getPlayerScore();

	state = game.getGameState();
}

//Gets
GameState GameModel::getGameState() const {return state;}
double GameModel::getPlayerCoins() const {return coins;}
int GameModel::getShipPrice() const {return shipPrice;}
int GameModel::getSoldierPrice() const {return soldierPrice;}
int GameModel::getFishSellPrice() const {return fishSellPrice;}
int GameModel::getMerchSellPrice() const {return merchSellPrice;}
int GameModel::getMerchBuyPrice() const {return merchBuyPrice;}
std::vector<ShipModel*> GameModel::getFriendlyShips() const {return friendlyShips;}
std::vector<ShipModel*> GameModel::getEnemyShips() const {return enemyShips;}

int GameModel::getEventProbability() const { return eventProb; }
int GameModel::getStormEventProbability() const { return stormProb; }
int GameModel::getMermaidEventProbability() const { return mermaidProb; }
int GameModel::getLullEventProbability() const { return lullProb; }
int GameModel::getRiotEventProbability() const { return riotProb; }
double GameModel::getPlayerScore() const { return score; }

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
void GameModel::setScore(int score) {this->score = score;}

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
			if (shipPosition->getType() == CellModel::Type::SEA) {
				SeaModel* seaCell = (SeaModel*)shipPosition;
				seaCell->removeShip();
			} else if(shipPosition->getType()==CellModel::Type::PORT) {
				PortModel* portCell = (PortModel*)shipPosition;
				portCell->removeShipFromPort(ship);
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
			} else if (shipPosition->getType() == CellModel::Type::PORT) {
				PortModel* portCell = (PortModel*)shipPosition;
				portCell->removeShipFromPort(ship);
			}
			enemyShips.erase(enemyShips.begin() + i);
			delete ship;
			ship = nullptr;
			return true;
		}
	}
	return false;
}

void GameModel::changeShipOwner(ShipModel* ship, Navigation navigation)
{
	if (ship->getOwner() == Owner::PLAYER || ship->getOwner()==Owner::LOST)
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
