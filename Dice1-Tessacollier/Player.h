#pragma once
/*
-------------------------------------------------------
Title: LCR Dice Game - Player Class
Name: Tessa Collier
Course: IT 312
Date: August 13, 2026
Project: Final Project

Code Description:
This class represents a player in the LCR game. It stores
the player's name and number of chips. Methods are provided
to set and retrieve the player's information and to add or
remove chips during the game.

The Player class separates player information from the game
logic, making the program easier to organize and maintain.
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
    // Creates a player with no name and three starting chips.
    Player()
    {
        m_name = "";
        m_chips = 3;
    }

    // Sets the player's name.
    void SetName(const std::string& name)
    {
        m_name = name;
    }

    // Returns the player's name.
    std::string GetName() const
    {
        return m_name;
    }

    // Returns the player's current number of chips.
    int GetChips() const
    {
        return m_chips;
    }

    // Adds one chip to the player's total.
    void AddChip()
    {
        m_chips++;
    }

    // Removes one chip from the player's total.
    void RemoveChip()
    {
        if (m_chips > 0)
        {
            m_chips--;
        }
    }
};