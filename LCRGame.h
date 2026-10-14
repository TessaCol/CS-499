/*
-------------------------------------------------------
Title: LCR Dice Game - Game Class
Name: Tessa Collier
Course: IT 312
Date: August 13, 2026
Project: Final Project

Code Description:
This class controls the main LCR game. It handles reading
the rules file, setting up the players, rolling the dice,
moving chips, determining when the game is over, and
displaying the winner.
-------------------------------------------------------
*/

#pragma once

#include "Player.h"
#include "LCRDatabase.h"
#include <vector>

class LCRGame
{
private:
	std::vector<Player> m_players;
	int m_numPlayers;
	int m_currentPlayer;
	int m_centerPot;
	LCRDatabase& m_database;

	void DisplayRules();
	void SetupGame();
	void PlayTurn();
	int RollDie();
	void ProcessDieResult( int result );
	int CountPlayersWithChips() const;
	bool HasWinner() const;
	void DisplayScores() const;

public:
	LCRGame( LCRDatabase& database );
	void RunGame();
};