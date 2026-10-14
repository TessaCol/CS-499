/*
-------------------------------------------------------
Title: LCR Dice Game Database
Name: Tessa Collier
Course: IT 312
Date: October 02, 2026
Project: Final Project

Code Description:
This class connects the LCR game to the SQLite database.

The class opens the database, creates the required
tables, adds players, and closes the database when it
is finished.
-------------------------------------------------------
*/

#include "LCRDatabase.h"
#include <iostream>

LCRDatabase::LCRDatabase()
{
	database = nullptr;
}

LCRDatabase::~LCRDatabase()
{
	CloseDatabase();
}

bool LCRDatabase::OpenDatabase( const std::string& fileName )
{
	int result = sqlite3_open( fileName.c_str() , &database );

	if ( result != SQLITE_OK )
	{
		std::cout << "Unable to open database." << std::endl;
		return false;
	}

	std::cout << "Database opened successfully." << std::endl;

	std::cout << "Database file: "
		<< sqlite3_db_filename( database , "main" )
		<< std::endl;

	return true;
}

void LCRDatabase::CloseDatabase()
{
	if ( database != nullptr )
	{
		sqlite3_close( database );
		database = nullptr;
	}
}

bool LCRDatabase::CreateTables()
{
	const char* sql = R"sql(

		CREATE TABLE IF NOT EXISTS Players
		(
			player_id INTEGER PRIMARY KEY AUTOINCREMENT,
			player_name TEXT NOT NULL
		);

		CREATE TABLE IF NOT EXISTS Games
		(
			game_id INTEGER PRIMARY KEY AUTOINCREMENT,
			game_date DATETIME DEFAULT CURRENT_TIMESTAMP,
			winner_id INTEGER,
			FOREIGN KEY (winner_id) REFERENCES Players(player_id)
		);

		CREATE TABLE IF NOT EXISTS GamePlayers
		(
			game_player_id INTEGER PRIMARY KEY AUTOINCREMENT,
			game_id INTEGER NOT NULL,
			player_id INTEGER NOT NULL,
			player_position INTEGER NOT NULL,
			chip_count INTEGER NOT NULL DEFAULT 3,
			FOREIGN KEY (game_id) REFERENCES Games(game_id),
			FOREIGN KEY (player_id) REFERENCES Players(player_id)
		);

		CREATE TABLE IF NOT EXISTS Turns
		(
			turn_id INTEGER PRIMARY KEY AUTOINCREMENT,
			game_id INTEGER NOT NULL,
			player_id INTEGER NOT NULL,
			dice_rolled INTEGER NOT NULL,
			turn_number INTEGER NOT NULL,
			FOREIGN KEY (game_id) REFERENCES Games(game_id),
			FOREIGN KEY (player_id) REFERENCES Players(player_id)
		);

		CREATE TABLE IF NOT EXISTS DiceResults
		(
			dice_result_id INTEGER PRIMARY KEY AUTOINCREMENT,
			turn_id INTEGER NOT NULL,
			die_number INTEGER NOT NULL,
			result TEXT NOT NULL,
			FOREIGN KEY (turn_id) REFERENCES Turns(turn_id)
		);

		CREATE TABLE IF NOT EXISTS ChipMovements
		(
			movement_id INTEGER PRIMARY KEY AUTOINCREMENT,
			turn_id INTEGER NOT NULL,
			from_player_id INTEGER,
			to_player_id INTEGER,
			movement_type TEXT NOT NULL,
			FOREIGN KEY (turn_id) REFERENCES Turns(turn_id),
			FOREIGN KEY (from_player_id) REFERENCES Players(player_id),
			FOREIGN KEY (to_player_id) REFERENCES Players(player_id)
		);

	)sql";

	char* errorMessage = nullptr;

	int result = sqlite3_exec(
		database ,
		sql ,
		nullptr ,
		nullptr ,
		&errorMessage
	);

	if ( result != SQLITE_OK )
	{
		std::cout << "Unable to create database tables." << std::endl;

		if ( errorMessage != nullptr )
		{
			std::cout << errorMessage << std::endl;
			sqlite3_free( errorMessage );
		}

		return false;
	}

	std::cout << "Database tables created successfully." << std::endl;

	return true;
}


// Adds a player to the Players table.
int LCRDatabase::AddPlayer( const std::string& playerName )
{
	const char* sql =
		"INSERT INTO Players (player_name) VALUES (?);";

	sqlite3_stmt* statement = nullptr;

	int result = sqlite3_prepare_v2(
		database ,
		sql ,
		-1 ,
		&statement ,
		nullptr
	);

	if ( result != SQLITE_OK )
	{
		std::cout << "Unable to prepare player insert."
			<< std::endl;

		return -1;
	}

	sqlite3_bind_text(
		statement ,
		1 ,
		playerName.c_str() ,
		-1 ,
		SQLITE_TRANSIENT
	);

	result = sqlite3_step( statement );

	if ( result != SQLITE_DONE )
	{
		std::cout << "Unable to add player to database."
			<< std::endl;

		std::cout << "SQLite error: "
			<< sqlite3_errmsg( database )
			<< std::endl;

		sqlite3_finalize( statement );

		return -1;
	}

	int playerId =
		static_cast<int>( sqlite3_last_insert_rowid( database ) );

	std::cout << "Player added to database: "
		<< playerName
		<< " (ID "
		<< playerId
		<< ")"
		<< std::endl;

	sqlite3_finalize( statement );

	return playerId;
}