#pragma once

// forward declare the GameState Class
class GameState;


class GameStateMachine // abstract game state machine class
{
public:
	virtual ~GameStateMachine() = default;

	virtual bool Init() = 0; // pure virtual function
	virtual bool UpdateCurrentState(bool processInput = true) = 0; // pure virtual function
	virtual void DrawCurrentState() = 0; // pure virtual function
	virtual void ChangeState(GameState* pNewState) = 0; // pure virtual function
	virtual void Cleanup() = 0; // pure virtual function
};