/*
-------------------------------------------------------
Title: LCR Dice Game - Player Class
Name: Tessa Collier
Course: IT 312
Date: August 13, 2026
Project: Final Project

Code Description:
This file contains the code for the Player class.
-------------------------------------------------------
*/

#include "Player.h"


// Creates a player with no name and three starting chips.
Player::Player()
{
    m_name = "";
    m_chips = 3;
}


// Sets the player's name.
void Player::SetName(const std::string& name)
{
    m_name = name;
}


// Returns the player's name.
std::string Player::GetName() const
{
    return m_name;
}


// Returns the player's current number of chips.
int Player::GetChips() const
{
    return m_chips;
}


// Adds one chip to the player's total.
void Player::AddChip()
{
    m_chips++;
}


// Removes one chip from the player's total.
void Player::RemoveChip()
{
    if (m_chips > 0)
    {
        m_chips--;
    }
}