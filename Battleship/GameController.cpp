#include "stdafx.h"
#include "GameController.h"
#include "SailboatModel.h"
#include "GalleonModel.h"
#include "SchoonerModel.h"
#include "FrigateModel.h"
#include "GhostShipModel.h"
#include "Consola.h"
#include "LullModel.h"
#include "MermaidModel.h"
#include "RiotModel.h"
#include "StormModel.h"
#include "GameUtil.h"

GameController::GameController()
{
	game = new GameModel();
	onEvent = new bool();
}

GameController::~GameController()
{
	if (map != nullptr)  delete(map);
	if (*onEvent) delete(event);
	delete game;
	delete onEvent;

	for (auto savedGame : savedGames) {
		if (savedGame.first != name) {
			delete(savedGame.second);
		}
	}
}

GameController::GameController(const GameController& gameController)
{
	map = new MapModel(*gameController.map);
	game = new GameModel(*gameController.game);
	setShipsToMap(map, game->getFriendlyShips());
	setShipsToMap(map, game->getEnemyShips());

	if (gameController.hasEvent()) {
		event = gameController.event->clone();
		updateEvent(event, game, map);
		onEvent = new bool();
		*onEvent = gameController.onEvent;
	} else {
		onEvent = new bool();
		event = nullptr;
	}
}

double GameController::getFinalScore() const {return game->getPlayerScore();}
CellModel* GameController::getCellAt(int x, int y) const { return map->getCellAt(x, y); }
GameState GameController::getGameState() const { return game->getGameState(); }
std::vector<PortModel*> GameController::getFriendlyPorts() const { return map->getFriendlyPorts(); }
std::vector<PortModel*> GameController::getEnemyPorts() const {return map->getEnemyPorts();}
std::vector<ShipModel*> GameController::getFriendlyShips() const { return game->getFriendlyShips(); }
std::vector<ShipModel*> GameController::getEnemyShips() const { return game->getEnemyShips(); }
std::vector<SeaModel*> GameController::getSeaCells() const {return map->getSeaCells();}

int GameController::getNumLines() const { return map->getNumLines(); }
int GameController::getNumColumns() const { return map->getNumColumns(); }
double GameController::getPlayerCoins() const { return game->getPlayerCoins(); }

CellModel* GameController::getFriendlyShipPositionByID(int id) const
{
	// game.getFriendlyShips().at(id-1)->getPosition() Dynamic
	for (auto friendlyShip : game->getFriendlyShips())
	{
		if (friendlyShip->getID()==id)
		{
			return friendlyShip->getPosition();
		}
	}
	return nullptr;
}

CellModel* GameController::getFriendlyPortPositionByID(char id) const
{
	for(auto friendlyPort : map->getFriendlyPorts())
	{
		if (friendlyPort->getID()==id)
		{
			int x = friendlyPort->getX();
			int y = friendlyPort->getY();
			return getCellAt(x, y);
		}
	}
	return nullptr;
}

ShipModel* GameController::getFriendlyShipByID(int id) const
{
	for (auto friendlyShip : game->getFriendlyShips())
	{
		if (friendlyShip->getID() == id)
		{
			return friendlyShip;
		}
	}
	return nullptr;
}

EventModel* GameController::getEvent() const {return event;}

void GameController::setEvent(EventModel* event) {this->event = event;}

bool GameController::readInitialFileConfigs(std::string filename)
{
	if (fileManager.readInitialFileConfigs(filename, map, game)) {
		game->setGameState(GameState::GAME);
		return true;
	}
	return false;
}

bool GameController::changeGameDifficulty(std::string difficulty)
{
	if (difficulty == "facil")
	{
		game->setPlayerCoins(COINS_EASY);
		game->setEventProbability(EVENT_PROB_EASY);
		game->setStormEventProbability(STORM_EVENT_PROB_EASY);
		game->setMermaidEventProbability(MERMAID_EVENT_PROB_EASY);
		game->setCalmEventProbability(LULL_EVENT_PROB_EASY);
		game->setRiotEventProbability(RIOT_EVENT_PROB_EASY);
		game->setShipPrice(SHIP_PRICE_EASY);
		game->setSoldierPrice(SOLDIER_PRICE_EASY);
		game->setFishSellPrice(FISH_SELL_PRICE_EASY);
		game->setMerchSellPrice(MERCH_SELL_PRICE_EASY);
		game->setMerchBuyPrice(MERCH_BUY_PRICE_EASY);
		return true;
	} else if(difficulty == "media") {
		game->setPlayerCoins(COINS_MEDIUM);
		game->setEventProbability(EVENT_PROB_MEDIUM);
		game->setStormEventProbability(STORM_EVENT_PROB_MEDIUM);
		game->setMermaidEventProbability(MERMAID_EVENT_PROB_MEDIUM);
		game->setCalmEventProbability(LULL_EVENT_PROB_MEDIUM);
		game->setRiotEventProbability(RIOT_EVENT_PROB_MEDIUM);
		game->setShipPrice(SHIP_PRICE_MEDIUM);
		game->setSoldierPrice(SOLDIER_PRICE_MEDIUM);
		game->setFishSellPrice(FISH_SELL_PRICE_MEDIUM);
		game->setMerchSellPrice(MERCH_SELL_PRICE_MEDIUM);
		game->setMerchBuyPrice(MERCH_BUY_PRICE_MEDIUM);
		return true;
	} else if(difficulty == "dificil") {
		game->setPlayerCoins(COINS_HARD);
		game->setEventProbability(EVENT_PROB_HARD);
		game->setStormEventProbability(STORM_EVENT_PROB_HARD);
		game->setMermaidEventProbability(MERMAID_EVENT_PROB_HARD);
		game->setCalmEventProbability(LULL_EVENT_PROB_HARD);
		game->setRiotEventProbability(RIOT_EVENT_PROB_HARD);
		game->setShipPrice(SHIP_PRICE_HARD);
		game->setSoldierPrice(SOLDIER_PRICE_HARD);
		game->setFishSellPrice(FISH_SELL_PRICE_HARD);
		game->setMerchSellPrice(MERCH_SELL_PRICE_HARD);
		game->setMerchBuyPrice(MERCH_BUY_PRICE_HARD);
		return true;
	}
	return false;
}

bool GameController::buyShip(char type)
{
	if (map->getFriendlyPorts().size()>0)
	{
		if (game->canRemoveCoins(game->getShipPrice()))
		{
			ShipModel* ship = nullptr;
			PortModel* position = map->getFriendlyPorts().at(0);
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
				game->removeCoins(game->getShipPrice());
				game->addFriendlyShip(ship);
				if (map->getFriendlyPorts().size()>0) {
					map->getFriendlyPorts().at(0)->addShipToPort(ship);
				} else {
					return false;
				}
				
			}
			return true;
		}
	}
	return false;
}

bool GameController::sellShip(char type)
{
	if (map->getFriendlyPorts().size() > 0)
	{
		ShipModel::Type shipType;
		switch (toupper(type))
		{
			case 'V': shipType = ShipModel::Type::SAILBOAT; break;
			case 'G': shipType = ShipModel::Type::GALLEON; break;
			case 'E': shipType = ShipModel::Type::SCHOONER; break;
			case 'F': shipType = ShipModel::Type::FRIGATE; break;
			case 'S': shipType = ShipModel::Type::GHOST; break;
			default: return false;
		}

		for (auto friendlyPort : map->getFriendlyPorts())
		{
			std::vector<ShipModel*> ships = friendlyPort->getShips();
			for (int i = 0;  i < ships.size(); i++)
			{
				if (ships.at(i)->getType()==shipType) {
					ShipModel* ship = ships.at(i);
					game->addCoins(calculateShipValue(ship));
					friendlyPort->removeShipFromPort(ship);
					game->removeFriendlyShip(ship);
					return true;
				}
			}
		}
		return false;
	}
	return false;
}

bool GameController::buyMerchCommand(ShipModel* ship, int amount)
{
	double cost = game->getMerchBuyPrice() * amount;

	for (auto friendlyPort : map->getFriendlyPorts())
	{
		std::vector<ShipModel*> ships = friendlyPort->getShips();
		for (int i = 0; i < ships.size(); i++)
		{
			if (ships.at(i)->getID() == ship->getID()) {
				if (game->canRemoveCoins(cost)) {
					if (ship->canAddToShipCargo(amount)) {
						ship->addMerchToShip(amount);
						game->removeCoins(cost);
						return true;
					}
					return false;
				}
				return false;
			}
		}
	}
	return false;
}

bool GameController::sellShipCargoCommand(ShipModel* ship)
{
	for (auto friendlyPort : map->getFriendlyPorts())
	{
		std::vector<ShipModel*> ships = friendlyPort->getShips();
		for (int i = 0; i < ships.size(); i++)
		{
			if (ships.at(i)->getID() == ship->getID()) {
				if (ship->getCapacity() > 0) {
					double value = calculateShipContentValue(ship);
					ship->empyShipCargo();
					game->addCoins(value);
					return true;
				}
				return false;
			}
		}
	}
	return false;
}

bool GameController::spawnEnemyShipAt(CellModel* position, char type)
{
	if (position->getType() == CellModel::Type::GROUND)
		return false;

	SeaModel* seaCell = nullptr;
	PortModel* portCell = nullptr;

	if (position->getType() == CellModel::Type::SEA) {
		seaCell = (SeaModel*)position;
		if (seaCell->hasShip()) {
			return false;
		}
	} else if (position->getType() == CellModel::Type::PORT) {
		portCell = (PortModel*)position;
		if (portCell->getOwner() == Owner::PLAYER) {
			return false;
		}
	}

	ShipModel* ship = nullptr;

	switch (toupper(type))
	{
		case 'V': ship = new SailboatModel(Owner::ENEMY, position); break;
		case 'F': ship = new FrigateModel(Owner::ENEMY, position); break;
		default: return false;
	}

	if (ship != nullptr)
	{
		if (seaCell!=nullptr) {
			seaCell->setShip(ship);
		}else{
			portCell->addShipToPort(ship);
		}
		game->addPirateShip(ship);
		return true;
	}

	return false;
}

bool GameController::spawnPositionEvent(char type, CellModel* startingCell)
{
	std::vector<SeaModel*> affectedPositions = map->get2x2ContinuousSeaCells(startingCell);

	if (affectedPositions.size() == 0) return false;

	switch (toupper(type))
	{
	case 'C': event = new LullModel(affectedPositions); break;
	case 'T': event = new StormModel(affectedPositions); break;
	default: return false;
	}
	*onEvent = true;
	return true;
}

bool GameController::spawnShipEvent(char type, ShipModel* affectedShip)
{
	if (hasEvent()) return false;
	if (affectedShip->getOwner() == Owner::ENEMY) return false;

	switch (toupper(type))
	{
		case 'M': 
		if (spawnRiotEvent(affectedShip)){
			event = new RiotModel(affectedShip);
			*onEvent = true;
			return true;
		} else {
			*onEvent = false;
			event = nullptr;
			return false;
		}		
		case 'S': event = new MermaidModel(affectedShip); break;
		default: return false;
	}
	*onEvent = true;
	return true;
}

bool GameController::orderShipCommand(ShipModel* ship, CellModel* goTo)
{
	if (goTo->getType() == CellModel::Type::GROUND) return false;

	ship->setGoTo(goTo);
	ship->setNavigation(Navigation::ORDER);
	return true;
}

bool GameController::autoShipCommand(ShipModel* ship)
{
	ship->setNavigation(Navigation::AUTO);
	ship->setGoTo(nullptr);
	return true;
}

bool GameController::stopShipCommand(ShipModel* ship)
{
	ship->setNavigation(Navigation::USER);
	ship->setGoTo(nullptr);
	return true;
}

bool GameController::buySoldiersCommand(ShipModel* ship, int amount)
{
	double cost = game->getSoldierPrice() * amount;

	for (auto friendlyPort : map->getFriendlyPorts())
	{
		std::vector<ShipModel*> ships = friendlyPort->getShips();
		for (int i = 0; i < ships.size(); i++)
		{
			if (ships.at(i)->getID() == ship->getID()) {
				if (game->canRemoveCoins(cost)) {
					if (ship->canAddSoldiersToShip(amount)) {
						ship->addSoldiersToShip(amount);
						game->removeCoins(cost);
						return true;
					}
					return false;
				}
				return false;
			}
		}
	}
	return false;
}

bool GameController::saveGameCommand(std::string name)
{
	if (savedGames.count(name)) {
		return false;
	} else {
		GameController* save = new GameController(*this);
		save->name = name;
		savedGames.insert(std::pair<std::string, GameController*>(name, save));
		return true;
	}	
}

bool GameController::loadGameCommand(std::string name)
{
	if (this->name == name) return false;

	if (savedGames.count(name)) {
		//Checks if there is an event going to clone it
		if(hasEvent()) {
			for (auto savedGame : savedGames) {
				if(savedGame.first==this->name) {
					if (savedGame.second->event != event) {
						savedGame.second->setEvent(this->event->clone());
					}
					
					break;
				}
			}
		}

		for (auto save : savedGames) {
			if (save.first == name) {
				MapModel* oldMap = map;
				EventModel* oldEvent = event;
				GameModel* oldGame = game;
				bool *oldOnEvent = onEvent;

				GameController* game = save.second;
				this->map = game->map;
				this->game = game->game;
				this->onEvent = game->onEvent;
				if(game->hasEvent()) {
					this->event = game->event;
				} else {
					this->event = nullptr;
				}

				if (this->name == UNSAVED) {
					if (oldMap != nullptr) delete(oldMap);
					if (oldEvent != nullptr) delete(oldEvent);
					delete(oldGame);
					delete(oldOnEvent);
				}
				this->name = game->name;
				
				return true;
			}
		}	
	}
	return false;
}

bool GameController::deleteGameCommand(std::string name)
{
	if (this->name == name) return false;

	if (savedGames.count(name)) {
		auto it = savedGames.find(name);
		savedGames.erase(it);
		return true;
	}

	return false;
}

void GameController::setShipsToMap(MapModel* map, std::vector<ShipModel*> ships)
{
	for (auto ship : ships)
	{
		CellModel* position = ship->getPosition();
		//Checks if ship is at sea
		if (position->getType()==CellModel::Type::SEA) {
			int x = position->getX();
			int y = position->getY();
			CellModel* cell = map->getCellAt(x, y);
			ship->setPosition(cell);
			SeaModel* sea = (SeaModel*)cell;
			sea->setShip(ship);	
		} else {
			//Ship is at a port
			int x = position->getX();
			int y = position->getY();
			CellModel* cell = map->getCellAt(x, y);
			ship->setPosition(cell);
			PortModel* port = (PortModel*)cell;
			port->addShipToPort(ship);
		}
	}
}

void GameController::updateFish()
{
	for (auto seaCell : map->getSeaCells()) {
		if (!seaCell->hasFish()) {
			seaCell->updateCountdown();
		}
	}
}

bool GameController::execCommand(std::string filename)
{
	return fileManager.executeCommandsFromFile(filename, this);
}

bool GameController::moveCommand(int id, CellModel* goToPosition)
{
	try
	{
		//ShipModel* ship = game.getFriendlyShips().at(id - 1); Dynamic ship id

		ShipModel* ship = nullptr;

		for (auto friendlyShip : game->getFriendlyShips())
		{
			if (friendlyShip->getID() == id)
			{
				ship = friendlyShip;
				break;
			}	
		}

		if (ship==nullptr) return false;
		if (ship->getType() == ShipModel::Type::GHOST) return false;

		if (ship->getOwner()==Owner::LOST) return false;


		if (canMoveShip(ship))
		{
			if (moveShip(ship, goToPosition))
			{
				ship->setNavigation(Navigation::USER);
				return true;
			}
			return false;
		}

	}
	catch (std::out_of_range e)
	{
		logger.addLineToInfoLog("Ship does not exist!!");
		return false;
	}
}

void GameController::proxCommand()
{
	friendlyFleetMovement(game->getFriendlyShips());
	enemyFleetMovement(game->getEnemyShips());
	shipBattles(game->getFriendlyShips());
	updateFish();
	if (hasEvent()) {
		if (!event->executeEvent())
		{
			logger.addLineToInfoLog("Event ended!");
			endEvent(event->getType());
			delete(event);
			event = nullptr;
			*onEvent = false;
		}
		else
		{
			//Check if events that affect ships can continue
			if (event->getType()==EventModel::Type::RIOT)
			{
				RiotModel* riot = (RiotModel*)event;
				if (riot->getAffectedShip()==nullptr) {
					logger.addLineToInfoLog("Riot Event ended Ship Sank!");
					endEvent(EventModel::Type::RIOT);
					delete(event);
					event = nullptr;
					*onEvent = false;
				}
			} else if(event->getType()==EventModel::Type::MERMAID) {
				MermaidModel* mermaid = (MermaidModel*)event;
				if (mermaid->getAffectedShip()==nullptr) {
					logger.addLineToInfoLog("Mermaid Event ended Ship Sank!");
					endEvent(EventModel::Type::MERMAID);
					delete(event);
					event = nullptr;
					*onEvent = false;
				}
			}else {
				logger.addLineToEventLog("Event still going!");
			}
			
		}	
	} else {
		if (spawnRandomEvent()) *onEvent = true;
		else *onEvent = false;
	}
	spawnRandomEnemyShip(map->getSeaCells(), map->getPirateProb());
	if (isGameOver()) endGame();
	logger.addLineToInfoLog("\nNEXT TURN\n");
}

void GameController::shipBattles(std::vector<ShipModel*> friendlyShips)
{
	for(auto friendlyShip : friendlyShips)
	{
		std::vector<SeaModel*> surroundingSeaCells = map->getSurroundingSeaCells(friendlyShip->getPosition());
		for(auto surroundingSeaCell : surroundingSeaCells)
		{
			if (surroundingSeaCell->hasShip())
			{
				if (surroundingSeaCell->getShipOwner() == Owner::ENEMY) {
					if(!shipCombat(friendlyShip, surroundingSeaCell->getShip())) 
						break;
				}
			}
		}
	}
}

bool GameController::shipCombat(ShipModel* friendlyShip, ShipModel* enemyShip)
{
	std::ostringstream infoLog, combatLog;
	if (friendlyShip==nullptr || enemyShip==nullptr)
	{
		infoLog << "Ship already sank, list update error nullptr!\n";
		logger.addLineToInfoLog(infoLog.str());
		return false;
	}

	int friendlyShipSoldiers = friendlyShip->getSoldiers();
	int enemyShipSoldiers = enemyShip->getSoldiers();

	if (friendlyShipSoldiers == 0 || enemyShipSoldiers == 0)
	{
		infoLog << "Ship already sank, list update error!\n";
		logger.addLineToInfoLog(infoLog.str());
		return false;
	}

	combatLog << "Ship Combat Between Ship: " << friendlyShip->getID() << " and " << enemyShip->getID() << '\n';

	infoLog << "Ship Combat Between Ship: " << friendlyShip->getID() << " and " << enemyShip->getID() << '\n';
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
		game->removeFriendlyShip(friendlyShip);
		game->removeEnemyShip(enemyShip);
		combatLog << "Both Ships Sank!!\n";
		friendlyShip = nullptr;
		enemyShip = nullptr;
		logger.addLineToInfoLog(infoLog.str());
		logger.addLineToCombatLog(combatLog.str());
		return false;
	} else if (friendlyShipSoldiers == 0)
	{
		combatLog << "Ship " << friendlyShip->getID() << " Sank!\n";
		//Enemy Ships gets friendly Ship stuff
		enemyShip->lootShip(friendlyShip);
		//If ship on Mermaid Event Sinks
		if (hasEvent()) {
			if (event->getType() == EventModel::Type::MERMAID) {
				MermaidModel* mermaid = (MermaidModel*)event;
				mermaid->setAffectedShip(nullptr);
			}
		}
		game->removeFriendlyShip(friendlyShip);
		friendlyShip = nullptr;
		logger.addLineToInfoLog(infoLog.str());
		logger.addLineToCombatLog(combatLog.str());
		return false;
	}else if (enemyShipSoldiers == 0)
	{
		combatLog << "Ship " << enemyShip->getID() << " Sank!\n";
		//Friendly Ships gets enemy Ship stuff
		friendlyShip->lootShip(enemyShip);
		//If ship on Riot Event Sinks
		if (hasEvent()) {
			if (event->getType()==EventModel::Type::RIOT) {
				RiotModel* riot = (RiotModel*)event;
				riot->setAffectedShip(nullptr);
			}
		}
		game->removeEnemyShip(enemyShip);
		enemyShip = nullptr;
	}
	logger.addLineToInfoLog(infoLog.str());
	logger.addLineToCombatLog(combatLog.str());
	return true;
}

bool GameController::portCombat(ShipModel* attacker, PortModel* port)
{
	std::ostringstream infoLog, combatLog;
	combatLog << "Port Combat between Port: " << port->getID() << " and Ship: " << attacker->getID() <<'\n';

	//generate random number from 0 to 100
	int random = rand() % 101;
	infoLog << "Random number for Port Combat: " << random;

	//Attacker wins if random number is less than equal than the ships soldier number
	if(random <= attacker->getSoldiers())
	{
		//Change port owners
		map->changePortOwner(port);
		combatLog << "Ship won the battle! \n";
	}
	else
	{
		//Sink Ship Because Battle was lost
		attacker->portCombat();
		combatLog << "Port won the battle! Ship " << attacker->getID() << " down! \n";

		if (attacker->getOwner()==Owner::PLAYER)
			game->removeFriendlyShip(attacker);
		else
			game->removeEnemyShip(attacker);
	
		logger.addLineToInfoLog(infoLog.str());
		logger.addLineToCombatLog(combatLog.str());
		return false;
	}

	attacker->portCombat();

	if (attacker->getSoldiers()==0)
	{
		if (attacker->getOwner() == Owner::PLAYER)
			game->removeFriendlyShip(attacker);
		else
			game->removeEnemyShip(attacker);
		logger.addLineToCombatLog(combatLog.str());
		return false;
	}

	logger.addLineToInfoLog(infoLog.str());
	logger.addLineToCombatLog(combatLog.str());

	return true;
}

void GameController::checkSurroundings(ShipModel* ship)
{

	std::vector<SeaModel*>surroudingSeaCells = map->getSurroundingSeaCells(ship->getPosition());

	if (ship->getOwner()==Owner::PLAYER)
	{
		for (auto surroundingSeaCell : surroudingSeaCells)
		{
			if (surroundingSeaCell->hasShip()) {
				ShipModel* surroundingShip = surroundingSeaCell->getShip();
				//Checks if ship is lost
				if (surroundingShip->getOwner() == Owner::LOST) {
					boardShip(ship, surroundingShip);
				}

				//Checks if there is any schooner to trasnfer fish from
				if (surroundingShip->getType()==ShipModel::Type::SCHOONER) {
					if (ship->getType()==ShipModel::Type::SAILBOAT || ship->getType() == ShipModel::Type::GALLEON) {
						ship->transferFish(surroundingShip);
					}	
				}
			}
		}
	} else {
		//Enemy check
		for (auto surroundingSeaCell : surroudingSeaCells)
		{
			if (surroundingSeaCell->hasShip()) {
				ShipModel* surroundingShip = surroundingSeaCell->getShip();
				//Checks if ship is lost
				if (surroundingShip->getOwner() == Owner::LOST) {
					boardShip(ship, surroundingShip);
				}
			}
		}
	}
	
}

void GameController::boardShip(ShipModel* attacker, ShipModel* lostShip)
{
	if (attacker->getOwner()==Owner::PLAYER) {
		attacker->conquerShip(lostShip);
		lostShip->setOwner(Owner::PLAYER);
		lostShip->setNavigation(Navigation::AUTO);
	} else {
		if (lostShip->getType() == ShipModel::Type::FRIGATE || lostShip->getType()==ShipModel::Type::SAILBOAT) {
			attacker->conquerShip(lostShip);
			game->changeShipOwner(lostShip, Navigation::AUTO);
		} else {
			game->removeFriendlyShip(lostShip);
		}
	}
}

bool GameController::hasEvent() const {return *onEvent;}

bool GameController::spawnRandomEvent() 
{
	std::ostringstream infoLog, eventLog;

	int random = rand() % 100;
	infoLog << "Event probability number: " << random << '\n';

	if (random < game->getEventProbability())
	{
		int lullProb = game->getLullEventProbability();
		int mermaidProb = game->getMermaidEventProbability() + lullProb;
		int riotProb = game->getRiotEventProbability() + mermaidProb;
		int stormProb = game->getStormEventProbability() + riotProb;

		int probabilitySum = stormProb;

		int randomEvent = rand() % probabilitySum;

		infoLog << "Event type random number: " << randomEvent << '\n';

		if (randomEvent < lullProb)
		{
			eventLog << "A lull event appeared!";

			std::vector<SeaModel*> affectedPositions = map->getRandom2x2ContinuousSeaCells();

			for (auto affectedPosition : affectedPositions)
				infoLog << "Affected cell x: " << affectedPosition->getX() << " y: " << affectedPosition->getY() << '\n';

			event = new LullModel(affectedPositions);
		}
		else if (randomEvent < mermaidProb)
		{
			eventLog << "A mermaid event appeared!\n";

			const int totalOfFriendlyShips = game->getFriendlyShips().size();

			if (totalOfFriendlyShips==0)
			{
				eventLog << "Mermaids are singing for the fishes!";
				logger.addLineToInfoLog(infoLog.str());
				logger.addLineToEventLog(eventLog.str());
				return false;
			}

			const int randomPosition = rand() % totalOfFriendlyShips;

			ShipModel* affectedShip = game->getFriendlyShips().at(randomPosition);

			eventLog << "Mermaids are singing  for ship " << affectedShip->getID();
			infoLog << "Affected Ship: " << affectedShip->getID() << '\n';

			event = new MermaidModel(affectedShip);
		} 
		else if (randomEvent < riotProb)
		{
			eventLog << "A riot event appeared!";

			const int totalOfFriendlyShips = game->getFriendlyShips().size();

			if (totalOfFriendlyShips == 0)
			{
				eventLog << "\nNo riots today!";
				logger.addLineToInfoLog(infoLog.str());
				logger.addLineToEventLog(eventLog.str());
				return false;
			}

			const int randomPosition = rand() % totalOfFriendlyShips;

			ShipModel* affectedShip = game->getFriendlyShips().at(randomPosition);

			if(spawnRiotEvent(affectedShip))
			{
				event = new RiotModel(affectedShip);
				*onEvent = true;
				return true;
			} else
			{
				*onEvent = false;
				event = nullptr;
				return false;
			}
		} 
		else
		{
			eventLog << "A storm event appeared!";

			std::vector<SeaModel*> affectedPositions = map->getRandom2x2ContinuousSeaCells();

			for (auto affectedPosition : affectedPositions)
				infoLog << "Affected cell x: " << affectedPosition->getX() << " y: " << affectedPosition->getY() << '\n';

			event = new StormModel(affectedPositions);
		}

		logger.addLineToInfoLog(infoLog.str());
		logger.addLineToEventLog(eventLog.str());
		return true;
	}

	eventLog << "No events appeared this turn!";

	logger.addLineToInfoLog(infoLog.str());
	logger.addLineToEventLog(eventLog.str());
	return false;
}

void GameController::endEvent(EventModel::Type type)
{
	switch (type)
	{
		case EventModel::Type::LULL: {
			LullModel* lull = (LullModel*)event;
			game->addCoins(lull->getTotalGoldBonus());
			break; }
		case EventModel::Type::RIOT: {
			RiotModel* riot = (RiotModel*)event;
			ShipModel* affectedShip = riot->getAffectedShip();
			if (affectedShip != nullptr)
				game->changeShipOwner(affectedShip, riot->getShipsOldNavigation());
			break; }
		case EventModel::Type::STORM: {
			StormModel* storm = (StormModel*)event;
			for (ShipModel* sinkShip : storm->getSinkShips())
			{
				if (sinkShip->getOwner() == Owner::PLAYER)
					game->removeFriendlyShip(sinkShip);
				else
					game->removeEnemyShip(sinkShip);
			}
			break; }
		default: break;
	}
	*onEvent = false;
}

bool GameController::spawnRiotEvent(ShipModel* affectedShip)
{
	std::ostringstream eventLog;

	ShipModel::Type shipType = affectedShip->getType();

	if (affectedShip->getPosition()->getType() == CellModel::Type::PORT) {
		eventLog << "Ship " << affectedShip->getID() << " is at port and wasn't affected by the riot!";
		logger.addLineToInfoLog(eventLog.str());
		logger.addLineToEventLog(eventLog.str());
		*onEvent = false;
		return false;
	}

	if (shipType == ShipModel::Type::FRIGATE || shipType == ShipModel::Type::SAILBOAT)
	{
		eventLog << "Ship " << affectedShip->getID() << " turned enemy during the riot!";
		game->changeShipOwner(affectedShip, Navigation::AUTO);
		*onEvent = true;
		logger.addLineToInfoLog(eventLog.str());
		logger.addLineToEventLog(eventLog.str());
		return true;
	} else {
		eventLog << "Ship " << affectedShip->getID() << " sank during the riot!";
		game->removeFriendlyShip(affectedShip);
		logger.addLineToInfoLog(eventLog.str());
		logger.addLineToEventLog(eventLog.str());
		*onEvent = false;
		return false;
	}
	
}

void GameController::updateEvent(EventModel* event, GameModel* game, MapModel* map)
{
	switch (event->getType())
	{
	case EventModel::Type::LULL: {
		LullModel* lull = (LullModel*)event;
		lull->setAffectedPositions(updateAffectedPositions(lull->getAffectedPositions(), map));
		lull->setAffectedShips(updateAffectedShips(lull->getAffectedShips(), game));
		break; }
	case EventModel::Type::MERMAID: {
		MermaidModel* mermaid = (MermaidModel*)event;
		mermaid->setAffectedShip(updateAffectedShip(mermaid->getAffectedShip(), game));
		break; }
	case EventModel::Type::RIOT: {
		RiotModel* riot = (RiotModel*)event;
		riot->setAffectedShip(updateAffectedShip(riot->getAffectedShip(), game));
		break; }
	case EventModel::Type::STORM: {
		StormModel* storm = (StormModel*)event;
		storm->setAffectedPositions(updateAffectedPositions(storm->getAffectedPositions(), map));
		storm->setSinkShips(updateAffectedShips(storm->getSinkShips(), game));
		storm->setStormSurvivors(updateAffectedShips(storm->getStormSurvivors(), game));
		break; }
	default:;
	}
}

std::vector<SeaModel*> GameController::updateAffectedPositions(std::vector<SeaModel*> affectedPositions, MapModel* map)
{
	std::vector<SeaModel*> tmp;
	int x, y;
	for (auto affectedPosition : affectedPositions) {
		x = affectedPosition->getX();
		y = affectedPosition->getY();
		tmp.push_back((SeaModel*)map->getCellAt(x, y));
	}
	return tmp;
}

ShipModel* GameController::updateAffectedShip(ShipModel* affectedShip, GameModel* game)
{
	if (affectedShip->getOwner() == Owner::PLAYER) {
		for (auto friendlyShip : game->getFriendlyShips()) {
			if (friendlyShip->getID() == affectedShip->getID()) {
				return friendlyShip;
			}
		}
	} else {
		for (auto enemyShip : game->getEnemyShips()) {
			if (enemyShip->getID() == affectedShip->getID()) {
				return enemyShip;
			}
		}
	}
}

std::vector<ShipModel*> GameController::updateAffectedShips(std::vector<ShipModel*> affectedShips, GameModel* game)
{
	std::vector<ShipModel*>tmp;

	for (auto affectedShip : affectedShips) {
		tmp.push_back(updateAffectedShip(affectedShip, game));
	}

	return tmp;
}

bool GameController::spawnRandomEnemyShip(std::vector<SeaModel*> seaCells, int probability)
{
	std::ostringstream log, enemyLog;
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
		game->addPirateShip(enemyShip);
		seaCells.at(position)->setShip(enemyShip);

		log << "Spawning random " << enemyShip->getAsString() << " at x: ";
		log << cell->getX() + 1 << " y: " << cell->getY() + 1;

		enemyLog << "A random enemy ship appeared at x: ";
		enemyLog << cell->getX() + 1 << " y: " << cell->getY() + 1;
		 
		logger.addLineToInfoLog(log.str());
		logger.addLineToEnemyLog(enemyLog.str());

		return true;
	}

	enemyLog << "No Enemy Ship Appeared!";
	logger.addLineToInfoLog(log.str());
	logger.addLineToEnemyLog(enemyLog.str());

	return false;
}

std::vector<SeaModel*> GameController::getSurroundingSeaCellsInRange2(const CellModel* currentCell) const { return map->getSurroundingSeaCellsInRange2(currentCell); }

void GameController::friendlyFleetMovement(std::vector<ShipModel*> friendlyShips)
{
	for (ShipModel* friendlyShip : friendlyShips)
	{
		if (canMoveShip(friendlyShip))
		{
			if (friendlyShip->getType()==ShipModel::Type::GHOST) {
				ghostShipMovement(friendlyShip);
				friendlyShip->resetMoves();
				continue;
			}
			switch (friendlyShip->getNavigation())
			{
				case Navigation::USER:
					watchingWaves(friendlyShip);
					break;
				case Navigation::AUTO: autoShipMovement(friendlyShip); break;
				case Navigation::ORDER: orderShipMovement(friendlyShip); break;
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
			switch (enemyShip->getNavigation())
			{
				case Navigation::AUTO: autoShipMovement(enemyShip); break;
				default: break;
			}
		}
		enemyShip->resetMoves();
	}
}

bool GameController::canMoveShip(ShipModel* ship) const { return ship->getNumOfMoves() < ship->getMaxMoves(); }

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

			if (ship->getType() == ShipModel::Type::SCHOONER && ship->getOwner() != Owner::LOST)
			{
				if (sea->hasFish()) {
					if (ship->canAddToShipCargo(1)) {
						sea->catchFish();
						ship->catchFish();
					}

				}

			}

		}
		else //Other option left is to go to a port
		{
			PortModel* port = (PortModel*)goToPosition;
			if (port->getOwner() == ship->getOwner())
			{
				port->addShipToPort(ship);
				ship->refillWater();
			}
			else {
				//Can only attack empty ports
				if (port->getNumberOfShips() > 0) {
					//Combats ships at port
					if(ship->getOwner()==Owner::PLAYER) {
						//Player Vs enemy Ships at port
						for (auto enemyShip : port->getShips())
							if (!shipCombat(ship, enemyShip)) return false;
					} else {
						//Player at port Vs enemy Ships
						for (auto friendlyShip : port->getShips())
							if (!shipCombat(friendlyShip, ship)) return false;
					}
					
					return true;
				}

				//If ship wins battle it will enter the port
				if (portCombat(ship, port))
				{
					port->addShipToPort(ship);
					ship->refillWater();
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
		//Checks surroundings
		checkSurroundings(ship);
		return true;
	}
}

void GameController::watchingWaves(ShipModel* ship)
{
	checkSurroundings(ship);
	ship->blockShipMovement();
	if (ship->getPosition()->getType() == CellModel::Type::SEA) {
		ship->navigationCost();
		if (ship->getType()==ShipModel::Type::SCHOONER) {
			SeaModel* sea = (SeaModel*)ship->getPosition();
			if (sea->hasFish()) {
				if (ship->canAddToShipCargo(1)) {
					sea->catchFish();
					ship->catchFish();
				}
			}
		}
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

void GameController::autoShipMovement(ShipModel* ship)
{
	ship->shipsAutoMovement(this);	
}

void GameController::orderShipMovement(ShipModel* ship)
{
	CellModel* goTo = ship->getGoTo();
	do {
		if (map->getSurroundingEmptySeaCells(ship->getPosition()).empty()) {
			ship->blockShipMovement();
			break;
		}
		moveShip(ship, goToCell(ship->getPosition(), goTo));
		if (goTo == ship->getPosition()) {
			break;
		}
	} while (canMoveShip(ship));
}

bool GameController::canMoveToCell(CellModel* cell)
{
	if (cell->getType() == CellModel::Type::GROUND) return false;

	if (cell->getType() == CellModel::Type::SEA) {
		SeaModel* sea = (SeaModel*)cell;
		if (sea->hasShip()) return false;
	}

	return true;
}

void GameController::ghostShipMovement(ShipModel* ghost)
{
	GhostShipModel* ghostShip = (GhostShipModel*)ghost;

	//Checks if can combat enemy ships
	if (ghostShip->canAttack()) {
		int totalEnemyShips = game->getEnemyShips().size();
		if (totalEnemyShips > 0 && ghostShip->canAttack()) {
			int random = rand() % totalEnemyShips;
			if (!shipCombat(ghost, game->getEnemyShips().at(random))) return;
			ghostShip->updateCountdown();
		}
	} else {
		ghostShip->updateCountdown();
	}

	int random = rand() % 2;

	if (random) {
		int totalFriendlyPorts = map->getFriendlyPorts().size();

		if (totalFriendlyPorts > 0) {
			random = rand() % totalFriendlyPorts;
			PortModel* port = map->getFriendlyPorts().at(random);

			if (ghost->getPosition()->getType() != CellModel::Type::PORT) return;

			PortModel* position = (PortModel*)ghostShip->getPosition();

			if (port->getID() != position->getID()) {
				moveShip(ghost, getCellAt(port->getX(), port->getY()));
			}
		}
	}
}

CellModel* GameController::goToCell(CellModel* current, CellModel* goTo)
{
	CellModel* tmp = current;

	int xPosition = current->getX() - goTo->getX();
	int yPosition = current->getY() - goTo->getY();

	//Check if cell is on the same column
	if (xPosition == 0) {
		//Check if go to is up
		if (yPosition > 0) {
			tmp = getCellAbove(current);
			if (canMoveToCell(tmp)) return tmp;
		} else {
			//Go to is down
			tmp = getCellBelow(current);
			if (canMoveToCell(tmp)) return tmp;
		}	
	}

	//Check if cell is on the same line
	if (yPosition == 0)
	{
		//Check if go to cell is at right 
		if (xPosition < 0) {
			tmp = getCellRight(current);
			if (canMoveToCell(tmp)) return tmp;
		} else {
			//cell is at left
			tmp = getCellLeft(current);
			if (canMoveToCell(tmp)) return tmp;
		}	
	}

	//Check if go to cell is at right 
	if (xPosition < 0) {
		//Check if go to is up
		if (yPosition > 0) {
			tmp = getCellAboveRight(current);
			if (canMoveToCell(tmp)) return tmp;
		} else {
			//Go to is down
			tmp = getCellBelowRight(current);
			if (canMoveToCell(tmp)) return tmp;
		}

	} else {
		//Go to is at left
		if (yPosition > 0) {
			tmp = getCellAboveLeft(current);
			if (canMoveToCell(tmp)) return tmp;
		} else {
			tmp = getCellBelowLeft(current);
			if (canMoveToCell(tmp)) return tmp;
		}
	}

	return generateRandomMove(current);
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

CellModel* GameController::getCellAbove(const CellModel* currentCell) const {return map->getCellAbove(currentCell);}
CellModel* GameController::getCellBelow(const CellModel* currentCell) const {return map->getCellBelow(currentCell);}
CellModel* GameController::getCellRight(const CellModel* currentCell) const {return map->getCellRight(currentCell);}
CellModel* GameController::getCellLeft(const CellModel* currentCell) const {return map->getCellLeft(currentCell);}
CellModel* GameController::getCellAboveRight(const CellModel* currentCell) const {return map->getCellAboveRight(currentCell);}
CellModel* GameController::getCellAboveLeft(const CellModel* currentCell) const {return map->getCellAboveLeft(currentCell);}
CellModel* GameController::getCellBelowRight(const CellModel* currentCell) const {return map->getCellBelowRight(currentCell);}
CellModel* GameController::getCellBelowLeft(const CellModel* currentCell) const {return map->getCellBelowLeft(currentCell);}

void GameController::addCoins(double amount) {game->addCoins(amount);}

double GameController::calculateShipValue(ShipModel* ship)
{
	double value = 0;
	value += game->getShipPrice();
	value += ship->getSoldiers() * game->getSoldierPrice();
	value += calculateShipContentValue(ship);
	return value;
}

double GameController::calculateShipContentValue(ShipModel* ship)
{
	double value = 0;
	if (ship->getCapacity() > 0) {
		value += ship->getMerch() * game->getMerchSellPrice();
		value += ship->getFish() * game->getFishSellPrice();
	}
	return value;
}

bool GameController::isGameOver()
{
	//Game ends when there are no friendly ships and no money to buy new ones
	return game->getFriendlyShips().size() == 0 && game->getPlayerCoins() > game->getShipPrice();
}

void GameController::endGame()
{
	game->setGameState(GameState::END);

	double score = 0;

	score += game->getPlayerCoins();

	for (auto friendlyShip : game->getFriendlyShips()) {
		score += calculateShipValue(friendlyShip);
	}

	game->setScore(score);
}

void GameController::addLineToInfoLog(std::string line) {logger.addLineToInfoLog(line);}
void GameController::addLineToCombatLog(std::string line) {logger.addLineToCombatLog(line);}
void GameController::addLineToEnemyLog(std::string line) {logger.addLineToEnemyLog(line);}

std::string GameController::getCombatLog() {return logger.getCombatLog();}
std::string GameController::getEventLog() {return logger.getEventLog();}
std::string GameController::getEnemyLog() {return logger.getEnemyLog();}

void GameController::flushLogs()
{
	logger.flushEnemyLog();
	logger.flushCombatLog();
	logger.flushEventLog();
}