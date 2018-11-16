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

	//Gets
	CellModel* getCellAt(int x, int y) const;
	GameState getGameState() const;
	std::vector<PortModel*> getFriendlyPorts();
	int getNumLines() const;
	int getNumColumns() const;
	int getPlayerCoins() const;

	//Initial Read From file
	bool readInitialFileConfigs(std::string filename);
	
	bool buyShip();

	//Player coins
	void addCoins(int amount);

	void endGame();
};

