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

class Player
{
private:
    std::string m_name;
    int m_chips;

public:
    Player();

    void SetName(const std::string& name);

    std::string GetName() const;

    int GetChips() const;

    void AddChip();

    void RemoveChip();
};
