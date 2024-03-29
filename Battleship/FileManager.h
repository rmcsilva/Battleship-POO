#pragma once
#include "MapModel.h"
#include "GameModel.h"


class GameController;

class FileManager
{
	enum class InitialConfigsCommands {
		linhas,
		colunas,
		moedas,
		probpirata,
		preconavio,
		precosoldado,
		precovendpeixe,
		precocompmercad,
		precovendmercad,
		soldadosporto,
		probevento,
		probtempestade,
		probsereias,
		probcalmaria,
		probmotim,
		INVALID
	};
public:
	FileManager();
	~FileManager();

	bool readInitialFileConfigs(std::string filename, MapModel *&map, GameModel *game);
	bool executeCommandsFromFile(std::string filename, GameController *gameController);
	static InitialConfigsCommands stringToInitialConfigs(std::string const& inString);
	bool setupMap(std::ifstream &file,int const &lines, MapModel *&map, GameModel *game);
	bool readMap(std::ifstream &file, int const &lines, int const &columns,MapModel *map, GameModel *game);
};

