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

int GameController::getNumLines() const
{
	return map->getNumLines();
}

int GameController::getNumColumns() const
{
	return map->getNumColumns();
}
