#pragma once
#include "PlaceableActor.h"

class Enemy : public PlaceableActor
{
public:
	Enemy(int x, int y, int deltaX = 0, int deltaY = 0); // for our moveable enemies

	virtual ActorType GetType() override { return ActorType::Enemy; } // override function to getType
	virtual void Draw() override; // override our virtual draw
	virtual void Update() override; // override our virtual update

private:
	int m_movementInX;
	int m_movementInY;

	int m_currentMovementX;
	int m_currentMovementY;

	int m_directionX;
	int m_directionY;

	void UpdateDirection(int& current, int& direction, int& movement);

};
