#pragma once
#include "FileManager.h"
#include "Logger.h"
#include "EventModel.h"
#include <map>

class GameController {
	FileManager fileManager;
	Logger logger;
	MapModel *map = nullptr;
	EventModel *event = nullptr;
	GameModel game;
	std::map<std::string, GameController*> savedGames;

public:
	GameController();
	~GameController();
	GameController(const GameController &game);

	//Gets
	CellModel* getCellAt(int x, int y) const;
	GameState getGameState() const;
	std::vector<PortModel*> getFriendlyPorts() const;
	std::vector<PortModel*> getEnemyPorts() const;
	std::vector<ShipModel*> getFriendlyShips() const;
	std::vector<SeaModel*> getSeaCells() const;
	int getNumLines() const;
	int getNumColumns() const;
	double getPlayerCoins() const;
	CellModel* getFriendlyShipPositionByID(int id) const;
	CellModel* getFriendlyPortPositionByID(char id) const;
	ShipModel* getFriendlyShipByID(int id) const;
	
	EventModel* getEvent() const;
	
	//Initial Read From file
	bool readInitialFileConfigs(std::string filename);

	bool canMoveShip(ShipModel* ship) const;
	bool moveShip(ShipModel* ship, CellModel* goToPosition);

	//Game Comands
	bool execCommand(std::string filename);
	bool moveCommand(int id, CellModel* goToPosition);
	void proxCommand();
	bool buyShip(char type);
	bool spawnEnemyShipAt(CellModel* position, char type);
	bool spawnPositionEvent(char type, CellModel* startingCell);
	bool spawnShipEvent(char type,ShipModel* affectedShip);
	bool orderShipCommand(ShipModel* ship, CellModel* goTo);
	bool saveGameCommand(std::string name);
	bool loadGameCommand(std::string name);
	//Game Logic (make private?)
	//Combat Logic
	void shipBattles(std::vector<ShipModel*>friendlyShips);
	bool shipCombat(ShipModel* friendlyShip, ShipModel* enemyShip);
	bool portCombat(ShipModel* attacker, PortModel* port);

	//Event Logic
	bool hasEvent() const;
	bool spawnRandomEvent();
	//TODO: make event actions to sink ships and such
	void endEvent(EventModel::Type type);
	bool spawnRiotEvent(ShipModel* affectedShip);
	//Enemy Ship Spawn Logic
	bool spawnRandomEnemyShip(std::vector<SeaModel*>seaCells, int probability);

	//Ship Movement Logic
	void friendlyFleetMovement(std::vector<ShipModel*> friendlyShips);
	void enemyFleetMovement(std::vector<ShipModel*> enemyShips);

	void lostShipMovement(ShipModel* ship);
	void autoShipMovement(ShipModel* ship);
	void orderShipMovement(ShipModel* ship);

	CellModel* goToCell(CellModel* current, CellModel* goTo);

	CellModel* generateRandomMove(const CellModel* currentCell);

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
	void addLineToEnemyLog(std::string line);
	std::string getCombatLog();
	std::string getEventLog();
	std::string getEnemyLog();
	void flushLogs();
};

std::ostream& operator<<(std::ostream& os, const GameController &gameController);