#include "stdafx.h"
#include "GameController.h"
#include "SailboatModel.h"
#include "GalleonModel.h"
#include "SchoonerModel.h"
#include "FrigateModel.h"
#include "GhostShip.h"

//TODO: Initialize with defaults

GameController::GameController()
{
}

GameController::~GameController()
{
	if (map != NULL)
		delete(map);
	//TODO: Delete ships and all that was allocated with new
}

CellModel* GameController::getCellAt(int x, int y) const { return map->getCellAt(x, y); }
GameState GameController::getGameState() const { return game.getGameState(); }
std::vector<PortModel*> GameController::getFriendlyPorts() const { return game.getFriendlyPorts(); }
std::vector<ShipModel*> GameController::getFriendlyShips() const { return game.getFriendlyShips(); }
std::vector<SeaModel*> GameController::getSeaCells() const {return game.getSeaCells();}

int GameController::getNumLines() const { return map->getNumLines(); }
int GameController::getNumColumns() const { return map->getNumColumns(); }
int GameController::getPlayerCoins() const { return game.getPlayerCoins(); }

CellModel* GameController::getFriendlyShipPositionByID(int id) const {return game.getFriendlyShips().at(id-1)->getPosition();}

bool GameController::readInitialFileConfigs(std::string filename)
{
	if (fileController.readInitialFileConfigs(filename, map, &event, &game)) {
		game.setGameState(GameState::GAME);
		return true;
	}
	return false;
}

bool GameController::buyShip(char type)
{
	//TODO:: Complete! Needs to recieve ship type 
	if (game.getFriendlyPorts().size()>0)
	{
		if (game.canRemoveCoins(game.getShipPrice()))
		{
			ShipModel* ship = nullptr;
			PortModel* position = game.getFriendlyPorts().at(0);
			switch (toupper(type))
			{
				case 'V': ship = new SailboatModel(Owner::PLAYER, position); break;
				case 'G': ship = new GalleonModel(position); break;
				case 'E': ship = new SchoonerModel(position); break;
				case 'F': ship = new FrigateModel(Owner::PLAYER, position); break;
				case 'S': ship = new GhostShip(position); break;
				default: return false; break;
			}
			if (ship!=nullptr)
			{
				game.removeCoins(game.getShipPrice());
				game.addFriendlyShip(ship);
				game.getFriendlyPorts().at(0)->addShipToPort(ship);
			}
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool GameController::canMoveShip(ShipModel* ship) const {return ship->getNumOfMoves() < ship->getMaxMoves();}

bool GameController::moveShip(ShipModel* ship, CellModel* goToPosition)
{
	if (goToPosition->getType() == CellModel::Type::GROUND)
	{
		return false;
	}
	else
	{
		CellModel* position = ship->getPosition();

		//Check cell that ship is going to
		if (goToPosition->getType() == CellModel::Type::SEA)
		{
			SeaModel* sea = (SeaModel*)goToPosition;

			if (sea->hasShip()) return false;
			//Only moves if cell is empty
			sea->setShip(ship);

		}
		else //Other option left to go to a port
		{
			PortModel* port = (PortModel*)goToPosition;
			if (port->getOwner() == ship->getOwner())
			{
				port->addShipToPort(ship);
				ship->refillWater();
			}
			else
			{
				//TODO: Combat with enemy port
				return false;
			}
		}

		//Check initial cell
		if (position->getType() == CellModel::Type::PORT)
		{
			PortModel* port = (PortModel*)position;
			port->removeShipFromPort(ship);
		}
		else //Other option left is to be at a sea cell
		{
			SeaModel* sea = (SeaModel*)position;
			sea->removeShip();
		}

		ship->moveShip(goToPosition);
		return true;
	}
}

bool GameController::moveCommand(int id, CellModel* goToPosition)
{
	try
	{
		ShipModel* ship = game.getFriendlyShips().at(id - 1);

		if (canMoveShip(ship))
		{
			if (moveShip(ship, goToPosition))
			{
				ship->setNavigation(Navigation::USER);
				return true;
			}
			return false;
		} 
		else
		{
			return false;
		}
	}
	catch (std::out_of_range e)
	{
		//TODO: Add to log ship doesnt exist
		return false;
	}
}

void GameController::proxCommand()
{
	friendlyFleetMovement(game.getFriendlyShips());
	enemyFleetMovement(game.getEnemyShips());
}

void GameController::friendlyFleetMovement(std::vector<ShipModel*> friendlyShips)
{
	for (ShipModel* friendlyShip : friendlyShips)
	{
		if (canMoveShip(friendlyShip))
		{
			switch (friendlyShip->getNavigation())
			{
				//TODO: Implement 
				case Navigation::AUTO: break;
				case Navigation::ORDER: break;
				case Navigation::LOST: lostShipMovement(friendlyShip); break;
			default: break;
			}
		}

		if (friendlyShip->getPosition()->getType()==CellModel::Type::SEA) 
			friendlyShip->navigationCost();

		friendlyShip->resetMoves();
	}
}

void GameController::enemyFleetMovement(std::vector<ShipModel*> enemyShips)
{
	for (ShipModel* enemyShip : enemyShips)
	{
		if (canMoveShip(enemyShip))
		{
			//TODO: Pirate ships will move on auto only later on
			switch (enemyShip->getNavigation())
			{
				//TODO: Implement 
				case Navigation::AUTO: break;
				case Navigation::LOST: lostShipMovement(enemyShip); break;
				default: break;
			}
		}
		enemyShip->resetMoves();
	}
}

void GameController::lostShipMovement(ShipModel* ship)
{
	do {
		while (!moveShip(ship, generateRandomMove(ship->getPosition())));
	} while (canMoveShip(ship));
}

CellModel* GameController::generateRandomMove(const CellModel* currentCell) const
{
	int randomNumber = rand() % 8 + 1;
	//TODO: Send number to logs
	//std::cout << randomNumber << " ";

	switch (randomNumber)
	{
		case 1:
			return getCellAbove(currentCell);
		case 2:
			return getCellBelow(currentCell);
		case 3:
			return getCellRight(currentCell);
		case 4:
			return getCellLeft(currentCell);
		case 5:
			return getCellAboveRight(currentCell);
		case 6:
			return getCellAboveLeft(currentCell);
		case 7:
			return getCellBelowRight(currentCell);
		case 8:
			return getCellBelowLeft(currentCell);
	}
}

CellModel* GameController::getCellAbove(const CellModel* currentCell) const {return map->getCellAbove(currentCell);}
CellModel* GameController::getCellBelow(const CellModel* currentCell) const {return map->getCellBelow(currentCell);}
CellModel* GameController::getCellRight(const CellModel* currentCell) const {return map->getCellRight(currentCell);}
CellModel* GameController::getCellLeft(const CellModel* currentCell) const {return map->getCellLeft(currentCell);}
CellModel* GameController::getCellAboveRight(const CellModel* currentCell) const {return map->getCellAboveRight(currentCell);}
CellModel* GameController::getCellAboveLeft(const CellModel* currentCell) const {return map->getCellAboveLeft(currentCell);}
CellModel* GameController::getCellBelowRight(const CellModel* currentCell) const {return map->getCellBelowRight(currentCell);}
CellModel* GameController::getCellBelowLeft(const CellModel* currentCell) const {return map->getCellBelowLeft(currentCell);}

void GameController::addCoins(double amount) {game.addCoins(amount);}

void GameController::endGame() {game.setGameState(GameState::END);}