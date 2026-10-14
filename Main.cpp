/*
-------------------------------------------------------
Title: LCR Dice Game
Name: Tessa Collier
Course: IT 312
Date: August 13, 2026
Project: Final Project

Code Description:
This program runs the Left Center Right dice game.
The main function creates an LCRGame object and starts
the game through the RunGame method.

The program uses object-oriented design with separate
Player and LCRGame classes.
-------------------------------------------------------
*/

#include "LCRGame.h"
#include "LCRDatabase.h"

int main()
{
	LCRDatabase database;

	if ( database.OpenDatabase( "C:\\Users\\Dunge\\Downloads\\Dice-Tessacollier\\Dice-Tessacollier\\LCRDatabase.db" ) )
	{
		database.CreateTables();

		LCRGame game( database );

		game.RunGame();
	}

	return 0;
}