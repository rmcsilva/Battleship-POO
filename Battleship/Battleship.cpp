// Battleship.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameController.h"
#include "View.h"

int main()
{
	//TODO: Make logs 
	//TODO: Add game difficulty, it changes probabilities and coins/costs
	//MapModel gameMap = MapModel(10, 20);
	GameController gameController;
	View gameView;

	//gameController.readInitialFileConfigs("initialConfig.txt");

	//CellModel::Type tipo = gameController.getCellAt(10, 2)->getType();
	//if (tipo == CellModel::Type::PORT) {
	//	std::cout << "Certo" << std::endl;
	//}

	//Consola::getch();

	gameView.setupLayout(&gameController);
	

    return 0;
}

