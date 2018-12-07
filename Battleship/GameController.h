#pragma once
#include "FileManager.h"
#include "Logger.h"

class GameController {
	FileManager fileController;
	Logger logger;
	MapModel *map = nullptr;
	EventModel event;
	GameModel game;

public:
	GameController();
	~GameController();

	//Gets
	CellModel* getCellAt(int x, int y) const;
	GameState getGameState() const;
	std::vector<PortModel*> getFriendlyPorts() const;
	std::vector<PortModel*> getEnemyPorts() const;
	std::vector<ShipModel*> getFriendlyShips() const;
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

	//Game Comands
	bool moveCommand(int id, CellModel* goToPosition);
	void proxCommand();

	//Game Logic (make private?)
	void shipBattles(std::vector<ShipModel*>friendlyShips);
	//TODO: Finish ship combat
	void shipCombat(ShipModel* friendlyShip, ShipModel* enemyShip);
	bool portCombat(ShipModel* attacker, PortModel* port);
	bool spawnRandomEnemyShip(std::vector<SeaModel*>seaCells, int probability);
	void friendlyFleetMovement(std::vector<ShipModel*> friendlyShips);
	void enemyFleetMovement(std::vector<ShipModel*> enemyShips);

	void lostShipMovement(ShipModel* ship);

	//TODO: Change to use getSurrouding method
	CellModel* generateRandomMove(const CellModel* currentCell);

	std::vector<SeaModel*> getSurroundingSeaCells(const CellModel* currentCell);
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

	//Logger Methods
	void addLineToInfoLog(std::string line);
	void addLineToCombatLog(std::string line);
};

std::ostream& operator<<(std::ostream& os, const GameController &gameController);