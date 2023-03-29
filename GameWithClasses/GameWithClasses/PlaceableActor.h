#pragma once
#include "Point.h"



// ----- DECLARATIONS --------

// enum for colors
enum class ActorColor
{
	RegularColor = 7,
	Blue = 9,
	Green = 10,
	Red = 12,
	SolidBlue = 153,
	SolidGreen = 34,
	SolidRed = 68
};

enum class ActorType
{
	Door,
	Enemy,
	Goal,
	Key,
	Money,
	Player
};

class PlaceableActor  // cannot create instances from placeableActor, only from classes that inherit this class.
{
public:
	//constructor & destructor and set default color to kRegularColor
	PlaceableActor(int x, int y, ActorColor color = ActorColor::RegularColor);
	virtual ~PlaceableActor();

	//member functions
	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int x, int y);

	// get color and return color function
	ActorColor GetColor() { return m_color; }

	// a function to remove the actor from being active, check to see if its active, and place in a particular position
	void Remove() { m_IsActive = false; }
	bool IsActive() { return m_IsActive; }
	void Place(int x, int y);

	// pure Virtual functions
	virtual ActorType GetType() = 0; // pure virtual function to return the Type
	virtual void Draw() = 0; // pure virtual function
	virtual void Update() // not PURE, just virtual function
	{

	}

	// allow dervide classes to access following
protected:
	Point* m_pPosition;

	bool m_IsActive;
	ActorColor m_color;



};