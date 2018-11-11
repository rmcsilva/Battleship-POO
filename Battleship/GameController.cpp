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
	return fileController.readInitialFileConfigs(filename, map, &event, &game);
}

CellModel * GameController::getCellAt(int x, int y) const
{
	return map->getCellAt(x,y);
}
