/*
-------------------------------------------------------
Title: LCR Dice Game - Player Class
Name: Tessa Collier
Course: IT 312
Date: August 13, 2026
Project: Final Project

Code Description:
This class represents a player in the LCR game.
It stores the player's name and number of chips.
-------------------------------------------------------
*/

#pragma once

#include <string>
#include <vector>
#include "sqlite3.h"

class LCRDatabase
{
public:
    LCRDatabase();
    ~LCRDatabase();

    bool OpenDatabase(const std::string& fileName);
    void CloseDatabase();
    bool CreateTables();

    int AddPlayer(const std::string& playerName);

    bool SaveCompletedGame(
        const std::vector<std::string>& playerNames,
        const std::vector<int>& chipCounts,
        int winnerIndex
    );

private:
    sqlite3* database;
};
