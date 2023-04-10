#pragma once
#include "GameState.h"
#include <windows.h>
#include "Player.h"
#include "level.h"
#include <vector>
#include <string>

// forward declare the statemachineExampleGame
class StateMachineExampleGame;

class GameplayState :  public GameState
{
	StateMachineExampleGame* m_pOwner;

	Player m_player;
	Level* m_pLevel;
	
	bool m_beatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;
	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* pOwner); // constructor that takes in a pointer which will be the owner of the statemachines
	~GameplayState();
	virtual void  Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

private:
	bool Load();

	void HandleCollision(int newPlayerX, int newPlayerY);
	void DrawHUD(const HANDLE& console);
};

