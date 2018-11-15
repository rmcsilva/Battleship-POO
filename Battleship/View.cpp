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
	for (int i = 0; i <gameController->getNumColumns(); i++)
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
		std::cout << std::setw(2) << i;
		for (int j = 0; j < gameController->getNumColumns(); j++)
		{
			if ((i+j) % 2) mainColor = true;
			else	   mainColor = false;
			paintMapCell(gameController->getCellAt(j, i), mainColor);
		}
		Consola::setBackgroundColor(TEXT_BACKGROUND);
		std::cout << '\n';
	}
	Consola::setBackgroundColor(TEXT_BACKGROUND);
}

void View::paintMapCell(CellModel* cell, bool mainColor) const
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
			if (port->getOwner() == CellModel::Owner::PLAYER)
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
		case GameCommands::PROX: break;
		case GameCommands::COMPRANAV:
			//TODO: Complete function, need to implement ships first!
			if (!gameController->buyShip())
				std::cout << "Player does not have enough coins!";
			break;
		case GameCommands::MOEDAS:
			//Read amount
			//gameController->addCoins(100);
			break;
		case GameCommands::SAIR:
			gameController->endGame();
			return false;
			break;
		case GameCommands::INVALID:
			break;
	}
	return true;
}

View::GameCommands View::stringToGameCommand(std::string const& inString)
{
	if (inString == "exec") return GameCommands::EXEC;
	if (inString == "prox") return GameCommands::PROX;
	if (inString == "compranav") return GameCommands::COMPRANAV;
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

