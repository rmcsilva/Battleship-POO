#include "stdafx.h"
#include "FileManager.h"
#include "Logger.h"
#include "View.h"


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

bool FileManager::readInitialFileConfigs(std::string filename, MapModel *&map, GameModel *game)
{
	int portSoldiers=-1;

	std::ifstream file(filename);
	std::string line;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::stringstream linestream(line);
			std::string command;
			int value;
			
			linestream >> command >> value;

			switch (stringToInitialConfigs(command))
			{
				case InitialConfigsCommands::linhas:
					if (!setupMap(file, value, map, game)) {
						//Error reading file 
						return false;
					}
					break;
				case InitialConfigsCommands::moedas:
					game->setPlayerCoins(value);
					break;
				case InitialConfigsCommands::probpirata:
					map->setPirateProb(value);
					break;
				case InitialConfigsCommands::preconavio:
					game->setShipPrice(value);
					break;
				case InitialConfigsCommands::precosoldado:
					game->setSoldierPrice(value);
					break;
				case InitialConfigsCommands::precovendpeixe:
					game->setFishSellPrice(value);
					break;
				case InitialConfigsCommands::precocompmercad:
					game->setMerchBuyPrice(value);
					break;
				case InitialConfigsCommands::precovendmercad:
					game->setMerchSellPrice(value);
					break;
				case InitialConfigsCommands::soldadosporto:
					portSoldiers = value;
					break;
				case InitialConfigsCommands::probevento:
					game->setEventProbability(value);
					break;
				case InitialConfigsCommands::probtempestade:
					game->setStormEventProbability(value);
					break;
				case InitialConfigsCommands::probsereias:
					game->setMermaidEventProbability(value);
					break;
				case InitialConfigsCommands::probcalmaria:
					game->setCalmEventProbability(value);
					break;
				case InitialConfigsCommands::probmotim:
					game->setRiotEventProbability(value);
					break;
				case InitialConfigsCommands::INVALID:
					file.close();
					return false;
					break;
			}
		}
	} else {
		return false;
	}

	if (portSoldiers != -1)
	{
		for (auto port : map->getFriendlyPorts())
			port->setNumberOfSoldiers(portSoldiers);
	}

	file.close();
	return true;
}

bool FileManager::executeCommandsFromFile(std::string filename, GameController* gameController)
{
	std::ifstream file(filename);
	std::string line;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::stringstream linestream(line);
			std::string command;

			linestream >> command;

			switch (View::stringToGameCommand(command)) {
			case View::GameCommands::EXEC: {
				std::string filename;
				linestream >> filename;
				gameController->execCommand(filename);
				break; }
			case View::GameCommands::PROX: {
				gameController->flushLogs();
				gameController->proxCommand();
				break; }
			case View::GameCommands::COMPRANAV: {
				char type;
				linestream >> type;
				gameController->buyShip(type);
				break; }
			case View::GameCommands::VENDENAV: {
				char type;
				linestream >> type;
				gameController->sellShip(type);
				break; }
			case View::GameCommands::LISTA: break;
			case View::GameCommands::COMPRA: {
				int id;
				linestream >> id;
				ShipModel* ship = gameController->getFriendlyShipByID(id);
				if (ship == nullptr) break;
				int amount;
				linestream >> amount;
				if (amount < 0) break; 
				gameController->buyMerchCommand(ship, amount);
				break; }
			case View::GameCommands::VENDE: {
				int id;
				linestream >> id;
				ShipModel* ship = gameController->getFriendlyShipByID(id);
				if (ship == nullptr) break;
				gameController->sellShipCargoCommand(ship);
				break; }
			case View::GameCommands::MOVE: {
				int id;
				linestream >> id;
				std::string pos;
				linestream >> pos;

				CellModel* oldPosition = gameController->getFriendlyShipPositionByID(id);
				if (oldPosition == nullptr) continue;
				CellModel* position = View::convertStringCommandToCell(pos, oldPosition, gameController);
				if (!gameController->moveCommand(id, position)) continue;
				break; }
			case View::GameCommands::AUTO: {
				int id;
				linestream >> id;
				ShipModel* ship = gameController->getFriendlyShipByID(id);
				if (ship == nullptr) break;
				gameController->autoShipCommand(ship);
				break; }
			case View::GameCommands::STOP: {
				int id;
				linestream >> id;
				ShipModel* ship = gameController->getFriendlyShipByID(id);
				if (ship == nullptr) break;
				gameController->stopShipCommand(ship);
				break; }
			case View::GameCommands::PIRATA: {
				int x, y;
				linestream >> x >> y;
				CellModel* position = gameController->getCellAt(x - 1, y - 1);
				char type;
				linestream >> type;
				gameController->spawnEnemyShipAt(position, type);
				break; }
			case View::GameCommands::EVPOS: {
				char type;
				linestream >> type;
				int x, y;
				linestream >> x >> y;
				if (gameController->hasEvent()) break;
				CellModel* startingCell = gameController->getCellAt(x - 1, y - 1);
				if (startingCell == nullptr) break;
				gameController->spawnPositionEvent(type, startingCell);
				break; }
			case View::GameCommands::EVNAV: {
				char type;
				linestream >> type;
				int id;
				linestream >> id;
				if (gameController->hasEvent()) return false;
				ShipModel* ship = gameController->getFriendlyShipByID(id);
				if (ship == nullptr) continue;
				gameController->spawnShipEvent(type, ship);
				break; }
			case View::GameCommands::MOEDAS: {
				double amount;
				linestream >> amount;
				if (amount < 0) { break; }
				gameController->addCoins(amount);
				break; }
			case View::GameCommands::VAIPARA: {
				int id;
				linestream >> id;
				ShipModel* ship = gameController->getFriendlyShipByID(id);
				if (ship == nullptr) break;

				std::string position;
				linestream >> position;

				int x, y;

				try {
					x = std::stoi(position);
					linestream >> y;
				}
				catch (std::invalid_argument e) {
					char id = position.at(0);
					CellModel* tmp = gameController->getFriendlyPortPositionByID(id);
					if (tmp == nullptr) break;
					x = tmp->getX() + 1;
					y = tmp->getY() + 1;
				}

				CellModel* cell;
				try {
					cell = gameController->getCellAt(x - 1, y - 1);
				}
				catch (std::out_of_range e) {
					break;
				}

				gameController->orderShipCommand(ship, cell);
				break; }
			case View::GameCommands::COMPRASOLD: {
				int id;
				linestream >> id;
				ShipModel* ship = gameController->getFriendlyShipByID(id);
				if (ship == nullptr) break;
				int amount;
				linestream >> amount;
				if (amount < 0) break;
				gameController->buySoldiersCommand(ship, amount);
				break; }
			case View::GameCommands::SAVEG: {
				std::string name;
				linestream >> name;
				gameController->saveGameCommand(name);
				break; }
			case View::GameCommands::LOADG: {
				std::string name;
				linestream >> name;
				gameController->loadGameCommand(name);
				break; }
			case View::GameCommands::DELG: {
				std::string name;
				linestream >> name;
				gameController->deleteGameCommand(name);
				break; }
			case View::GameCommands::SAIR: {
				gameController->endGame();
				file.close();
				return false;
				break; }
			case View::GameCommands::INVALID:
				file.close();
				return false;
			default:
				file.close();
				return false;
			}
		}
	} else {
		file.close();
		return false;
	}
	file.close();
	return true;
}

FileManager::InitialConfigsCommands FileManager::stringToInitialConfigs(std::string const & inString)
{
	if (inString == "linhas") return InitialConfigsCommands::linhas;
	if (inString == "colunas") return InitialConfigsCommands::colunas;
	if (inString == "moedas") return InitialConfigsCommands::moedas;
	if (inString == "probpirata") return InitialConfigsCommands::probpirata;
	if (inString == "preconavio") return InitialConfigsCommands::preconavio;
	if (inString == "precosoldado") return InitialConfigsCommands::precosoldado;
	if (inString == "precovendpeixe") return InitialConfigsCommands::precovendpeixe;
	if (inString == "precocompmercad") return InitialConfigsCommands::precocompmercad;
	if (inString == "precovendmercad") return InitialConfigsCommands::precovendmercad;
	if (inString == "soldadosporto") return InitialConfigsCommands::soldadosporto;
	if (inString == "probevento") return InitialConfigsCommands::probevento;
	if (inString == "probtempestade") return InitialConfigsCommands::probtempestade;
	if (inString == "probsereias") return InitialConfigsCommands::probsereias;
	if (inString == "probcalmaria") return InitialConfigsCommands::probcalmaria;
	if (inString == "probmotim") return InitialConfigsCommands::probmotim;
	return InitialConfigsCommands::INVALID;
}

bool FileManager::setupMap(std::ifstream &file,int const &lines, MapModel *&map, GameModel *game)
{
	std::string line;

	if (std::getline(file, line)) {
		std::stringstream linestream(line);

		std::string command;
		int value;

		linestream >> command >> value;

		if (stringToInitialConfigs(command) == InitialConfigsCommands::colunas) {
			try {
				map = new MapModel(lines, value);
			}
			catch (std::bad_array_new_length& e) {
				std::cerr << "bad array new length caught: " << e.what() << '\n';
			} catch (std::bad_alloc& e) {
				std::cerr << "bad_alloc caught: " << e.what() << '\n';
			}

			if (readMap(file, lines, value, map, game)) {
				return true;
			}
			else {
				return false;
			}
			
			
		} else {
			return false;
		}	
	} else {
		return false;
	}

	return true;
}

bool FileManager::readMap(std::ifstream & file, int const & lines, int const & columns, MapModel *map, GameModel *game)
{
	char cellType;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			file >> cellType;
			if (isalpha(cellType))
			{
				if (isupper(cellType)) 
				{
					map->addPortCellAt(j, i, cellType, Owner::PLAYER);
					map->addFriendlyPort((PortModel*)map->getCellAt(j,i));
				} 
				else {
					map->addPortCellAt(j, i, cellType, Owner::ENEMY);
					map->addPiratePort((PortModel*)map->getCellAt(j, i));
				}
			}
			else if (cellType == '.') {
				map->addCellAt(j, i, CellModel::Type::SEA);
				map->addSeaCell((SeaModel*)map->getCellAt(j, i));
			}
			else if (cellType == '+') {
				map->addCellAt(j, i, CellModel::Type::GROUND);
			}
			else {
				return false;
			}
		}
	}
	//Consume the last line
	std::string buffer;
	std::getline(file, buffer);
	return true;
}

