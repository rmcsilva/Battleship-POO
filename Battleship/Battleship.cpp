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

	//TODO: Fix errors when removing ship
	//TODO: Update Fish Cells
	//TODO: Add a info command that shows a ship information

	gameView.setupLayout(&gameController);
	
    return 0;
}

