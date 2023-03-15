#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// color variables
constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;

// constructor
Game::Game()
	: m_isGameOver(false)
{

}

Game::~Game()
{

}

bool Game::Load()
{
	return m_level.Load("Level1.txt", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}

void Game::Run()
{
	Draw();

	m_isGameOver = Update(); // sets gameover to true or false
	if (m_isGameOver)
	{
		Draw();
	}
}

void Game::Unload() // useful for when we need to clear after the level.
{

}

bool Game::isGameOver()
{
	return m_isGameOver;
}

bool Game::Update()
{
    char input = (char)_getch();

    // create 2 variables that will store the playerXY so we can see if the new position is over a space.
    int newPlayerX = m_player.GetXPosition();
    int newPlayerY = m_player.GetYPosition();
    switch (input)
    {
    case'w':
    case'W':
    {
        newPlayerY--;
        break;
    }
    case's':
    case'S':
    {
        newPlayerY++;
        break;
    }
    case'a':
    case'A':
    {
        newPlayerX--;
        break;
    }
    case'd':
    case'D':
    {
        newPlayerX++;
        break;
    }
    default:
        break;
    }

 
    //check to see if the level of the index is equal to ' '
    if (m_level.IsSpace(newPlayerX, newPlayerY))
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }

    else if (m_level.IsKey(newPlayerX, newPlayerY))
    {
        m_level.PickUpKey(newPlayerX, newPlayerY);
        m_player.PickUpKey();
                            m_level.IsSpace(newPlayerX, newPlayerY) == true;
        m_player.SetPosition(newPlayerX, newPlayerY);
        // Player pick up key sound.

    }
    else if (m_level.IsDoor(newPlayerX, newPlayerY) && m_player.hasKey())
    {
        m_level.OpenDoor(newPlayerX, newPlayerY);
        m_player.UseKey();
        m_player.SetPosition(newPlayerX, newPlayerY);
        // play door open sound
    }
    else if (m_level.IsDoor(newPlayerX, newPlayerY) && !m_player.hasKey())
    {
       // PlayDoorClosedSound();
    }
    else if (m_level.IsGoal(newPlayerX, newPlayerY))
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
        return true; // meaing the game is Over
    }
    return false;

}

void Game::Draw()
{
    system("cls");
    for (int y = 0; y < m_level.GetHeight(); y++)
    {
        for (int x = 0; x < m_level.GetWidth(); x++)
        {
            if (m_player.GetXPosition() == x && m_player.GetYPosition() == y)
            {
                m_player.Draw();
            }
            else
            {
                // enable us to bring the colors to the console
                HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
                if (m_level.IsDoor(x, y))
                {
                    if (m_player.hasKey())
                    {
                        SetConsoleTextAttribute(console, kOpenDoorColor);
                    }
                    else
                    {
                        SetConsoleTextAttribute(console, kClosedDoorColor);
                    }
                }
                else
                {
                    SetConsoleTextAttribute(console, kRegularColor);
                }

                m_level.Draw(x, y); // will draw with either 3 colors kRegularColor, kClosedDoorColor, kOpenDoorColor
            }
        }

        std::cout << endl;
    }
}