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
	std::vector<PortModel*> getFriendlyPorts() const;
	std::vector<ShipModel*> GameController::getFriendlyShips() const;
	std::vector<SeaModel*> getSeaCells() const;
	int getNumLines() const;
	int getNumColumns() const;
	int getPlayerCoins() const;
	CellModel* getFriendlyShipPositionByID(int id) const;
	
	//Initial Read From file
	bool readInitialFileConfigs(std::string filename);
	
	bool buyShip(char type);

	bool canMoveShip(ShipModel* ship) const;
	bool moveShip(ShipModel* ship, CellModel* goToPosition);
	bool moveCommand(int id, CellModel* goToPosition);

	void proxCommand();
	void friendlyFleetMovement(std::vector<ShipModel*> friendlyShips);
	void enemyFleetMovement(std::vector<ShipModel*> enemyShips);

	void lostShipMovement(ShipModel* ship);

	CellModel* generateRandomMove(const CellModel* currentCell) const;

	CellModel* getCellAbove(const CellModel* currentCell) const;
	CellModel* getCellBelow(const CellModel* currentCell) const;
	CellModel* getCellRight(const CellModel* currentCell) const;
	CellModel* getCellLeft(const CellModel* currentCell) const;
	//Diagonals
	CellModel* getCellAboveRight(const CellModel* currentCell) const;
	CellModel* getCellAboveLeft(const CellModel* currentCell) const;
	CellModel* getCellBelowRight(const CellModel* currentCell) const;
	CellModel* getCellBelowLeft(const CellModel* currentCell) const;

	//Player coins
	void addCoins(double amount);
	
	void endGame();
};

