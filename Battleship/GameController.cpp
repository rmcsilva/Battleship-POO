#include "stdafx.h"
#include "GameController.h"

//TODO: Initialize with defaults

GameController::GameController()
{
}

bool GameController::readInitialFileConfigs(std::string filename)
{
	return fileController.readInitialFileConfigs(filename, map);
}

CellModel * GameController::getCellAt(int x, int y) const
{
	return map->getCellAt(x,y);
}
