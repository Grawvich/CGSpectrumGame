#pragma once
#include "PlaceableActor.h"

class Goal : public PlaceableActor
{
public:
	Goal(int x, int y);

	virtual ActorType GetType() override { return ActorType::Goal; } // override function to getType
	virtual void Draw() override;
};