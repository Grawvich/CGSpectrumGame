#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int deltaX, int deltaY)
	: PlaceableActor(x, y)
	, m_currentMovementX(0)
	, m_currentMovementY(0)
	, m_directionX(0)
	, m_directionY(0)
	, m_movementInX(deltaX)
	, m_movementInY(deltaY)
{
	if (m_movementInX != 0)
	{
		m_directionX = 1;
	}
	if (m_movementInY != 0)
	{
		m_directionY = 1;
	}
}

void Enemy::Draw()
{
	std::cout << (char)153; // ASCII character
}

void Enemy::Update() // this function allows the enemy can ALSO move diagonally
{
	if (m_movementInX != 0) // if theres movement in the X direction (right)
	{
		UpdateDirection(m_currentMovementX, m_directionX, m_movementInX); // update
	}
	if (m_movementInY != 0) // if theres movement in the Y direction (down)
	{
		UpdateDirection(m_currentMovementY, m_directionY, m_movementInY); // update
	}

	this->SetPosition(m_pPosition->x + m_directionX, m_pPosition->y + m_directionY); // set enemy in new position  plus direction
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	current += direction;
	if (std::abs(current) > movement) // if the current direction is greater than the movement then reverse the direction
	{
		current = movement * direction;
		direction *= -1; // reverse direction
	}
}