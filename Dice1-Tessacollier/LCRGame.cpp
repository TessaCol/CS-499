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


// Constructor.
LCRGame::LCRGame()
{
    m_numPlayers = 0;
    m_currentPlayer = 0;
    m_centerPot = 0;
}


// Displays the rules from the text file.
void LCRGame::DisplayRules()
{
    std::ifstream rulesFile("LCRRules.txt");

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

    while (std::getline(rulesFile, line))
    {
        std::cout << line << std::endl;
    }

    rulesFile.close();

    std::cout << "========================================"
        << std::endl;

    std::cout << std::endl;
}


// Sets up the players.
void LCRGame::SetupGame()
{
    do
    {
        std::cout << "Enter the number of players: ";
        std::cin >> m_numPlayers;

        if (m_numPlayers < 3)
        {
            std::cout << "LCR requires at least 3 players."
                << std::endl;

            std::cout << "Please add more players."
                << std::endl << std::endl;
        }

        if (m_numPlayers > MAX_PLAYERS)
        {
            std::cout << "The maximum number of players is "
                << MAX_PLAYERS << "."
                << std::endl << std::endl;
        }

    } while (m_numPlayers < 3 || m_numPlayers > MAX_PLAYERS);


    for (int i = 0; i < m_numPlayers; i++)
    {
        std::string name;

        std::cout << "Enter the name of player "
            << i + 1 << ": ";

        std::cin >> name;

        m_players[i].SetName(name);
    }

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


// Processes the result of one die.
void LCRGame::ProcessDieResult(int result)
{
    // A result of 1 means Left.
    if (result == 1)
    {
        int leftPlayer =
            (m_currentPlayer - 1 + m_numPlayers) % m_numPlayers;

        m_players[m_currentPlayer].RemoveChip();

        m_players[leftPlayer].AddChip();

        std::cout << "L - "
            << m_players[m_currentPlayer].GetName()
            << " passes a chip to "
            << m_players[leftPlayer].GetName()
            << "."
            << std::endl;
    }

    // A result of 2 means Right.
    else if (result == 2)
    {
        int rightPlayer =
            (m_currentPlayer + 1) % m_numPlayers;

        m_players[m_currentPlayer].RemoveChip();

        m_players[rightPlayer].AddChip();

        std::cout << "R - "
            << m_players[m_currentPlayer].GetName()
            << " passes a chip to "
            << m_players[rightPlayer].GetName()
            << "."
            << std::endl;
    }

    // A result of 3 means Center.
    else if (result == 3)
    {
        m_players[m_currentPlayer].RemoveChip();

        m_centerPot++;

        std::cout << "C - "
            << m_players[m_currentPlayer].GetName()
            << " puts a chip in the center."
            << std::endl;
    }

    // Results 4 through 6 are neutral dots.
    else
    {
        std::cout << "* - No action."
            << std::endl;
    }
}


// Plays one player's turn.
void LCRGame::PlayTurn()
{
    Player& player = m_players[m_currentPlayer];

    // A player rolls one die for each chip they have,
    // with a maximum of three dice.
    int numberOfDice = player.GetChips();

    if (numberOfDice > 3)
    {
        numberOfDice = 3;
    }

    // Players with no chips skip their roll.
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

    for (int die = 0; die < numberOfDice; die++)
    {
        int result = RollDie();

        ProcessDieResult(result);
    }
}


// Counts players who currently have at least one chip.
int LCRGame::CountPlayersWithChips() const
{
    int playersWithChips = 0;

    for (int i = 0; i < m_numPlayers; i++)
    {
        if (m_players[i].GetChips() > 0)
        {
            playersWithChips++;
        }
    }

    return playersWithChips;
}


// Determines whether only one player still has chips.
bool LCRGame::HasWinner() const
{
    return CountPlayersWithChips() == 1;
}


// Displays each player's current chip count.
void LCRGame::DisplayScores() const
{
    std::cout << std::endl;

    std::cout << "Current Chip Totals:"
        << std::endl;

    for (int i = 0; i < m_numPlayers; i++)
    {
        std::cout << m_players[i].GetName()
            << ": "
            << m_players[i].GetChips()
            << " chip(s)"
            << std::endl;
    }

    std::cout << "Center Pot: "
        << m_centerPot
        << " chip(s)"
        << std::endl;

    std::cout << std::endl;
}


// Runs the complete game.
void LCRGame::RunGame()
{
    DisplayRules();

    SetupGame();

    std::cout << "The game is starting!"
        << std::endl << std::endl;

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

        // Move to the next player.
        m_currentPlayer =
            (m_currentPlayer + 1) % m_numPlayers;
    }


    // Find and display the winner.
    for (int i = 0; i < m_numPlayers; i++)
    {
        if (m_players[i].GetChips() > 0)
        {
            std::cout << "========================================"
                << std::endl;

            std::cout << "WINNER: "
                << m_players[i].GetName()
                << "!"
                << std::endl;

            std::cout << "They have "
                << m_players[i].GetChips()
                << " chip(s)."
                << std::endl;

            std::cout << "========================================"
                << std::endl;

            break;
        }
    }
}