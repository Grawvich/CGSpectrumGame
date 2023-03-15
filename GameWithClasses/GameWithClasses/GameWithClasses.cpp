// GameWithArrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// CREATE a maze that the player can walk through and gather items, and reach a goal
#include <iostream>
#include "Game.h"

using namespace std;
int main()
{
    Game myGame;
    // load game
    if (myGame.Load())
    {
        while (!myGame.isGameOver())
        {
            myGame.Run();
        }

        cout << "We Won!!!!" << endl;
        // Play win sound PlayWinSound();
    }
    else
    {
        cout << "Game did not load, terminating now.";
    }

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
