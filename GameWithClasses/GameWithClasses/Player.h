#pragma once
#include "Point.h"


class Player
{
	// private member variables
	Point m_position;
	bool m_hasKey;

public:
	Player();
	~Player();

	int GetXPosition() { return m_position.x; }
	int GetYPosition() { return m_position.y; }

	// for Level.cpp, allowing Load function to pointer to player X & Y
	int* GetXPositionPointer() { return &(m_position.x); }
	int* GetYPositionPointer() { return &(m_position.y); }

	void SetPosition(int x, int y);

	// member functions
	bool hasKey();
	void PickUpKey();
	void UseKey();
	void Draw();


};