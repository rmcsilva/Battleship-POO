#include "stdafx.h"
#include "GameController.h"
#include "SailboatModel.h"
#include "GalleonModel.h"
#include "SchoonerModel.h"
#include "FrigateModel.h"
#include "GhostShipModel.h"
#include "Consola.h"

//TODO: Initialize with defaults

GameController::GameController()
{
}

GameController::~GameController()
{
	if (map != nullptr)
		delete(map);
	//TODO: Delete ships and all that was allocated with new
}

CellModel* GameController::getCellAt(int x, int y) const { return map->getCellAt(x, y); }
GameState GameController::getGameState() const { return game.getGameState(); }
std::vector<PortModel*> GameController::getFriendlyPorts() const { return game.getFriendlyPorts(); }
std::vector<PortModel*> GameController::getEnemyPorts() const {return game.getEnemyPorts();}
std::vector<ShipModel*> GameController::getFriendlyShips() const { return game.getFriendlyShips(); }
std::vector<SeaModel*> GameController::getSeaCells() const {return game.getSeaCells();}

int GameController::getNumLines() const { return map->getNumLines(); }
int GameController::getNumColumns() const { return map->getNumColumns(); }
int GameController::getPlayerCoins() const { return game.getPlayerCoins(); }

CellModel* GameController::getFriendlyShipPositionByID(int id) const
{
	// game.getFriendlyShips().at(id-1)->getPosition() Dynamic
	for (auto friendlyShip : game.getFriendlyShips())
	{
		if (friendlyShip->getID()==id)
		{
			return friendlyShip->getPosition();
		}
	}
	return nullptr;
}

bool GameController::readInitialFileConfigs(std::string filename)
{
	if (fileController.readInitialFileConfigs(filename, map, &event, &game)) {
		game.setGameState(GameState::GAME);
		return true;
	}
	return false;
}

bool GameController::buyShip(char type)
{
	//TODO:: Complete! Needs to recieve ship type 
	if (game.getFriendlyPorts().size()>0)
	{
		if (game.canRemoveCoins(game.getShipPrice()))
		{
			ShipModel* ship = nullptr;
			PortModel* position = game.getFriendlyPorts().at(0);
			switch (toupper(type))
			{
				case 'V': ship = new SailboatModel(Owner::PLAYER, position); break;
				case 'G': ship = new GalleonModel(position); break;
				case 'E': ship = new SchoonerModel(position); break;
				case 'F': ship = new FrigateModel(Owner::PLAYER, position); break;
				case 'S': ship = new GhostShipModel(position); break;
				default: return false;
			}
			if (ship!=nullptr)
			{
				game.removeCoins(game.getShipPrice());
				game.addFriendlyShip(ship);
				game.getFriendlyPorts().at(0)->addShipToPort(ship);
			}
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool GameController::canMoveShip(ShipModel* ship) const {return ship->getNumOfMoves() < ship->getMaxMoves();}

bool GameController::moveShip(ShipModel* ship, CellModel* goToPosition)
{
	if (goToPosition->getType() == CellModel::Type::GROUND)
	{
		return false;
	}
	else
	{
		CellModel* position = ship->getPosition();

		//Check cell that ship is going to
		if (goToPosition->getType() == CellModel::Type::SEA)
		{
			SeaModel* sea = (SeaModel*)goToPosition;

			if (sea->hasShip()) return false;
			//Only moves if cell is empty
			sea->setShip(ship);

		}
		else //Other option left is to go to a port
		{
			PortModel* port = (PortModel*)goToPosition;
			if (port->getOwner() == ship->getOwner())
			{
				port->addShipToPort(ship);
				ship->refillWater();
			}
			else
			{
				//TODO: Combat with enemy port
				//Can only attack empty ports
				if (port->getNumberOfShips()>0) return false;

				//If ship wins battle it will enter the port
				if(portCombat(ship, port))
				{
					port->addShipToPort(ship);
					ship->refillWater();
				} 
				else
				{
					return false;
				}
			}
		}

		//Check initial cell
		if (position->getType() == CellModel::Type::PORT)
		{
			PortModel* port = (PortModel*)position;
			port->removeShipFromPort(ship);
		}
		else //Other option left is to be at a sea cell
		{
			SeaModel* sea = (SeaModel*)position;
			sea->removeShip();
		}

		ship->moveShip(goToPosition);
		return true;
	}
}

bool GameController::moveCommand(int id, CellModel* goToPosition)
{
	try
	{
		//ShipModel* ship = game.getFriendlyShips().at(id - 1); Dynamic ship id

		ShipModel* ship = nullptr;

		for (auto friendlyShip : game.getFriendlyShips())
		{
			if (friendlyShip->getID() == id)
			{
				ship = friendlyShip;
				break;
			}	
		}

		if (ship==nullptr) return false;


		if (canMoveShip(ship))
		{
			if (moveShip(ship, goToPosition))
			{
				ship->setNavigation(Navigation::USER);
				return true;
			}
			return false;
		} 
		else
		{
			return false;
		}
	}
	catch (std::out_of_range e)
	{
		//TODO: Add to log ship doesn't exist
		return false;
	}
}

void GameController::proxCommand()
{
	friendlyFleetMovement(game.getFriendlyShips());
	enemyFleetMovement(game.getEnemyShips());
	shipBattles(game.getFriendlyShips());
	//TODO:Add events
	spawnRandomEnemyShip(game.getSeaCells(), map->getPirateProb());
	logger.addLineToInfoLog("\nNEXT TURN\n");
}

void GameController::shipBattles(std::vector<ShipModel*> friendlyShips)
{
	for(auto friendlyShip : friendlyShips)
	{
		//TODO: Check if ship is on enemy port

		std::vector<SeaModel*> surroundingSeaCells = getSurroundingSeaCells(friendlyShip->getPosition());
		for(auto surroundingSeaCell : surroundingSeaCells)
		{
			if (surroundingSeaCell->hasShip())
			{
				if (surroundingSeaCell->getShipOwner() == Owner::ENEMY)
					shipCombat(friendlyShip, surroundingSeaCell->getShip());
			}
		}
	}
}

void GameController::shipCombat(ShipModel* friendlyShip, ShipModel* enemyShip)
{
	std::ostringstream infoLog, combatLog;
	combatLog << "Ship Combat Between Ship: " << friendlyShip->getID() << " and " << enemyShip->getID() << '\n';

	int friendlyShipSoldiers = friendlyShip->getSoldiers();
	int enemyShipSoldiers = enemyShip->getSoldiers();

	infoLog << "Friendly Ship Soldiers: " << friendlyShipSoldiers << '\n';
	infoLog << "Enemy Ship Soldiers: " << enemyShipSoldiers << '\n';

	int friendlyShipRandom = rand() % friendlyShipSoldiers + 1;
	int enemyShipRandom = rand() % enemyShipSoldiers + 1;

	infoLog << "Friendly Ship Random: " << friendlyShipRandom << '\n';
	infoLog << "Enemy Ship Random: " << enemyShipRandom << '\n';

	int damage;
	//If friendly Ship Wins
	if (friendlyShipRandom > enemyShipRandom)
	{
		combatLog << "Ship " << friendlyShip->getID() <<" Won combat!\n";
		damage = friendlyShip->combatVictory();
		enemyShip->combatDefeat(damage);
	} 
	else
	{
		combatLog << "Ship " << enemyShip->getID() << " Won combat!\n";
		damage = enemyShip->combatVictory();
		friendlyShip->combatDefeat(damage);
	}

	friendlyShipSoldiers = friendlyShip->getSoldiers();
	enemyShipSoldiers = enemyShip->getSoldiers();

	infoLog << "Friendly Ship Soldiers After Combat: " << friendlyShipSoldiers << '\n';
	infoLog << "Enemy Ship Soldiers After Combat: " << enemyShipSoldiers << '\n';

	if (friendlyShipSoldiers==0 && enemyShipSoldiers==0)
	{
		//Remove both ships from game
		game.removeFriendlyShip(friendlyShip);
		game.removeEnemyShip(enemyShip);
		combatLog << "Both Ships Sank!!\n";
	} else if (friendlyShipSoldiers == 0)
	{
		//Enemy Ships gets friendly Ship stuff
		enemyShip->lootShip(friendlyShip);
		game.removeFriendlyShip(friendlyShip);
		combatLog << "Ship " << friendlyShip->getID() << " Sank!\n";
	}else if (enemyShipSoldiers == 0)
	{
		//Friendly Ships gets enemy Ship stuff
		friendlyShip->lootShip(enemyShip);
		game.removeEnemyShip(enemyShip);
		combatLog << "Ship " << enemyShip->getID() << " Sank!\n";
	}

	logger.addLineToInfoLog(infoLog.str());
	logger.addLineToCombatLog(combatLog.str());
}

bool GameController::portCombat(ShipModel* attacker, PortModel* port)
{
	std::ostringstream infoLog, combatLog;
	combatLog << "Port Combat between Port: " << port->getID() << " and Ship: " << attacker->getID() <<'\n';

	//generate random number from 0 to 100
	int random = rand() % 100 + 1;
	infoLog << "Random number for Port Combat: " << random;

	//Attacker wins if random number is less than equal than the ships soldier number
	if(random <= attacker->getSoldiers())
	{
		//Change port owners
		game.changePortOwner(port);
		combatLog << "Ship won the battle! \n";
	}
	else
	{
		//Afunadr navio?
		attacker->portCombat();
		combatLog << "Port won the battle! \n";
		return false;
	}

	attacker->portCombat();

	if (attacker->getSoldiers()==0)
	{
		if (attacker->getOwner() == Owner::PLAYER)
			game.removeFriendlyShip(attacker);
		else
			game.removeEnemyShip(attacker);
		logger.addLineToCombatLog(combatLog.str());
		return false;
	}

	logger.addLineToInfoLog(infoLog.str());
	logger.addLineToCombatLog(combatLog.str());

	return true;
}

bool GameController::spawnRandomEnemyShip(std::vector<SeaModel*> seaCells, int probability)
{
	std::ostringstream log;
	//generate random number from 0 to 99
	int random = rand() % 100;

	log << "Enemy Ship random number: " << random << '\n';
	
	if (random < probability)
	{
		//Spawn enemy ship
		bool cellHasShip = true;
		int position;
		do
		{
			position = rand() % seaCells.size();
			cellHasShip = seaCells.at(position)->hasShip();
		} while (cellHasShip);

		CellModel* cell = (CellModel*)seaCells.at(position);

		//generate two random values 0 or 1
		int type = rand() % 2;

		ShipModel* enemyShip;

		if (type==0)
			enemyShip = new FrigateModel(Owner::ENEMY, cell);
		else 
			enemyShip = new SailboatModel(Owner::ENEMY, cell);

		//Add ship to vector and sets ship position
		game.addPirateShip(enemyShip);
		seaCells.at(position)->setShip(enemyShip);

		log << "Spawning random " << enemyShip->getAsString() << " at x: ";
		log << cell->getX() + 1 << " y: " << cell->getY() + 1;
		 
		logger.addLineToInfoLog(log.str());

		return true;
	}

	return false;
}

void GameController::friendlyFleetMovement(std::vector<ShipModel*> friendlyShips)
{
	for (ShipModel* friendlyShip : friendlyShips)
	{
		if (canMoveShip(friendlyShip))
		{
			switch (friendlyShip->getNavigation())
			{
				//TODO: Implement 
				case Navigation::AUTO: break;
				case Navigation::ORDER: break;
				case Navigation::LOST: lostShipMovement(friendlyShip); break;
			default: break;
			}
		}

		if (friendlyShip->getPosition()->getType()==CellModel::Type::SEA) 
			friendlyShip->navigationCost();

		friendlyShip->resetMoves();
	}
}

void GameController::enemyFleetMovement(std::vector<ShipModel*> enemyShips)
{
	for (ShipModel* enemyShip : enemyShips)
	{
		if (canMoveShip(enemyShip))
		{
			//TODO: Pirate ships will move on auto only later on
			switch (enemyShip->getNavigation())
			{
				//TODO: Implement 
				case Navigation::AUTO: break;
				//TODO: Enemy ships will only use auto movement
				case Navigation::LOST: lostShipMovement(enemyShip); break;
				default: break;
			}
		}
		enemyShip->resetMoves();
	}
}

void GameController::lostShipMovement(ShipModel* ship)
{
	std::ostringstream os;
	os << "Random Movement Ship -> " << ship->getAsString() << " ID: " << ship->getID();
	os << " Position: x " << ship->getPosition()->getX() << " y: " << ship->getPosition()->getY();
	logger.addLineToInfoLog(os.str());

	do {
		while (!moveShip(ship, generateRandomMove(ship->getPosition())));
	} while (canMoveShip(ship));
}

CellModel* GameController::generateRandomMove(const CellModel* currentCell)
{
	int randomNumber = rand() % 8 + 1;
	

	switch (randomNumber)
	{
		case 1:
			logger.addLineToInfoLog("Cell Above");
			return getCellAbove(currentCell);
		case 2:
			logger.addLineToInfoLog("Cell Bellow");
			return getCellBelow(currentCell);
		case 3:
			logger.addLineToInfoLog("Cell Right");
			return getCellRight(currentCell);
		case 4:
			logger.addLineToInfoLog("Cell Left");
			return getCellLeft(currentCell);
		case 5:
			logger.addLineToInfoLog("Cell Above Right");
			return getCellAboveRight(currentCell);
		case 6:
			logger.addLineToInfoLog("Cell Above Left");
			return getCellAboveLeft(currentCell);
		case 7:
			logger.addLineToInfoLog("Cell Below Right");
			return getCellBelowRight(currentCell);
		case 8:
			logger.addLineToInfoLog("Cell Below Left");
			return getCellBelowLeft(currentCell);
	}
}

std::vector<SeaModel*> GameController::getSurroundingSeaCells(const CellModel* currentCell)
{
	std::vector<SeaModel*> seaCells;

	CellModel* cellTmp;

	cellTmp = getCellAbove(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellBelow(currentCell);
	if(cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellRight(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellLeft(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellAboveRight(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellAboveLeft(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellBelowRight(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellBelowLeft(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	return seaCells;
}

CellModel* GameController::getCellAbove(const CellModel* currentCell) const {return map->getCellAbove(currentCell);}
CellModel* GameController::getCellBelow(const CellModel* currentCell) const {return map->getCellBelow(currentCell);}
CellModel* GameController::getCellRight(const CellModel* currentCell) const {return map->getCellRight(currentCell);}
CellModel* GameController::getCellLeft(const CellModel* currentCell) const {return map->getCellLeft(currentCell);}
CellModel* GameController::getCellAboveRight(const CellModel* currentCell) const {return map->getCellAboveRight(currentCell);}
CellModel* GameController::getCellAboveLeft(const CellModel* currentCell) const {return map->getCellAboveLeft(currentCell);}
CellModel* GameController::getCellBelowRight(const CellModel* currentCell) const {return map->getCellBelowRight(currentCell);}
CellModel* GameController::getCellBelowLeft(const CellModel* currentCell) const {return map->getCellBelowLeft(currentCell);}

void GameController::addCoins(double amount) {game.addCoins(amount);}

void GameController::endGame() {game.setGameState(GameState::END);}

void GameController::addLineToInfoLog(std::string line) {logger.addLineToInfoLog(line);}
void GameController::addLineToCombatLog(std::string line) {logger.addLineToCombatLog(line);}
