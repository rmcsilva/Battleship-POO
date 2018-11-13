#include "stdafx.h"
#include "View.h"
#include <iomanip>


View::View()
{
}

void View::setupLayout(GameController *gameController)
{
	while (gameController->getGameState() != GameState::END)
	{
		switch (gameController->getGameState())
		{
		case GameState::SETUP:
			//TODO:Uncomment this is for tests only
			initialLayout(gameController);
			//gameController->readInitialFileConfigs("initialConfig.txt");
			break;
		case GameState::GAME:
			//TODO: Make game menu
			Consola::clrscr();
			gameLayout(gameController);
			Consola::getch();
			break;
		case GameState::END:
			//TODO: Menu with score
			break;
		}
	}
}

void View::initialLayout(GameController *gameController)
{
	Consola::clrscr();
	std::cout << INITIAL_LAYOUT;

	while (true) {
		std::cout << COMMAND_LINE;
		std::string command;
		std::getline(std::cin, command);

		if (readInitialCommands(command, gameController)) {
			//TODO: Show initial stats 
			return;
		}
	}
	


}

bool View::readInitialCommands(std::string const &input, GameController * gameController)
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
				Consola::setTextColor(SUCESS_COLOR);
				std::cout << READ_SUCESS;
				Consola::setTextColor(TEXT_COLOR);
				Consola::getch();
				return true;
			}
			Consola::setTextColor(ERROR_COLOR);
			std::cout << ERROR_READING_FILE << filename << std::endl;
			Consola::setTextColor(TEXT_COLOR);
			return false;
			break;
		}
		default:
			return false;
			break;
	}
}

View::InitialCommands View::stringToInitialCommand(std::string const & inString)
{
	if (inString == "config") return InitialCommands::CONFIG;
	return InitialCommands::INVALID;
}

void View::gameLayout(GameController* gameController)
{	
	Consola::gotoxy(2, 0);
	for (int i = 0; i <gameController->getNumColumns(); i++)
	{
		if (i%2)Consola::setTextColor(Consola::CINZENTO); 
		else	Consola::setTextColor(Consola::BRANCO_CLARO);
		std::cout << std::setw(2) << i;
	}

	Consola::setTextColor(TEXT_COLOR);
	Consola::gotoxy(0, 1);

	bool mainColor;
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

void View::paintMapCell(CellModel* cell, bool mainColor)
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

