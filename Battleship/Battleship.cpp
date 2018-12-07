// Battleship.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameController.h"
#include "View.h"

int main()
{
	//TODO: Add game difficulty, it changes probabilities and coins/costs
	GameController gameController;
	View gameView;

	srand(time(NULL));

	//TODO: Add visual combat help
	//TODO: Add a info command that shows a ship information

	gameView.setupLayout(&gameController);
	
    return 0;
}

