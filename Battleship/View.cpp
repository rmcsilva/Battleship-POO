#include "stdafx.h"
#include "View.h"
#include <iomanip>


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
			//TODO: Make game menu
			gameLayout(gameController);
			gameAction(gameController);
			break;
		case GameState::END:
			//TODO: Menu with score
			std::cout << "Leaving game!";
			Consola::getch();
			exit(1);
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
	switch (cell->getType())
	{
		case CellModel::Type::SEA:
			if (mainColor)
			{
				Consola::setBackgroundColor(SEA_COLOR_MAIN);
				std::cout << "  ";
			}
			else
			{
				Consola::setBackgroundColor(SEA_COLOR_OFF);
				std::cout << "  ";
			}
			break;
		case CellModel::Type::PORT: {
			PortModel* port = (PortModel*)cell;
			if (port->getOwner() == CellModel::CellOwner::PLAYER)
			{
				Consola::setTextColor(FRIENDLY_SHIP_COLOR);
				Consola::setBackgroundColor(FRIENDLY_PORT_COLOR);
				std::cout << ' ' << port->getID();
			}
			else
			{
				Consola::setTextColor(ENEMY_SHIP_COLOR);
				Consola::setBackgroundColor(ENEMY_PORT_COLOR);
				std::cout << ' ' << port->getID();
			}
			break;
		}
		case CellModel::Type::GROUND:
			if (mainColor)
			{
				Consola::setBackgroundColor(GROUND_COLOR_MAIN);
				std::cout << "  ";
			}
			else
			{
				Consola::setBackgroundColor(GROUND_COLOR_OFF);
				std::cout << "  ";
			}
			break;
	}
}

void View::gameAction(GameController* gameController)
{
	std::string command;
	do
	{
		Consola::clrcommands(gameController->getNumLines() + 1);
		showFriendlyPortsInfo(gameController->getFriendlyPorts());
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
		case GameCommands::EXEC: break;
		case GameCommands::PROX:
			//TODO:Perform commands
			//TODO: Implement ships auto movement
			updateAllSeaCells(gameController->getSeaCells());
			updateAllShips(gameController->getFriendlyShips());
			
			break;
		case GameCommands::COMPRANAV:
			//TODO: Complete function, need to implement ships first!
			char type;
			line >> type;
			if (!gameController->buyShip(type))
				std::cout << COMMAND_EXECUTE_ERROR;
			break; 
		case GameCommands::MOVE: {
			int id;
			line >> id;
			std::string pos;
			line >> pos;
			try
			{
				CellModel* oldPosition = gameController->getFriendlyShipPositionByID(id);
				CellModel* position = convertStringCommandToCell(pos, oldPosition, gameController);
				gameController->move(id, position);
			}
			catch (std::out_of_range e)
			{
				std::cout << "Ship does not exist!";
				break;
			}
			break;
		}
		case GameCommands::MOEDAS:
			double amount;
			line >> amount;
			//TODO: Add restrictions 
			if (amount < 0) {break;}
			gameController->addCoins(amount);
			break;
		case GameCommands::SAIR:
			gameController->endGame();
			return false;
			break;
		case GameCommands::INVALID:
			break;
	}
	Consola::getch();
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

	//TODO: Review
	if (seaCell->hasShip())
	{
		//if (seaCell->getShipOwner() == ShipOwner::PLAYER)
		//{
		//	Consola::setBackgroundColor(FRIENDLY_SHIP_COLOR);
		//	std::cout << std::setw(2) << seaCell->getShip()->getID();
		//}
		//else
		//{
		//	Consola::setBackgroundColor(ENEMY_SHIP_COLOR);
		//	std::cout << std::setw(2) << seaCell->getShip()->getID();
		//}
	}
	else
	{
		//TODO: Check if cell has fish
		if (mainColor)
		{
			Consola::setBackgroundColor(SEA_COLOR_MAIN);
			std::cout << "  ";
		}
		else
		{
			Consola::setBackgroundColor(SEA_COLOR_OFF);
			std::cout << "  ";
		}
	}

	Consola::setBackgroundColor(TEXT_BACKGROUND);
}

void View::updateAllShips(std::vector<ShipModel*> const& ships) const
{
	
	for (ShipModel* const &ship : ships)
	{
		int x = ship->getPosition()->getX();
		int y = ship->getPosition()->getY();
		goToMapPosition(x, y);
		Consola::setBackgroundColor(FRIENDLY_SHIP_COLOR);
		std::cout << std::setw(2) << ship->getID();
	}
	Consola::setBackgroundColor(TEXT_BACKGROUND);
}

void View::goToMapPosition(int x, int y) const
{
	x = (x + 1) * 2;
	y = (y + 1);
	Consola::gotoxy(x, y);
}

CellModel* View::convertStringCommandToCell(std::string command, CellModel* currentCell, GameController *gameController) const
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
