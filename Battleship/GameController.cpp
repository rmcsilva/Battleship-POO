#include "stdafx.h"
#include "GameController.h"

//TODO: Initialize with defaults

GameController::GameController()
{
}

GameController::~GameController()
{
	if (map != NULL)
	{
		delete(map);
	}
}

bool GameController::readInitialFileConfigs(std::string filename)
{
	if (fileController.readInitialFileConfigs(filename, map, &event, &game)) {
		game.setGameState(GameState::GAME);
		return true;
	}
	return false;
}

CellModel * GameController::getCellAt(int x, int y) const
{
	return map->getCellAt(x,y);
}

GameState GameController::getGameState() const
{
	return game.getGameState();
}

std::vector<PortModel*> GameController::getFriendlyPorts()
{
	return game.getFriendlyPorts();
}

bool GameController::buyShip()
{
	//TODO:: Complete! Needs to recieve ship type and see if the player has money to buy
	
	if (game.getFriendlyPorts().size()>0)
	{
		if (game.removeCoins(game.getShipPrice()))
		{
			//game.addFriendlyShip(new ShipModel);
			//game.getFriendlyPorts().at(0)->addShipToPort(new ShipModel);
			return true;
		}
		
	}
	return false;
}

int GameController::getNumLines() const
{
	return map->getNumLines();
}

int GameController::getNumColumns() const
{
	return map->getNumColumns();
}

void GameController::endGame()
{
	game.setGameState(GameState::END);
}
