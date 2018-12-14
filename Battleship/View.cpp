#include "stdafx.h"
#include "View.h"
#include <iomanip>
#include "LullModel.h"
#include "MermaidModel.h"
#include "RiotModel.h"
#include "StormModel.h"


View::View()
{
}

void View::setupLayout(GameController *gameController)
{
	while (true)
	{
		switch (gameController->getGameState())
		{
			case GameState::SETUP:
				//TODO:Uncomment this is for tests only
				//initialLayout(gameController);
				gameController->readInitialFileConfigs("initialConfig.txt");
				break;
			case GameState::GAME:
				gameLayout(gameController);
				gameAction(gameController);
				break;
			case GameState::END:
				//TODO: Menu with score
				std::cout << "Leaving game!";
				Consola::getch();
				return;
			break;
		}
	}
}

void View::initialLayout(GameController *gameController) const
{
	Consola::clrscr();
	std::cout << INITIAL_LAYOUT;
	std::string command;
	do {
		std::cout << COMMAND_LINE;
		std::getline(std::cin, command);
	} while (readInitialCommands(command, gameController));

	Consola::setTextColor(SUCESS_COLOR);
	std::cout << READ_SUCESS;
	Consola::setTextColor(TEXT_COLOR);
	Consola::getch();

	//TODO: Show initial stats 
}

bool View::readInitialCommands(std::string const &input, GameController * gameController) const
{
	std::istringstream line(input);
	std::string command;

	line >> command;

	switch (stringToInitialCommand(command))
	{
		case InitialCommands::CONFIG: {
			std::string filename;
			line >> filename;

			if (gameController->readInitialFileConfigs(filename)) {
				return false;
			}
			Consola::setTextColor(ERROR_COLOR);
			std::cout << ERROR_READING_FILE << filename << std::endl;
			Consola::setTextColor(TEXT_COLOR);
			return true;
			break;
		}
		default:
			return true;
			break;
	}
}

View::InitialCommands View::stringToInitialCommand(std::string const & inString)
{
	if (inString == "config") return InitialCommands::CONFIG;
	return InitialCommands::INVALID;
}

void View::gameLayout(GameController* gameController) const
{	
	Consola::clrscr();
	Consola::gotoxy(2, 0);

	//Show X Positions
	for (int i = 1; i <=gameController->getNumColumns(); i++)
	{
		if (i%2)Consola::setTextColor(Consola::CINZENTO); 
		else	Consola::setTextColor(Consola::BRANCO_CLARO);
		std::cout << std::setw(2) << i;
	}

	Consola::setTextColor(TEXT_COLOR);
	Consola::gotoxy(0, 1);

	bool mainColor;
	//Print Map and Y position
	for (int i = 0; i < gameController->getNumLines(); i++) 
	{
		Consola::setTextColor(TEXT_COLOR);
		Consola::gotoxy(0, i * 2 + 1);
		std::cout << std::setw(2) << i+1;
		for (int j = 0; j < gameController->getNumColumns(); j++)
		{
			if ((i+j) % 2) mainColor = true;
			else	   mainColor = false;
			paintInitialMapCell(gameController->getCellAt(j, i), mainColor);
		}
		Consola::setBackgroundColor(TEXT_BACKGROUND);
		std::cout << '\n';
	}
	Consola::setBackgroundColor(TEXT_BACKGROUND);
}

void View::paintInitialMapCell(CellModel* cell, bool mainColor) const
{
	goToMapPosition(cell->getX(), cell->getY());
	switch (cell->getType())
	{
		case CellModel::Type::SEA:{
			if (mainColor)
				Consola::setBackgroundColor(SEA_COLOR_MAIN);
			else
				Consola::setBackgroundColor(SEA_COLOR_OFF);

			//Initially every cell has fish
			std::cout << " *";

			goToMapOffPosition(cell->getX(), cell->getY());
			std::cout << "  ";
			break;
		}
		case CellModel::Type::PORT: {
			PortModel* port = (PortModel*)cell;
			if (port->getOwner() == Owner::PLAYER)
			{
				Consola::setTextColor(FRIENDLY_SHIP_COLOR);
				Consola::setBackgroundColor(FRIENDLY_PORT_COLOR);	
			}
			else
			{
				Consola::setTextColor(ENEMY_SHIP_COLOR);
				Consola::setBackgroundColor(ENEMY_PORT_COLOR);
			}
			std::cout << ' ' << port->getID();
			Consola::setTextColor(TEXT_COLOR);

			goToMapOffPosition(cell->getX(), cell->getY());
			//Initially all ports are empty
			std::cout << "  ";
			break;
		}
		case CellModel::Type::GROUND:
			if (mainColor)
				Consola::setBackgroundColor(GROUND_COLOR_MAIN);
			else
				Consola::setBackgroundColor(GROUND_COLOR_OFF);

			std::cout << "  ";

			goToMapOffPosition(cell->getX(), cell->getY());
			std::cout << "  ";
			break;
	}
}

void View::gameAction(GameController* gameController)
{
	std::string command;
	do
	{
		Consola::clrcommands(gameController->getNumLines() * 2 + 1);
		showFriendlyPortsInfo(gameController->getFriendlyPorts());
		showLogsInfo(gameController->getEnemyLog(), gameController->getCombatLog(), gameController->getEventLog());
		std::cout << "Player Coins: " << gameController->getPlayerCoins() << '\n';
		std::cout << COMMAND_LINE;
		std::getline(std::cin, command);
	} while (readGameCommands(command, gameController));
}

bool View::readGameCommands(std::string const& input, GameController* gameController) const
{
	std::istringstream line(input);
	std::string command;

	line >> command;

	switch (stringToGameCommand(command))
	{
		case GameCommands::EXEC: {
			std::string filename;
			line >> filename;
			gameController->execCommand(filename);
			updateAllSeaCells(gameController->getSeaCells());
			updateAllPortCells(gameController->getFriendlyPorts(), gameController->getEnemyPorts());
			updateEventInformation(gameController);
			break; }
		case GameCommands::PROX: {
			gameController->flushLogs();
			//TODO:Perform commands
			//TODO: Implement ships auto movement
			gameController->proxCommand();
			updateAllSeaCells(gameController->getSeaCells());
			updateAllPortCells(gameController->getFriendlyPorts(), gameController->getEnemyPorts());
			updateEventInformation(gameController);
			break; }
		case GameCommands::COMPRANAV: {
			char type;
			line >> type;
			if (!gameController->buyShip(type))
				std::cout << COMMAND_EXECUTE_ERROR;
			else
				updatePortCell(gameController->getFriendlyPorts().at(0));
			break; }
		case GameCommands::MOVE: {
			int id;
			line >> id;
			std::string pos;
			line >> pos;

			CellModel* oldPosition = gameController->getFriendlyShipPositionByID(id);
			if (oldPosition==nullptr)
			{
				std::cout << "Ship does not exist!";
				Consola::getch();
				break;
			}
			CellModel* position = convertStringCommandToCell(pos, oldPosition, gameController);
			if (!gameController->moveCommand(id, position)) { std::cout << COMMAND_EXECUTE_ERROR; Consola::getch(); }
			updateAllSeaCells(gameController->getSeaCells());
			updateAllPortCells(gameController->getFriendlyPorts(), gameController->getEnemyPorts());
			updateEventInformation(gameController);
			break;
		}
		case GameCommands::MOEDAS: {
			double amount;
			line >> amount;
			//TODO: Add restrictions 
			if (amount < 0) { break; }
			gameController->addCoins(amount);
			break; }
		case GameCommands::PIRATA: {
			int x, y;
			line >> x >> y;
			CellModel* position = gameController->getCellAt(x-1, y-1);
			char type;
			line >> type;
			//TODO: Verify position
			gameController->spawnEnemyShipAt(position, type);
			updateAllSeaCells(gameController->getSeaCells());
			updateAllPortCells(gameController->getFriendlyPorts(), gameController->getEnemyPorts());
			break; }
		case GameCommands::EVPOS: {
			char type;
			line >> type;
			int x, y;
			line >> x >> y;
			if (gameController->hasEvent()) break;
			CellModel* startingCell = gameController->getCellAt(x-1, y-1);
			if (startingCell == nullptr) break;
			gameController->spawnPositionEvent(type, startingCell);
			updateEventInformation(gameController);
			break; }
		case GameCommands::EVNAV: {
			char type;
			line >> type;
			int id;
			line >> id;
			if (gameController->hasEvent()) return false;
			ShipModel* ship = gameController->getFriendlyShipByID(id);
			if (ship==nullptr)
			{
				std::cout << "Ship does not exist!";
				Consola::getch();
				break;
			}
			gameController->spawnShipEvent(type, ship);
			updateAllSeaCells(gameController->getSeaCells());
			break;
		}
		case GameCommands::SAIR:
			gameController->endGame();
			return false;
		case GameCommands::INVALID:
			break;
	}
	//Consola::getch();
	return true;
}

View::GameCommands View::stringToGameCommand(std::string const& inString)
{
	if (inString == "exec") return GameCommands::EXEC;
	if (inString == "prox") return GameCommands::PROX;
	if (inString == "compranav") return GameCommands::COMPRANAV;
	if (inString == "vendenav") return GameCommands::VENDENAV;
	if (inString == "lista") return GameCommands::LISTA;
	if (inString == "compra") return GameCommands::COMPRA;
	if (inString == "vende") return GameCommands::VENDE;
	if (inString == "move") return GameCommands::MOVE;
	if (inString == "auto") return GameCommands::AUTO;
	if (inString == "stop") return GameCommands::STOP;
	if (inString == "pirata") return GameCommands::PIRATA;
	if (inString == "evpos") return GameCommands::EVPOS;
	if (inString == "evnav") return GameCommands::EVNAV;
	if (inString == "moedas") return GameCommands::MOEDAS;
	if (inString == "vaipara") return GameCommands::VAIPARA;
	if (inString == "comprasold") return GameCommands::COMPRASOLD;
	if (inString == "saveg") return GameCommands::SAVEG;
	if (inString == "loadg") return GameCommands::LOADG;
	if (inString == "delg") return GameCommands::DELG;
	if (inString == "sair") return GameCommands::SAIR;
	return GameCommands::INVALID;
}

void View::showFriendlyPortsInfo(std::vector<PortModel*> const& ports) const
{
	if (ports.size()>0)
	{
		std::cout << "Main Port -> ";
		for (PortModel* const &port : ports)
			std::cout << *port;
	}
	else
	{
		std::cout << "Player has no friendly ports!";
	}	
}

void View::showLogsInfo(std::string enemyLog, std::string combatLog, std::string eventLog) const
{
	if (combatLog.empty())
		std::cout << "No combats this turn! \n";
	else
		std::cout << '\n' << combatLog;
	
	std::cout << eventLog;
	std::cout << enemyLog;
}

void View::updateAllSeaCells(std::vector<SeaModel*> const& seaCells) const
{
	for (SeaModel* const &seaCell : seaCells)
		updateSeaCell(seaCell);	
}

void View::updateSeaCell(SeaModel* const& seaCell) const
{
	bool mainColor;
	int x = seaCell->getX();
	int y = seaCell->getY();

	if ((x + y) % 2) mainColor = true;
	else	   mainColor = false;

	goToMapPosition(x, y);

	if (seaCell->hasShip())
	{
		Consola::setTextColor(TEXT_BACKGROUND);

		//TODO: Identify ship type
		if (seaCell->getShipOwner() == Owner::PLAYER)
			Consola::setBackgroundColor(FRIENDLY_SHIP_COLOR);
		else
			Consola::setBackgroundColor(ENEMY_SHIP_COLOR);

		std::cout << std::setw(2) << seaCell->getShip()->getID();
		
		goToMapOffPosition(x, y);

		//TODO: Verify ship type and add corresponding color
		switch (seaCell->getShipType())
		{
			case ShipModel::Type::FRIGATE: std::cout << " F"; break;
			case ShipModel::Type::GALLEON: std::cout << " G"; break;
			case ShipModel::Type::GHOST: std::cout << " S"; break;
			case ShipModel::Type::SAILBOAT: std::cout << " V"; break;
			case ShipModel::Type::SCHOONER: std::cout << " E"; break;
		}

		Consola::setTextColor(TEXT_COLOR);
	}
	else
	{
		if (mainColor)
			Consola::setBackgroundColor(SEA_COLOR_MAIN);
		else
			Consola::setBackgroundColor(SEA_COLOR_OFF);

		std::cout << " ";

		if (seaCell->hasFish())
			std::cout << "*";
		else 
			std::cout << " ";

		goToMapOffPosition(x, y);
		std::cout << "  ";
	}
	Consola::setBackgroundColor(TEXT_BACKGROUND);
}

void View::updateAllPortCells(std::vector<PortModel*> const &friendlyPorts, std::vector<PortModel*> const &enemyPorts) const
{
	for (PortModel* const &friendlyPort : friendlyPorts)
		updatePortCell(friendlyPort);
	for (PortModel* const &enemyPort : enemyPorts)
		updatePortCell(enemyPort);
}

void View::updatePortCell(PortModel* const& portCell) const
{
	int x = portCell->getX();
	int y = portCell->getY();
	goToMapPosition(x, y);

	if (portCell->getOwner() == Owner::PLAYER)
	{
		Consola::setTextColor(FRIENDLY_SHIP_COLOR);
		Consola::setBackgroundColor(FRIENDLY_PORT_COLOR);
	}
	else
	{
		Consola::setTextColor(ENEMY_SHIP_COLOR);
		Consola::setBackgroundColor(ENEMY_PORT_COLOR);
	}
	std::cout << ' ' << portCell->getID();

	goToMapOffPosition(x,y);

	int numberOfShips = portCell->getNumberOfShips();

	if (numberOfShips)
		std::cout << std::setw(2) << numberOfShips;
	else
		std::cout << "  ";

	Consola::setTextColor(TEXT_COLOR);
	Consola::setBackgroundColor(TEXT_BACKGROUND);
}

void View::updateEventInformation(const GameController *gameController) const
{
	if (gameController->hasEvent())
	{
		EventModel* event = gameController->getEvent();
		Consola::setBackgroundColor(EVENT_COLOR);

		switch (event->getType())
		{
			case EventModel::Type::LULL: {
				LullModel* lull = (LullModel*)event;

				std::vector<SeaModel*> affectedPositions = lull->getAffectedPositions();
				for (SeaModel* affectedPosition : affectedPositions)
				{
					int x = affectedPosition->getX();
					int y = affectedPosition->getY();
		
					if (affectedPosition->hasShip())
					{
						goToMapOffPosition(x, y);
						std::cout << "C";
					} 
					else
					{
						goToMapPosition(x, y);
						std::cout << std::setw(2) << "  ";

						goToMapOffPosition(x, y);
						std::cout << "C ";
					}
				}

				break; }
			case EventModel::Type::MERMAID: {
				MermaidModel* mermaid = (MermaidModel*)event;
				ShipModel* affectedShip = mermaid->getAffectedShip();
				goToMapOffPosition(affectedShip->getPosition()->getX(), affectedShip->getPosition()->getY());
				std::cout << "S";
				break; }
			case EventModel::Type::RIOT: {
				RiotModel* riot = (RiotModel*)event;
				ShipModel* affectedShip = riot->getAffectedShip();
				goToMapOffPosition(affectedShip->getPosition()->getX(), affectedShip->getPosition()->getY());
				std::cout << "M";
				break; }
			case EventModel::Type::STORM: {
				StormModel* storm = (StormModel*)event;

				std::vector<SeaModel*> affectedPositions = storm->getAffectedPositions();
				for (SeaModel* affectedPosition : affectedPositions)
				{
					int x = affectedPosition->getX();
					int y = affectedPosition->getY();

					if (affectedPosition->hasShip())
					{
						goToMapOffPosition(x, y);
						std::cout << "T";
					}
					else
					{
						goToMapPosition(x, y);
						std::cout << std::setw(2) << "  ";

						goToMapOffPosition(x, y);
						std::cout << "T ";
					}
				}
				break; }
			default: ;
		}

		Consola::setBackgroundColor(TEXT_BACKGROUND);
	}
}

void View::goToMapPosition(int x, int y)
{
	x = (x + 1) * 2;
	y = y * 2 + 1;
	Consola::gotoxy(x, y);
}

void View::goToMapOffPosition(int x, int y)
{
	x = (x + 1) * 2;
	y = y * 2 + 2;
	Consola::gotoxy(x, y);
}

CellModel* View::convertStringCommandToCell(std::string command, CellModel* currentCell, GameController *gameController)
{
	if (command.length() == 1)
	{
		if (command.compare("D") == 0) return gameController->getCellRight(currentCell);
		if (command.compare("E") == 0) return gameController->getCellLeft(currentCell);
		if (command.compare("C") == 0) return gameController->getCellAbove(currentCell);
		if (command.compare("B") == 0) return gameController->getCellBelow(currentCell);
	}else if (command.length() == 2)
	{
		if (command.compare("CD") == 0) return gameController->getCellAboveRight(currentCell);
		if (command.compare("CE") == 0) return gameController->getCellAboveLeft(currentCell);
		if (command.compare("BE") == 0) return gameController->getCellBelowLeft(currentCell);
		if (command.compare("BD") == 0) return gameController->getCellBelowRight(currentCell);
	}
	return currentCell;
}
