// LevelEditorGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// The user can specify how many columns and rows they want and based on that they will populate the level from that displaying dynamic memory and pointers


#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <fstream>

using namespace std;

// ------ DECLARATIONS of variables---------
constexpr char kTopRightBorder = 187; // Extended ASCII character 187
constexpr char kTopLefttBorder = 201; // Extended ASCII character 201
constexpr char kBottomRightBorder = 188; // Extended ASCII character 188
constexpr char kBottomLeftBorder = 200; // Extended ASCII character 200
constexpr char kHorizontalBorder = 205; // Extended ASCII character 205
constexpr char kVerticalBorder = 186; // Extended ASCII character 186

// constants for the cursor
constexpr char kCursor = '_';
// constants for arrow keys
constexpr int kArrowInput = 224; // Extended ASCII character
constexpr int kLeftArrow = 75; // Extended ASCII character
constexpr int kRightArrow = 77; // Extended ASCII character
constexpr int kUpArrow = 72; // Extended ASCII character
constexpr int kDownArrow = 80; // Extended ASCII character
constexpr int kEscape = 27; // Extended ASCII character


// ------DECLARATIONS of FUNCTIONS ---------

// function to get level dimensions
void GetLevelDimensions(int& width, int& height); // reference variableswidth & height. WE could have passed it in by POINTER VARIABLE too.
//function to display the level
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
// function to get index x and y from array
int GetIndexFromXY(int x, int y, int width);
//function to DisplayBorder
void DisplayTopBorder(int width);
//function to DisplayBorder
void DisplayBottomBorder(int width);
//function to DisplayBorder, DOES NOT TAKE PARAMETERS
void DisplayLeftBorder();
//function to DisplayBorder, DOES NOT TAKE PARAMETERS
void DisplayRightBorder();
// function to editLevel
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height);
// function to SaveLevel
void SaveLevel(char* pLevel, int width, int height);

int main()
{
	int levelWidth;
	int levelHeight;

	GetLevelDimensions(levelWidth, levelHeight);
	// allocate dynamic memory for the array
	char* pLevel = new char[levelWidth * levelHeight];

	// populate the array with spaces " "
	for (int i = 0; i < levelWidth * levelHeight; i++)
	{
		pLevel[i] = ' ';
	}

	// create local scope variables
	int cursorX = 0;
	int cursorY = 0;
	bool doneEditing = false;

	// loop for runtime
	while (!doneEditing)
	{
		system("cls"); // clear screen
		// displaylevel to terminal
		DisplayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);
		doneEditing = EditLevel(pLevel, cursorX, cursorY, levelWidth, levelHeight);
	}

	system("cls");
	DisplayLevel(pLevel, levelWidth, levelHeight, -1, -1); // a little trick to do wherethe player char isnt shown

	// Call function to SaveLevel
	SaveLevel(pLevel, levelWidth, levelHeight);

	// de-allocate the memory of the array
	delete[] pLevel;
	pLevel = nullptr;
}


// -------- DEFINITIONS -------

// function to get level dimensions
void GetLevelDimensions(int& width, int& height) // reference variableswidth & height. WE could have passed it in by POINTER VARIABLE too.
{
	// ask user for height & width
	cout << "Please enter width of your level: ";
	cin >> width;

	cout << "Please enter height of your level: ";
	cin >> height;
}

//function to display the level
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY)
{
	DisplayTopBorder(width);
	// double for loop to iterate through and display some information from the array
	for (int y = 0; y < height; y++)
	{
		DisplayLeftBorder();
		for (int x = 0; x < width; x++)
		{
			// 
			if (cursorX == x && cursorY == y)
			{
				cout << kCursor;
			}
			else
			{
				// We require the helper function to get our index from the array
				int index = GetIndexFromXY(x, y, width);
				cout << pLevel[index];
			}
		}
		DisplayRightBorder();
	}

	DisplayBottomBorder(width);
}

// function to get index x and y from array
int GetIndexFromXY(int x, int y, int width)
{
	return x + y * width;
}

//function to DisplayBorder
void DisplayTopBorder(int width)
{
	cout << kTopLefttBorder;
	// loop to display the border for the total width
	for (int i = 0; i < width; i++)
	{
		cout << kHorizontalBorder;
	}
	cout << kTopRightBorder << endl;
}

//function to DisplayBorder
void DisplayBottomBorder(int width)
{
	cout << kBottomLeftBorder;
	// loop to display the border for the total width
	for (int i = 0; i < width; i++)
	{
		cout << kHorizontalBorder;
	}
	cout << kBottomRightBorder << endl;
}

//function to DisplayBorder, DOES NOT TAKE PARAMETERS
void DisplayLeftBorder()
{
	cout << kVerticalBorder;
}

//function to DisplayBorder, DOES NOT TAKE PARAMETERS
void DisplayRightBorder()
{
	cout << kVerticalBorder << endl;
}

// function to SaveLevel
void SaveLevel(char* pLevel, int width, int height)
{
	// ask the user to pick a name for their level
	string levelName;
	cout << "Pick a name for your level file( eg: Level1.txt):  ";
	cin >> levelName;

	// since we want all the edit files the level will write to be accessable by the project we insert 
	levelName.insert(0, "../"); // ../ means in windows file explorer language, "move up one folder" allowing access to the files

	ofstream levelFile;
	levelFile.open(levelName);
	if (!levelFile)// check to see if any flag errors occur
	{
		cout << " Opening file failed!" << endl;
	}
	else // continue to save levelFile
	{
		levelFile << width << endl;
		levelFile << height << endl;
		levelFile.write(pLevel, height * width);

		if (!levelFile) // check to see if any flag errors occur
		{
			cout << " Write failed!" << endl;
		}
		levelFile.close();

	}
}


// function to editLevel
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height)
{
	int newCursorX = cursorX;
	int newCursorY = cursorY;

	// get input
	int intInteger = _getch();

	// if key arrow input
	if (intInteger == kArrowInput)
	{
		// so that the compiler reads the exact arrow that was pressed.
		int arrowInput = _getch();
		switch (arrowInput)
		{
		case kLeftArrow:
			newCursorX--;
			break;
		case kRightArrow:
			newCursorX++;
			break;
		case kUpArrow:
			newCursorY--;
			break;
		case kDownArrow:
			newCursorY++;
			break;
		default:
			cout << "entry not valid!" << endl;
			break;

		}

		// CLAMP METHOD: Clamp X values so that the values wont go below 0 or over the width/height of the level
		if (newCursorX < 0)
			newCursorX = 0;
		else if (newCursorX == width)
			newCursorX = width - 1; // total width minus 1 to keep within the boundaries
		// CLAMP METHOD: Clamp Y values so that the values wont go below 0 or over the width/height of the level
		if (newCursorY < 0)
			newCursorY = 0;
		else if (newCursorY == width)
			newCursorY = width - 1; // total width minus 1 to keep within the boundaries    DEBUG THE CLAMP METHOD LATER------------ 

		cursorX = newCursorX;
		cursorY = newCursorY;
	}
	// if ESC key input
	else
	{
		if (intInteger == kEscape)
		{
			return true; // means we are done editing this level, returning bool editLevel to true.
		}
		else
		{
			// store the key in the map that was pressed because our player is pressing the arrow keys
			int index = GetIndexFromXY(newCursorX, newCursorY, width);
			pLevel[index] = (char)intInteger;
		}
	}
	return false; // terminate loop

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
