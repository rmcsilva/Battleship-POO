// Battleship.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameController.h"
#include "View.h"

int main()
{
	//TODO: Make logs 
	//TODO: Add game difficulty, it changes probabilities and coins/costs
	GameController gameController;
	View gameView;

	srand(time(NULL));

	//TODO: Implement enemy ships

	gameView.setupLayout(&gameController);
	
    return 0;
}

