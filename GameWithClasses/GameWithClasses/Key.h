#pragma once
#include "PlaceableActor.h"

class Key : public PlaceableActor
{
public:
	// constructor that takes in the X, Y, and color
	Key(int x, int y, ActorColor color)
		:PlaceableActor(x, y, color)
	{

	}

	// virtual function override to draw key
	virtual void Draw() override;
	virtual ActorType GetType() override { return ActorType::Key; } // override function to getType

};
