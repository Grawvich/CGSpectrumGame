#include <iostream>
#include <fstream>
#include <windows.h>
#include <assert.h>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"

using namespace std;

// declare some characters from the ASCII extended table
constexpr char WAL = (char)219;
constexpr char KEY = (char)232;
constexpr char DOR = (char)179;
constexpr char END = (char)36;




// constructors and destructors
Level::Level()
	: m_pLevelData(nullptr)
	, m_height(0)
	, m_width(0)
{

}

Level::~Level()
{
    if (m_pLevelData != nullptr)
    {
        delete[] m_pLevelData;
        m_pLevelData = nullptr;
    }

    while (!m_pActors.empty()) // while the actor list is not empty
    {
        delete m_pActors.back(); // return us the elemtn at the end, then delete. 
        m_pActors.pop_back(); // this progresively delets the list to the beginning
    }
}

// use pointers to point to player.x & player.y positions
bool Level::Load(std::string levelName, int* playerX, int* playerY)
{

    levelName.insert(0, "../");
    ifstream levelFile;
    levelFile.open(levelName);
    if (!levelFile)
    {
        cout << "Opening file failed!" << endl;
        return false; // return null pointer if there was an error.
    }
    else
    {
        // character read to gt width and height
        constexpr int tempSize = 25;
        char temp[tempSize];

        // store char array into integers width & height from levelFile, basically setting the width and heigth from the levelData
        levelFile.getline(temp, tempSize, '\n');
        m_width = atoi(temp); // helper function atoi takes the character array and stores in an integer

        levelFile.getline(temp, tempSize, '\n');
        m_height = atoi(temp); // helper function atoi takes the character array and stores in an integer

        m_pLevelData = new char[m_width * m_height]; // REMEMBER to De-allocate memory
        levelFile.read(m_pLevelData, (long long)m_width * (long long)m_height);

        
        // function call to check if there are any characters that the user has typed inside the level
        bool anyWarnings = Convert(playerX, playerY);
        if (anyWarnings)
        {
            cout << "There were some warnings in the level data, see above." << endl;
            system("pause");

        }
        return true;
    }
}

void Level::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, kRegularColor); // set color to regular

    // Draw the Level after getting width and height
    for (int y = 0; y < GetHeight(); ++y)
    {
        for (int x = 0; x < GetWidth(); ++x)
        {
            int indexToPrint = GetIndexFromCoordinates(x, y);
            cout << m_pLevelData[indexToPrint];
        }
        cout << endl;
    }

    // position the cursor at the correct location so we can draw the appropriate actors according to their position
    COORD actorCursorPosition; // COORDinate Datatype

    // DRAW actors
    for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor) // go throuhg beginnning of actors array to the end and increment.
    {
        if ((*actor)->IsActive()) // if actor is active the we draw, if not active the we dont draw
        {
            actorCursorPosition.X = (*actor)->GetXPosition();
            actorCursorPosition.Y = (*actor)->GetYPosition();
            SetConsoleCursorPosition(console, actorCursorPosition); // select the console  and actorCurrentPosition then draw the actor
            (*actor)->Draw(); // draw the actor
        }
    }






}

bool Level::IsSpace(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' '; // if its a space, return true or false
}

bool Level::IsWall(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == WAL; // if its a wall, return true or false
}


// private member funcitons
bool Level::Convert(int* playerX, int* playerY)
{
    bool anyWarnings = false;
    // double for loop to read all hars inside the array
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int index = GetIndexFromCoordinates(x, y);

            switch (m_pLevelData[index])
            {
            case '+':
            case '-':
            case '|': // any of these means we have a wall
                m_pLevelData[index] = WAL;
                break;
            case 'r': // red key
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kRedColor)); // adds the red key to our vector list
                break;
            case 'g': // green key
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kGreenColor)); // adds the green key to our vector list
                break;
            case 'b': // blue key
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, kBlueColor)); // adds the blue key to our vector list
                break;
            case 'R': // red Door
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Door(x, y, kRedColor, kRedColorSolid)); // adds red door to the vecotr
                break;
            case 'G': // green Door
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Door(x, y, kGreenColor, kGreenColorSolid)); // adds green door to the vecotr
                break;
            case 'B': // Blue door
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Door(x, y, kBlueColor, kBlueColorSolid)); // adds blue door to the vecotr
                break;
            case 'X': // Blue door
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Goal(x, y)); // adds Goal to the vecotr
                break;
            case '$': // Blue door
                m_pLevelData[index] = ' ';
                m_pActors.push_back(new Money(x, y, 1 + rand() % 5)); // adds money to the vecotr from 1-5 
                break;
            case '@': // Blue door
                m_pLevelData[index] = ' ';
                if (playerX != nullptr && playerY != nullptr)
                {
                    *playerX = x;
                    *playerY = y;
                }
                break;
            case 'e':
                m_pActors.push_back(new Enemy(x, y));
                m_pLevelData[index] = ' '; // clear the level
                break;
            case 'h':
                m_pActors.push_back(new Enemy(x, y, 3, 0));
                m_pLevelData[index] = ' '; // clear the level
                break;
            case 'v':
                m_pLevelData[index] = ' '; 
                m_pActors.push_back(new Enemy(x, y, 0, 2));
                m_pLevelData[index] = ' '; // clear the level
                break;
                break;
            case ' ': // do nothing  when there is a space except leave a space
                break;
            default:
                cout << " Invalid Char in level file: " << m_pLevelData[index] << endl;
                anyWarnings = true;
                break;
            }

        }
    }


    return anyWarnings;

}

int Level::GetIndexFromCoordinates(int x, int y)
{
    return x + y * m_width;
}

// Updates all actors and returns a colliding actor if there is one
PlaceableActor* Level::UpdateActors(int x, int y) // pass x & y of the acotr (player in this case)
{
    PlaceableActor* collidedActor = nullptr;

    for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor) // loop all of elements in our actor vector
    {
        (*actor)->Update(); // Update all actors

        if (x == (*actor)->GetXPosition() && y == (*actor)->GetYPosition()) // means a collision occured
        {
            // should only be able to collide with one actor, should not detect multiple colliders
            assert(collidedActor == nullptr); // means that make sure the collider is eual to null. assert only triggers in debug mode.
            collidedActor = (*actor);
        }
    }
    return collidedActor; // return the collided actor

}