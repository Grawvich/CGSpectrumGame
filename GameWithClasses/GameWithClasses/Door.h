#pragma once
#include "PlaceableActor.h"

class Door : public PlaceableActor
{
public:
	Door(int x, int y, int color, int closedColor);
	virtual void Draw() override;
	// get & set door color
	bool IsOpen() { return m_isOpen; }
	void Open() { m_isOpen = true; }

private:
	bool m_isOpen;
	int m_closedColor;

};
