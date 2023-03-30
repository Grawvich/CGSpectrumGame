// GameWithArrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// CREATE a maze that the player can walk through and gather items, and reach a goal
//#include "vld.h"
#include <iostream>
#include "Game.h"
#include "AudioManager.h"
#include "StateMachineExampleGame.h"


using namespace std;

int main()
{
    Game myGame;

    StateMachineExampleGame gameStateMachine(&myGame);

    myGame.Initialize(&gameStateMachine);
    myGame.RunGameLoop();
    myGame.Deinitialize();


    AudioManager::DestroyInstance(); // destroy AudioManager to prevent memory leaks

    return 0; // return an integer
}








/*
// functions to play sound at various times 
void PlayDoorClosedSound()
{
    Beep(500, 75); // (frequency, duration)
    Beep(500, 75); // play the sound a second time
}

void PlayDoorOpenSound()
{
    Beep(1397, 75);
}

void PlayKeyPickupSound()
{
    Beep(1568, 75);
}

void PlayWinSound()
{
    // a series of beep function calls to produce a melody with the <window.h> library
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1545, 1000);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1175, 1000);
}*/
