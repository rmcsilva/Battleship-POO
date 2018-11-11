// Battleship.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Consola.h"
#include "MapModel.h"
#include "SeaModel.h"
#include "GameController.h"
#include <iostream>

int main()
{
	//TODO: Make logs 
	//TODO: Add game difficulty, it changes probabilities and coins/costs
	MapModel gameMap = MapModel(10, 20);
	GameController gameController;

	gameController.readInitialFileConfigs("initialConfig.txt");

	CellModel::Type tipo = gameController.getCellAt(10, 2)->getType();
	if (tipo == CellModel::Type::PORT) {
		std::cout << "Certo" << std::endl;
	}

	Consola::getch();
    return 0;
}

