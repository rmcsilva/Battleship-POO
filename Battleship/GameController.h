#pragma once
#include "FileManager.h"
#include "Logger.h"
#include "EventModel.h"
#include <map>

class GameController {
	const char* UNSAVED = "Game Not Saved";

	FileManager fileManager;
	Logger logger;
	MapModel *map = nullptr;
	EventModel *event = nullptr;
	GameModel *game = nullptr;
	std::string name = UNSAVED;
	std::map<std::string, GameController*> savedGames;
	bool *onEvent;
	
public:
	GameController();
	~GameController();
	GameController(const GameController &gameController);

	//Gets
	double getFinalScore() const;
	CellModel* getCellAt(int x, int y) const;
	GameState getGameState() const;
	std::vector<PortModel*> getFriendlyPorts() const;
	std::vector<PortModel*> getEnemyPorts() const;
	std::vector<ShipModel*> getFriendlyShips() const;
	std::vector<ShipModel*> getEnemyShips() const;
	std::vector<SeaModel*> getSeaCells() const;
	int getNumLines() const;
	int getNumColumns() const;
	double getPlayerCoins() const;
	CellModel* getFriendlyShipPositionByID(int id) const;
	CellModel* getFriendlyPortPositionByID(char id) const;
	ShipModel* getFriendlyShipByID(int id) const;
	
	EventModel* getEvent() const;

	void setEvent(EventModel* event);
	
	//Initial Read From file
	bool readInitialFileConfigs(std::string filename);
	bool changeGameDifficulty(std::string difficulty);

	//Game Comands
	bool execCommand(std::string filename);
	bool moveCommand(int id, CellModel* goToPosition);
	void proxCommand();
	bool buyShip(char type);
	bool sellShip(char type);
	bool buyMerchCommand(ShipModel* ship, int amount);
	bool sellShipCargoCommand(ShipModel* ship);
	bool spawnEnemyShipAt(CellModel* position, char type);
	bool spawnPositionEvent(char type, CellModel* startingCell);
	bool spawnShipEvent(char type,ShipModel* affectedShip);
	bool orderShipCommand(ShipModel* ship, CellModel* goTo);
	bool autoShipCommand(ShipModel* ship);
	bool stopShipCommand(ShipModel* ship);
	bool buySoldiersCommand(ShipModel* ship, int amount);
	bool saveGameCommand(std::string name);
	bool loadGameCommand(std::string name);
	bool deleteGameCommand(std::string name);
	void setShipsToMap(MapModel* map, std::vector<ShipModel*>ships);
	//Game Logic (make private?)
	void updateFish();

	//Combat Logic
	void shipBattles(std::vector<ShipModel*>friendlyShips);
	bool shipCombat(ShipModel* friendlyShip, ShipModel* enemyShip);
	bool portCombat(ShipModel* attacker, PortModel* port);
	void checkSurroundings(ShipModel* ship);
	void boardShip(ShipModel* attacker, ShipModel* lostShip);

	//Event Logic
	bool hasEvent() const;
	bool spawnRandomEvent();
	void endEvent(EventModel::Type type);
	bool spawnRiotEvent(ShipModel* affectedShip);
	void updateEvent(EventModel* event, GameModel* game, MapModel* map);
	std::vector<SeaModel*> updateAffectedPositions(std::vector<SeaModel*> affectedPositions, MapModel* map);
	ShipModel* updateAffectedShip(ShipModel* affectedShip, GameModel* game);
	std::vector<ShipModel*> updateAffectedShips(std::vector<ShipModel*> affectedShips, GameModel* game);
	//Enemy Ship Spawn Logic
	bool spawnRandomEnemyShip(std::vector<SeaModel*>seaCells, int probability);

	//Map Logic
	std::vector<SeaModel*> getSurroundingSeaCellsInRange2(const CellModel* currentCell) const;

	//Ship Movement Logic
	void friendlyFleetMovement(std::vector<ShipModel*> friendlyShips);
	void enemyFleetMovement(std::vector<ShipModel*> enemyShips);

	bool canMoveShip(ShipModel* ship) const;
	bool moveShip(ShipModel* ship, CellModel* goToPosition);
	void watchingWaves(ShipModel* ship);

	void lostShipMovement(ShipModel* ship);
	void autoShipMovement(ShipModel* ship);
	void orderShipMovement(ShipModel* ship);

	bool canMoveToCell(CellModel* cell);

	void ghostShipMovement(ShipModel* ghost);

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
	double calculateShipValue(ShipModel* ship);
	double calculateShipContentValue(ShipModel* ship);

	bool isGameOver();
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