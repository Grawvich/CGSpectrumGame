#pragma once
#include "PlaceableActor.h"

class Money : public PlaceableActor
{
public:
	// Constructor for the money placement and worth
	Money(int x, int y, int worth);

	// Get & Set for money worth
	int GetWorth() const { return m_worth; }

	virtual void Draw() override;
private:
	int m_worth; // provide worth

};