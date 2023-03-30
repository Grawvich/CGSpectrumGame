#include "Game.h"


// constructor
Game::Game()
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}

void Game::RunGameLoop()
{
	bool isGameover = false;
	while (!isGameover)
	{
		Update(false); // update without input first
		Draw();
		isGameover = Update();
	}

	Draw(); // one last Draw() to update the state of the machine.
}

void Game::Deinitialize()
{
	if (m_pStateMachine)
	{
		m_pStateMachine->Cleanup();
	}
}

bool Game::Update(bool processInput)
{
	return m_pStateMachine->UpdateCurrentState(processInput);
}
void Game::Draw()
{
	m_pStateMachine->DrawCurrentState();
}


