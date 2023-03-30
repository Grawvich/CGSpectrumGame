#pragma once
#include <windows.h>


class AudioManager
{
	// automatically made private because they are above the public:
	static AudioManager* s_pInstance;

	AudioManager()
	{

	}


public:
	static AudioManager* GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new AudioManager();
		}
		return s_pInstance; 
	}

	// destroy the instance so we dont get memory leaks
	static void DestroyInstance()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

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
		Beep(1568, 50);
		Beep(1568,200);
	}

	void PlayKeyDropSound()
	{
		Beep(1568, 200);
		Beep(1568, 50);
	}

	void PlayLoseLivesSound()
	{
		Beep(1568, 50);
	}

	void PlayLoseSound()
	{
		Beep(500, 75);
		Beep(500, 75);
		Beep(500, 75);
		Beep(500, 75);
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
	}
};