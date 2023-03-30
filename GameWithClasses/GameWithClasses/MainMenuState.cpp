#include "MainMenuState.h"
#include "StateMachineExampleGame.h"

#include <iostream>
#include <conio.h>

using namespace std;

constexpr int kEscapeKey = 27;
constexpr int kPlay = '1';
constexpr int kQuit = '2';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool MainMenuState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch(); // get input
		if (input == kEscapeKey || (char)input == kQuit)
		{
			shouldQuit = true;
		}
		else if ((char)input == kPlay)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
		}
	}

	return shouldQuit;
}

void MainMenuState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "         - - - MAINE MENU - - - " << endl << endl;
	cout << "          " <<  "1. Play " << endl;
	cout << "          " <<  "2. Quit " << endl;
}


