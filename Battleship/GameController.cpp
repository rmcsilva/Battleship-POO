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
				case 'V': ship = new SailboatModel(ShipOwner::PLAYER, position); break;
				case 'G': ship = new GalleonModel(position); break;
				case 'E': ship = new SchoonerModel(position); break;
				case 'F': ship = new FrigateModel(ShipOwner::PLAYER, position); break;
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

bool GameController::move(int id, CellModel* goToPosition)
{
	try
	{
		ShipModel* ship = game.getFriendlyShips().at(id - 1);
		//TODO: Update port information (ships may leave port)
		//TODO: See better way to show ships if by map or ship
		//TODO: Todo check boundaries
		//if (ship->getNumOfMoves() < ship->getMaxMoves())
		//{
		//	
		//} 
		//else
		//{
		//	return false;
		//}
		//SeaModel * cell = (SeaModel*)goToPosition;
		//cell->setShip(ship);
		ship->setPosition(goToPosition);
	}
	catch (std::out_of_range e)
	{
		//TODO: Add to log ship doesnt exist
		return false;
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