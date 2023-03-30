#pragma once
#include "GameState.h"
#include "Player.h"
#include "level.h"

// forward declare the statemachineExampleGame
class StateMachineExampleGame;

class GameplayState :  public GameState

{
	StateMachineExampleGame* m_pOwner;

	Player m_player;
	Level m_level;
	
	bool m_Beatgame;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

public:
	GameplayState(StateMachineExampleGame* pOwner); // constructor that takes in a pointer which will be the owner of the statemachines
	
	virtual void  Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

private:
	bool Load();

	void HandleCollision(int newPlayerX, int newPlayerY);
};

