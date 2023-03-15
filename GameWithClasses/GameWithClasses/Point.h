#pragma once

// change class to struct to make all member variables & functions PUBLIC, remove public:
struct Point
{
// member variables
	int x;
	int y;

	// constructor
	Point()
		: x(0)
		, y(0)
	{
	

	}

	Point(int x, int y)
	{ // member variables x & y, equal the public variables x & y
		this->x = x;
		this->y = y;

	}


};