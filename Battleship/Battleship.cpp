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

	srand(time(NULL));
	gameController.readInitialFileConfigs("initialConfig.txt");

	//CellModel::Type tipo = gameController.getCellAt(10, 2)->getType();
	//if (tipo == CellModel::Type::PORT) {
	//	std::cout << "Certo" << std::endl;
	//}
	//Consola::getch();

	//CellModel* cell = gameController.getCellAt(18, 1);
	//std::cout << cell->getX() << "  " << cell->getY() << '\n';
	//cell = gameController.getCellAboveRight(cell);
	//std::cout << cell->getX() << "  " << cell->getY() << '\n';
	//cell = gameController.getCellAboveRight(cell);
	//std::cout << cell->getX() << "  " << cell->getY() << '\n';
	//Consola::getch();

	gameView.setupLayout(&gameController);
	
    return 0;
}

