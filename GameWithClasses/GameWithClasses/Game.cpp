#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"
#include "AudioManager.h"


using namespace std;

// color variables
constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

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
	return m_level.Load("Level3.txt", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
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

bool Game::IsGameOver()
{
	return m_isGameOver;
}

bool Game::Update()
{
    int input = _getch(); // get input from user and store into variable
    int arrowInput = 0;
    int newPlayerX = m_player.GetXPosition(); // store player position into newPlayerX variable
    int newPlayerY = m_player.GetYPosition(); // store player position into newPlayerY variable

    //One of the arrow keys were pressed
    if (input == kArrowInput)
    {
        arrowInput = _getch();  // get which arrow is pressed
    }

    if ((input == kArrowInput && arrowInput == kLeftArrow) ||
        (char)input == 'A' || (char)input == 'a')
    {
        newPlayerX--;           // move player Left
    }
    else if ((input == kArrowInput && arrowInput == kRightArrow) ||
        (char)input == 'D' || (char)input == 'd')
    {
        newPlayerX++;           // move player Right
    }
    else if ((input == kArrowInput && arrowInput == kUpArrow) ||
        (char)input == 'W' || (char)input == 'w')
    {
        newPlayerY--;           // move player Up
    }
    else if ((input == kArrowInput && arrowInput == kDownArrow) ||
        (char)input == 'S' || (char)input == 's')
    {
        newPlayerY++;           // move player Down
    }
    else if (input == kEscapeKey)
    {
        m_UserQuit = true;
        return true; // user wants to quit
    }
    else if ((char)input == 'Z' || (char)input == 'z')
    {
        m_player.DropKey();
    }

    // If position never changes
    if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
    {
        return false;
    }
    else
    {
        return HandleCollision(newPlayerX, newPlayerY);
    }
}

// function to handle collision
// arguements are the new position X & Y that the player is moving to
bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
    // bool to trigger when game is done
    bool isGameDone = false;
    // if a collission occurs, it will return to us the collidedActor
    PlaceableActor* collidedActor = m_level.UpdateActors(newPlayerX, newPlayerY); 

    if (collidedActor != nullptr && collidedActor->IsActive()) // check if we've collided with an actor, and if it is active
    {
        switch (collidedActor->GetType())
        {
        case ActorType::Enemy:
        {
            // if collidedActor is an Enemy, create pointer variable of Type Enemy to store
            Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
            assert(collidedEnemy); // trigger alarm if anything goes wrong 
            AudioManager::GetInstance()->PlayLoseLivesSound(); // Play LoseLivesSound
            if (collidedEnemy)
            {
                collidedEnemy->Remove();
                m_player.SetPosition(newPlayerX, newPlayerY);

                m_player.DecrementLives();
                if (m_player.GetLives() < 0)
                {
                    isGameDone = true;
                }
            }
            break;
        }// end of enemy switch
        case ActorType::Money:
        {
            // if collidedActor is Money, create pointer variable of Type Money to store
            Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
            AudioManager::GetInstance()->PlayKeyPickupSound(); // Play PickUpSound
            if (collidedMoney)
            {
                collidedMoney->Remove();
                m_player.AddMoney(collidedMoney->GetWorth()); // add money to players worth
                m_player.SetPosition(newPlayerX, newPlayerY);
            }
            break;
        }// end of money switch
        case ActorType::Key:
        {
            // if collidedActor is Key, create pointer variable of Type Key to store
            Key* collidedKey = dynamic_cast<Key*>(collidedActor);
            AudioManager::GetInstance()->PlayKeyPickupSound();
            if (collidedKey)
            {
                m_player.PickUpKey(collidedKey);
                collidedKey->Remove();
                AudioManager::GetInstance()->PlayKeyDropSound(); // Play KeyPickUpSound
                m_player.SetPosition(newPlayerX, newPlayerY);
                
            }

            break;
        }// end of Key switch
        case ActorType::Door:
        {
            Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
            if (collidedDoor)
            {
                if (!collidedDoor->IsOpen()) // if door is not open
                {
                    if (m_player.hasKey(collidedDoor->GetColor())) // check to see if player has same key
                    {
                        collidedDoor->Open();
                        collidedDoor->Remove();
                        m_player.UseKey();
                        AudioManager::GetInstance()->PlayDoorOpenSound(); // Play door open sound
                        m_player.SetPosition(newPlayerX, newPlayerY);
                        
                    }
                    else
                    {
                        // Play door Closed sound
                    }
                }
                else
                {
                    m_player.SetPosition(newPlayerX, newPlayerY);
                }
            }
            break;
        }// end of Door switch
        case ActorType::Goal:
        {
            Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
            AudioManager::GetInstance()->PlayWinSound(); // Play win sound
            if (collidedGoal)
            {
                collidedGoal->Remove();
                m_player.SetPosition(newPlayerX, newPlayerY);
                isGameDone = true; // meaning the player has won and the game has finished

            }
            break;
        }// end of goal switch

        default:
            break;
        }
    } // end of collision with  actors

    else if (m_level.IsSpace(newPlayerX, newPlayerY)) // no collision, or empty space
    {
        m_player.SetPosition(newPlayerX, newPlayerY); // then update player position to empty space
    }
    else if (m_level.IsWall(newPlayerX, newPlayerY))
    {
        // do nothing because of wall in front of player. 
    }

    return isGameDone;
}



// function to draw
void Game::Draw()
{
    // enable us to bring the colors to the console
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    
    m_level.Draw();

    // Set Cursor to player position
    COORD actorCursorPosition;
    actorCursorPosition.X = m_player.GetXPosition();
    actorCursorPosition.Y = m_player.GetYPosition();
    SetConsoleCursorPosition(console, actorCursorPosition);
    m_player.Draw();

    // Set the sursor to the end of the level
    COORD currentCursorPosition;
    currentCursorPosition.X = 0;
    currentCursorPosition.Y = m_level.GetHeight();
    SetConsoleCursorPosition(console, currentCursorPosition);
    
}