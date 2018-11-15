#pragma once
#include "Consola.h"
#include "GameController.h"
class View
{
	const int GROUND_COLOR_MAIN = Consola::BRANCO;
	const int GROUND_COLOR_OFF = Consola::BRANCO_CLARO;
	const int SEA_COLOR_MAIN = Consola::AZUL;
	const int SEA_COLOR_OFF = Consola::AZUL_CLARO;
	const int FRIENDLY_PORT_COLOR = Consola::CINZENTO;
	const int ENEMY_PORT_COLOR = Consola::AMARELO_CLARO;
	const int FRIENDLY_SHIP_COLOR = Consola::VERDE_CLARO;
	const int ENEMY_SHIP_COLOR = Consola::VERMELHO_CLARO;

	const int ERROR_COLOR = Consola::VERMELHO_CLARO;
	const int SUCESS_COLOR = Consola::VERDE_CLARO;
	const int TEXT_COLOR = Consola::BRANCO;

	const int TEXT_BACKGROUND = Consola::PRETO;

	enum class InitialCommands {CONFIG, INVALID};
	enum class GameCommands
	{
		EXEC,
		PROX,
		COMPRANAV,
		MOEDAS,
		SAIR,
		INVALID
	};
	//TODO: Put in a separate header file with error messages and stuff
	const char* INITIAL_LAYOUT = "Battleship Setup\n";
	const char* COMMAND_LINE = "Command Line: ";
	const char* READ_SUCESS = "File read sucessfully! \nPress any key to start the game...";
	const char* ERROR_READING_FILE = "Error reading from file: ";
public:
	View();

	void setupLayout(GameController *gameController);
	void initialLayout(GameController *gameController) const;
	bool readInitialCommands(std::string const &input, GameController *gameController) const;
	static InitialCommands stringToInitialCommand(std::string const& inString);

	void gameLayout(GameController *gameController) const;
	void paintMapCell(CellModel* cell, bool mainColor) const;
	void gameAction(GameController *gameController);
	bool readGameCommands(std::string const &input, GameController *gameController) const;
	static GameCommands stringToGameCommand(std::string const& inString);
	void showFriendlyPortsInfo(std::vector<PortModel*> const &ports) const;
};

