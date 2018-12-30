// Battleship.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameController.h"
#include "View.h"

int main()
{
	GameController gameController;
	View gameView;

	srand(time(NULL));

	gameView.setupLayout(&gameController);
	
    return 0;
}

