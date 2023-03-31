#pragma once
#include "GameState.h"

// forward declare class to get access

class StateMachineExampleGame;

class MainMenuState :  public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	MainMenuState(StateMachineExampleGame* pOwner);
	~MainMenuState() = default;

	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
};

