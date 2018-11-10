#pragma once
#include "FileControler.h"
class GameController {
	FileController fileController;
	MapModel *map;
public:
	GameController();
	bool readInitialFileConfigs(std::string filename);
	CellModel* getCellAt(int x, int y) const;
};

