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
#include <fstream>
#include <iostream>
#include <random>
#include <string>

class LCRGame
{
private:
    // Maximum number of players allowed by the program.
    static const int MAX_PLAYERS = 100;

    Player m_players[MAX_PLAYERS];
    int m_numPlayers;
    int m_currentPlayer;
    int m_centerPot;

    // Displays the rules stored in the text file.
    void DisplayRules();

    // Gets the number of players and their names.
    void SetupGame();

    // Rolls the dice and processes the current player's turn.
    void PlayTurn();

    // Generates a random number from 1 through 6.
    int RollDie();

    // Processes one result from a die.
    void ProcessDieResult(int result);

    // Returns the number of players who currently have chips.
    int CountPlayersWithChips() const;

    // Determines whether the game has a winner.
    bool HasWinner() const;

    // Displays the current chip totals.
    void DisplayScores() const;

public:
    // Constructor.
    LCRGame();

    // Starts and controls the complete game.
    void RunGame();
};