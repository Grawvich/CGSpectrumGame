#include "SettingsState.h"
#include <iostream>
#include <conio.h>
#include "StateMachineExampleGame.h"
#include "AudioManager.h"


using namespace std;

constexpr int kEscapeKey = 27;
constexpr int kSound = '1';
constexpr int kMainMenu = '2';

SettingsState::SettingsState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool SettingsState::Update(bool processInput)
{
	
	if (processInput)
	{
		int input = _getch(); // get input
		if (input == kEscapeKey || (char)input == kMainMenu)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		else if ((char)input == kSound)
		{
			AudioManager::GetInstance()->ToggleSound();
			AudioManager::GetInstance()->PlayKeyPickupSound();
		}
	}

	return false;
}

void SettingsState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "         - - - MAINE MENU - - - " << endl << endl;
	cout << "          " << kSound << ". Toggle Sound " << endl;
	if (AudioManager::GetInstance()->IsSoundOn())
	{
		cout << "ON" << endl;
		cout << "OFF" << endl;
	}
	cout << "          " << "2. Back to Main Menu " << endl;
}