#include "stdafx.h"
#include "View.h"


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
			initialLayout(gameController);
			break;
		case GameState::GAME:
			//TODO: Make game menu
			Consola::clrscr();
			std::cout << "In game";
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

