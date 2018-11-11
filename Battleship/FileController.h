#pragma once
#include "MapModel.h"
#include "EventModel.h"
#include "GameModel.h"

class FileController
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
		probmotim
	};
public:
	FileController();
	~FileController();

	bool readInitialFileConfigs(std::string filename, MapModel *&map, EventModel *event, GameModel *game);
	InitialConfigsCommands stringToInitialConfigs(std::string const& inString);
	bool setupMap(std::ifstream &file,int const &lines, MapModel *&map, GameModel *game);
	bool readMap(std::ifstream &file, int const &lines, int const &columns,MapModel *map, GameModel *game);
};

