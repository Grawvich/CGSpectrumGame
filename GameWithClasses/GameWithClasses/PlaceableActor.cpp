#include "PlaceableActor.h"

//constructor & destructor and set default color to kRegularColor
PlaceableActor::PlaceableActor(int x, int y, int color)
	:m_pPosition(new Point(x, y))
	, m_IsActive(true)
	, m_color(color)
{

}
PlaceableActor::~PlaceableActor()
{
	delete m_pPosition;
	m_pPosition = nullptr;
}

//---------member functions

// function to get X position
int PlaceableActor::GetXPosition()
{
	return m_pPosition->x; // use dereference operator to get value 
}

// function to get Y position
int PlaceableActor::GetYPosition()
{
	return m_pPosition->y; // use dereference operator to get value 
}

// funciton to get pointer X position
int* PlaceableActor::GetXPositionPointer()
{
	return &(m_pPosition->x); // use dereference operator to get value 
}

// function to get Y position Pointer
int* PlaceableActor::GetYPositionPointer()
{
	return &(m_pPosition->y); // use dereference operator to get value 
}

// function to set position of actor
void PlaceableActor::SetPosition(int x, int y)
{
	m_pPosition->x = x;
	m_pPosition->y = y;
}


// a function to place actor in a particular position and set IsActive = true which activates it.
void PlaceableActor::Place(int x, int y)
{
	m_pPosition->x = x;
	m_pPosition->y = y;
	m_IsActive = true;
}

