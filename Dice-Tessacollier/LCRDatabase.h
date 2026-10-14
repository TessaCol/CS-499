/*
-------------------------------------------------------
Title: LCR Dice Game Database
Name: Tessa Collier
Course: IT 312
Date: October 02, 2026
Project: Final Project

Code Description:
This class handles the database for the Left Center
Right dice game.

The class opens and closes the database and creates
the tables needed to store game information.
-------------------------------------------------------
*/

#pragma once

#include <string>
#include "sqlite3.h"

class LCRDatabase
{
public:
	LCRDatabase();
	~LCRDatabase();

	bool OpenDatabase( const std::string& fileName );
	void CloseDatabase();
	bool CreateTables();

	int AddPlayer( const std::string& playerName );

private:
	sqlite3* database;
};
