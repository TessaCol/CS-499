/*
-------------------------------------------------------
Title: LCR Dice Game - Game Class
Name: Tessa Collier
Course: IT 312
Date: August 13, 2026
Project: Final Project

Code Description:
This file contains the implementation of the LCR game.
-------------------------------------------------------
*/

#include "LCRGame.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Initializes the game and connects it to the database.
LCRGame::LCRGame(LCRDatabase& database)
    : m_database(database)
{
    m_numPlayers = 0;
    m_currentPlayer = 0;
    m_centerPot = 0;
}

// Displays the game rules from the text file.
void LCRGame::DisplayRules()
{
    std::ifstream rulesFile(
        "C:\\Users\\Dunge\\Downloads\\Dice-Tessacollier\\x64\\Debug\\LCRRules.txt"
    );

    if (!rulesFile)
    {
        std::cout << "Error: Could not open LCRRules.txt."
            << std::endl;

        std::cout << "Make sure the file is in the same folder as the program."
            << std::endl << std::endl;

        return;
    }

    std::cout << "========================================"
        << std::endl;

    std::cout << "       LEFT CENTER RIGHT RULES"
        << std::endl;

    std::cout << "========================================"
        << std::endl;

    std::string line;

    // Read and display each line of the rules file.
    while (std::getline(rulesFile, line))
    {
        std::cout << line << std::endl;
    }

    rulesFile.close();

    std::cout << "========================================"
        << std::endl << std::endl;
}

// Gets the number of players and their names.
void LCRGame::SetupGame()
{
    while (true)
    {
        std::cout << "Enter the number of players: ";
        std::cin >> m_numPlayers;

        // Handle input that is not a number.
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            std::cout << "Invalid input. "
                << "Please enter a number of 3 or more."
                << std::endl << std::endl;

            continue;
        }

        // LCR requires at least three players.
        if (m_numPlayers < 3)
        {
            std::cout << "LCR requires at least 3 players."
                << std::endl << std::endl;

            continue;
        }

        break;
    }

    // Clear the vector before adding players.
    m_players.clear();

    // Reserve space for the requested number of players.
    m_players.reserve(m_numPlayers);

    for (int i = 0; i < m_numPlayers; i++)
    {
        std::string name;

        while (true)
        {
            std::cout << "Enter the name of player "
                << i + 1 << ": ";

            std::cin >> name;

            if (!name.empty())
            {
                break;
            }

            std::cout << "Invalid name. "
                << "Please enter a player name."
                << std::endl;
        }

        // Create a player and add it to the vector.
        Player player;
        player.SetName(name);
        m_players.push_back(player);
    }

    // Player records will be saved with the completed game.
    std::cout << std::endl;
    std::cout << "Game setup complete!"
        << std::endl << std::endl;
}

// Generates a random die value from 1 through 6.
int LCRGame::RollDie()
{
    static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());
    static std::uniform_int_distribution<int> distribution(1, 6);

    return distribution(generator);
}

// Processes a die result and transfers chips when needed.
void LCRGame::ProcessDieResult(int result)
{
    if (result == 1)
    {
        // Find the player to the left, wrapping around the vector.
        int leftPlayer =
            (m_currentPlayer - 1 + m_numPlayers) % m_numPlayers;

        m_players[m_currentPlayer].RemoveChip();
        m_players[leftPlayer].AddChip();

        std::cout << "L - "
            << m_players[m_currentPlayer].GetName()
            << " passes a chip to "
            << m_players[leftPlayer].GetName()
            << "." << std::endl;
    }
    else if (result == 2)
    {
        // Find the player to the right, wrapping around the vector.
        int rightPlayer =
            (m_currentPlayer + 1) % m_numPlayers;

        m_players[m_currentPlayer].RemoveChip();
        m_players[rightPlayer].AddChip();

        std::cout << "R - "
            << m_players[m_currentPlayer].GetName()
            << " passes a chip to "
            << m_players[rightPlayer].GetName()
            << "." << std::endl;
    }
    else if (result == 3)
    {
        // Move a chip into the center pot.
        m_players[m_currentPlayer].RemoveChip();
        m_centerPot++;

        std::cout << "C - "
            << m_players[m_currentPlayer].GetName()
            << " puts a chip in the center."
            << std::endl;
    }
    else
    {
        // Results 4, 5, and 6 do not move a chip.
        std::cout << "* - No action."
            << std::endl;
    }
}

// Plays one player's turn.
void LCRGame::PlayTurn()
{
    Player& player = m_players[m_currentPlayer];

    // A player rolls up to three dice, limited by their chip count.
    int numberOfDice = player.GetChips();

    if (numberOfDice > 3)
    {
        numberOfDice = 3;
    }

    // Players without chips skip their turn.
    if (numberOfDice == 0)
    {
        std::cout << player.GetName()
            << " has no chips and skips the roll."
            << std::endl;

        return;
    }

    std::cout << player.GetName()
        << " has "
        << player.GetChips()
        << " chip(s) and rolls "
        << numberOfDice
        << " die/dice."
        << std::endl;

    // Roll each die and process its result.
    for (int die = 0; die < numberOfDice; die++)
    {
        int result = RollDie();
        ProcessDieResult(result);
    }
}

// Counts players who still have at least one chip.
int LCRGame::CountPlayersWithChips() const
{
    int playersWithChips = 0;

    // Check each player in the vector.
    for (const Player& player : m_players)
    {
        if (player.GetChips() > 0)
        {
            playersWithChips++;
        }
    }

    return playersWithChips;
}

// The game ends when only one player has chips.
bool LCRGame::HasWinner() const
{
    return CountPlayersWithChips() == 1;
}

// Displays the current chip totals.
void LCRGame::DisplayScores() const
{
    std::cout << std::endl;
    std::cout << "Current Chip Totals:"
        << std::endl;

    for (const Player& player : m_players)
    {
        std::cout << player.GetName()
            << ": "
            << player.GetChips()
            << " chip(s)"
            << std::endl;
    }

    std::cout << "Center Pot: "
        << m_centerPot
        << " chip(s)"
        << std::endl << std::endl;
}

// Runs the game and saves the completed results.
void LCRGame::RunGame()
{
    DisplayRules();
    SetupGame();

    std::cout << "The game is starting!"
        << std::endl << std::endl;

    // Continue until only one player has chips.
    while (!HasWinner())
    {
        std::cout << "----------------------------------------"
            << std::endl;

        std::cout << "It is "
            << m_players[m_currentPlayer].GetName()
            << "'s turn."
            << std::endl;

        PlayTurn();
        DisplayScores();

        // Move to the next player, wrapping around when necessary.
        m_currentPlayer =
            (m_currentPlayer + 1) % m_numPlayers;
    }

    // Collect the final names and chip counts for saving.
    std::vector<std::string> playerNames;
    std::vector<int> chipCounts;
    int winnerIndex = -1;

    for (int i = 0; i < static_cast<int>(m_players.size()); i++)
    {
        playerNames.push_back(m_players[i].GetName());
        chipCounts.push_back(m_players[i].GetChips());

        // Remember the index of the player who has chips.
        if (m_players[i].GetChips() > 0)
        {
            winnerIndex = i;
        }
    }

    // Announce the winner and save the completed game.
    if (winnerIndex >= 0)
    {
        const Player& winner = m_players[winnerIndex];

        std::cout << "========================================"
            << std::endl;

        std::cout << "WINNER: "
            << winner.GetName()
            << "!" << std::endl;

        std::cout << "They have "
            << winner.GetChips()
            << " chip(s)."
            << std::endl;

        std::cout << "========================================"
            << std::endl;

        // Save the winner and final chip counts to SQLite.
        if (m_database.SaveCompletedGame(
            playerNames, chipCounts, winnerIndex))
        {
            std::cout << "Game results saved to the database."
                << std::endl;
        }
        else
        {
            std::cout << "Warning: Game results could not be saved."
                << std::endl;
        }
    }
}
