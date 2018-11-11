#pragma once
#include "FileController.h"
class GameController {
	FileController fileController;
	MapModel *map = NULL;
	EventModel event;
	GameModel game;
public:
	GameController();
	~GameController();

	bool readInitialFileConfigs(std::string filename);
	CellModel* getCellAt(int x, int y) const;
	GameState getGameState() const;
};

