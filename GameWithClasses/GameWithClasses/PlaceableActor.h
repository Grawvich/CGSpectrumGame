#pragma once
#include "Point.h"



// ----- DECLARATIONS --------

constexpr int kGreenColor = 10;
constexpr int kGreenColorSolid = 34;
constexpr int kRedColor = 12;
constexpr int kRedColorSolid = 68;
constexpr int kBlueColor = 9;
constexpr int kBlueColorSolid = 153;
constexpr int kRegularColor = 7;

class PlaceableActor  // cannot create instances from placeableActor, only from classes that inherit this class.
{
public:
	//constructor & destructor and set default color to kRegularColor
	PlaceableActor(int x, int y, int color = kRegularColor);
	virtual ~PlaceableActor();

	//member functions
	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int x, int y);

	// get color and return color function
	int GetColor() { return m_color; }

	// a function to remove the actor from being active, check to see if its active, and place in a particular position
	void Remove() { m_IsActive = false; }
	bool IsActive() { return m_IsActive; }
	void Place(int x, int y);

	// pure Virtual functions
	virtual void Draw() = 0; // pure virtual function
	virtual void Update() // not PURE, just virtual function
	{

	}

	// allow dervide classes to access following
protected:
	Point* m_pPosition;

	bool m_IsActive;
	int m_color;



};