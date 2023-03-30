#pragma once
#include "GameStateMachine.h"

// forward declare a couple classes we are going to use
class Game;
class GameState;


class StateMachineExampleGame : public GameStateMachine
{
public:

    // create enum that will store all the scenes of our game and be made public
    enum class SceneName
    {
        None,
        MainMenu,
        Gameplay
    };

private:
    Game* m_pOwner; // allow the state to interact with the game

    GameState* m_pCurrentState;
    GameState* m_pNewState;

public:
    StateMachineExampleGame(Game* pOwner); // owner of the statemachine

    virtual bool Init() override;
    virtual bool UpdateCurrentState(bool processInput = true) override;
    virtual void DrawCurrentState() override;
    virtual void ChangeState(GameState* pNewState) override;
    virtual void Cleanup() override;
    void LoadScene(SceneName scene);
};

