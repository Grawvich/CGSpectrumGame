#include "Level.h"
#include "Player.h"
#include <iostream>
#include <fstream>

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

void Level::Draw(int x, int y)
{
    int index = GetIndexFromCoordinates(x, y);
    cout << m_pLevelData[index];
}

bool Level::IsSpace(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

bool Level::IsDoor(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == DOR;
}

bool Level::IsKey(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == KEY;
}

bool Level::IsGoal(int x, int y)
{
    return m_pLevelData[GetIndexFromCoordinates(x, y)] == END;
}

void Level::PickUpKey(int x, int y)
{
    int index = GetIndexFromCoordinates(x, y);
    
    m_pLevelData[GetIndexFromCoordinates(x, y)] = ' ';
    
}

void Level::OpenDoor(int x, int y)
{
    m_pLevelData[GetIndexFromCoordinates(x, y)] = ' ';
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
            case '|':
                m_pLevelData[index] = WAL;
                break;
            case '*':
                m_pLevelData[index] = KEY;
                break;
            case 'D':
                m_pLevelData[index] = DOR;
                break;
            case 'X':
                m_pLevelData[index] = END;
                break;
            case '@':
                m_pLevelData[index] = ' ';
                if(playerX != nullptr && playerY != nullptr)
                { // there might be times when we dont want the level to set playerX & PlayerY from the levelData, and we can just pass null instead of the player x & playerY variables
                    *playerX = x;
                    *playerY = y;
                }
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
