#include "stdafx.h"
#include "GameController.h"

//TODO: Initialize with defaults

GameController::GameController()
{
}

GameController::~GameController()
{
	if (map != NULL) {delete(map);}
	//TODO: Delete ships and all that was allocated with new
}

CellModel * GameController::getCellAt(int x, int y) const { return map->getCellAt(x, y); }
GameState GameController::getGameState() const { return game.getGameState(); }
std::vector<PortModel*> GameController::getFriendlyPorts() { return game.getFriendlyPorts(); }
int GameController::getNumLines() const { return map->getNumLines(); }
int GameController::getNumColumns() const { return map->getNumColumns(); }
int GameController::getPlayerCoins() const { return game.getPlayerCoins(); }

bool GameController::readInitialFileConfigs(std::string filename)
{
	if (fileController.readInitialFileConfigs(filename, map, &event, &game)) {
		game.setGameState(GameState::GAME);
		return true;
	}
	return false;
}

bool GameController::buyShip()
{
	//TODO:: Complete! Needs to recieve ship type 
	if (game.getFriendlyPorts().size()>0)
	{
		if (game.removeCoins(game.getShipPrice()))
		{
			//game.addFriendlyShip(new ShipModel);
			//game.getFriendlyPorts().at(0)->addShipToPort(new ShipModel);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void GameController::endGame() {game.setGameState(GameState::END);}
