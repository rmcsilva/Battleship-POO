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
	const int LOST_SHIP_COLOR = Consola::CYAN_CLARO;
	const int EVENT_COLOR = Consola::ROXO;

	//TODO:Add lost ship color

	const int ERROR_COLOR = Consola::VERMELHO_CLARO;
	const int SUCESS_COLOR = Consola::VERDE_CLARO;
	const int TEXT_COLOR = Consola::BRANCO;
	const int SHIP_TEXT_COLOR = Consola::PRETO;

	const int TEXT_BACKGROUND = Consola::PRETO;

	//TODO: Put in a separate header file with error messages and stuff
	const char* INITIAL_LAYOUT = "Battleship Setup\n";
	const char* COMMAND_LINE = "Command Line: ";
	const char* READ_SUCESS = "File read sucessfully! \nPress any key to start the game...";
	const char* ERROR_READING_FILE = "Error reading from file: ";
	const char* COMMAND_EXECUTE_ERROR = "Command could not be executed! Recheck and try again!\n";
public:
	View();

	enum class InitialCommands { CONFIG, INVALID };
	enum class GameCommands
	{
		EXEC,
		PROX,
		COMPRANAV,
		VENDENAV,
		LISTA,
		COMPRA,
		VENDE,
		MOVE,
		AUTO,
		STOP,
		PIRATA,
		EVPOS,
		EVNAV,
		MOEDAS,
		VAIPARA,
		COMPRASOLD,
		SAVEG,
		LOADG,
		DELG,
		SAIR,
		INVALID
	};

	void setupLayout(GameController *gameController);
	void initialLayout(GameController *gameController) const;
	bool readInitialCommands(std::string const &input, GameController *gameController) const;
	static InitialCommands stringToInitialCommand(std::string const& inString);

	void gameLayout(GameController *gameController) const;
	void paintInitialMapCell(CellModel* cell, bool mainColor) const;
	void gameAction(GameController *gameController);
	bool readGameCommands(std::string const &input, GameController *gameController) const;
	static GameCommands stringToGameCommand(std::string const& inString);
	void showFriendlyPortsInfo(std::vector<PortModel*> const &ports) const;
	void showLogsInfo(std::string enemyLog, std::string combatLog, std::string eventLog) const;
	void updateAllSeaCells(std::vector<SeaModel*> const &seaCells) const;
	void updateSeaCell(SeaModel* const &seaCell) const;
	void updateAllPortCells(std::vector<PortModel*> const &friendlyPorts, std::vector<PortModel*> const &enemyPorts) const;
	void updatePortCell(PortModel* const &portCell) const;
	void updateEventInformation(const GameController *gameController) const;
	static void goToMapPosition(int x, int y);
	static void goToMapOffPosition(int x, int y);
	static CellModel* convertStringCommandToCell(std::string command, CellModel* currentCell, GameController *gameController);
};

