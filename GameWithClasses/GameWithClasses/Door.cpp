#include <iostream>
#include <Windows.h>
#include "Door.h"

Door::Door(int x, int y, int color, int closedColor)
	: PlaceableActor(x, y, color)
	, m_isOpen(false) // start the door closed
	, m_closedColor(closedColor) // set door to closed color
{

}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen)
	{
		SetConsoleTextAttribute(console, m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, m_closedColor);
	}
	std::cout << "|";
	SetConsoleTextAttribute(console, kRegularColor);
}