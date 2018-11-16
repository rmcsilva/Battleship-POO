#include "stdafx.h"
#include "FileController.h"


FileController::FileController()
{
}


FileController::~FileController()
{
}

bool FileController::readInitialFileConfigs(std::string filename, MapModel *&map, EventModel *event, GameModel *game)
{
	//TODO: Add info to logs

	std::ifstream file(filename);
	std::string line;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::stringstream linestream(line);
			std::string command;
			int value;

			//Teste stream
			std::cout << linestream.str() << std::endl;
			
			linestream >> command >> value;
			//std::cout << command << std::endl;

			switch (stringToInitialConfigs(command))
			{
				case InitialConfigsCommands::linhas:
					if (!setupMap(file, value, map, game)) {
						//TODO: Error reading file 
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
					//TODO: COMPLETEEE
					break;
				case InitialConfigsCommands::probevento:
					event->setProbability(value);
					break;
				case InitialConfigsCommands::probtempestade:
					event->setStormProbability(value);
					break;
				case InitialConfigsCommands::probsereias:
					event->setMermaidProbability(value);
					break;
				case InitialConfigsCommands::probcalmaria:
					event->setCalmProbability(value);
					break;
				case InitialConfigsCommands::probmotim:
					event->setRiotProbability(value);
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
	file.close();
}

FileController::InitialConfigsCommands FileController::stringToInitialConfigs(std::string const & inString)
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

bool FileController::setupMap(std::ifstream &file,int const &lines, MapModel *&map, GameModel *game)
{
	std::string line;

	if (std::getline(file, line)) {
		std::stringstream linestream(line);
		std::cout << linestream.str() << std::endl;

		std::string command;
		int value;

		linestream >> command >> value;

		std::cout << command << std::endl;
		std::cout << value << std::endl;

		if (stringToInitialConfigs(command) == InitialConfigsCommands::colunas) {
			try {
				map = new MapModel(lines, value);
			}
			catch (std::bad_alloc& e) {
				std::cerr << "bad_alloc caught: " << e.what() << '\n';
				//TODO: add to log invalid lines, columns number
			}

			if (readMap(file, lines, value, map, game)) {
				return true;
			}
			else {
				return false;
			}
			
			
		} else {
			//TODO: Ordem errada no ficheiro
			return false;
		}	
	} else {
		//TODO:Add to log 
		return false;
	}

	return true;
}

bool FileController::readMap(std::ifstream & file, int const & lines, int const & columns, MapModel *map, GameModel *game)
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
					map->addPortCellAt(j, i, cellType, CellModel::CellOwner::PLAYER);
					game->addFriendlyPort((PortModel*)map->getCellAt(j,i));
				} 
				else {
					map->addPortCellAt(j, i, cellType, CellModel::CellOwner::PIRATE);
					game->addPiratePort((PortModel*)map->getCellAt(j, i));
				}
			}
			else if (cellType == '.') {
				map->addCellAt(j, i, CellModel::Type::SEA);
				game->addSeaCell((SeaModel*)map->getCellAt(j, i));
			}
			else if (cellType == '+') {
				map->addCellAt(j, i, CellModel::Type::GROUND);
			}
			else {
				return false;
			}
			std::cout << cellType;
		}
		std::cout << std::endl;
	}
	//Consume the last line
	std::string buffer;
	std::getline(file, buffer);
	return true;
}

