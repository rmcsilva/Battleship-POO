#include "stdafx.h"
#include "FileControler.h"


FileController::FileController()
{
}


FileController::~FileController()
{
}

bool FileController::readInitialFileConfigs(std::string filename, MapModel *&map)
{
	//TODO: Add info to logs

	std::ifstream file(filename);
	std::string line;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::stringstream linestream(line);
			std::string comand;
			int value;

			//Teste stream
			std::cout << linestream.str() << std::endl;
			
			linestream >> comand >> value;
			//std::cout << comand << std::endl;

			switch (stringToInitialConfigs(comand))
			{
				case InitialConfigsCommands::linhas:
					if (!setupMap(file, value, map)) {
						//TODO: Error reading file 
						return false;
					}
					break;
				case InitialConfigsCommands::moedas:
					break;
				case InitialConfigsCommands::probpirata:
					break;
				default:
					return false;
					break;
			}
		}
	} else {
		return false;
	}
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
}

bool FileController::setupMap(std::ifstream &file,int const &lines, MapModel *&map)
{
	std::string line;

	if (std::getline(file, line)) {
		std::stringstream linestream(line);
		std::cout << linestream.str() << std::endl;

		std::string comand;
		int value;

		linestream >> comand >> value;

		std::cout << comand << std::endl;
		std::cout << value << std::endl;

		if (stringToInitialConfigs(comand) == InitialConfigsCommands::colunas) {
			try {
				map = new MapModel(lines, value);
			}
			catch (int e) {
				//TODO: add to log invalid lines, columns number
			}

			if (readMap(file, lines, value, map)) {
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

bool FileController::readMap(std::ifstream & file, int const & lines, int const & columns, MapModel *map)
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
					map->addPortCellAt(j, i, CellModel::Owner::PLAYER);
				} 
				else {
					map->addPortCellAt(j, i, CellModel::Owner::PIRATE);
				}
			}
			else if (cellType == '.') {
				map->addCellAt(j, i, CellModel::Type::SEA);
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

