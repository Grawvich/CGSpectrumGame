#include "Player.h"
#include "Key.h"
#include <iostream>

using namespace std;

//declare player lives
constexpr int kStartingNumberLives = 3;

// constructor
Player::Player()
	: PlaceableActor(0,0) // call the placeable Actor, and p[ass in coordinates with default color
	, m_pCurrentKey(nullptr) // set current key to null because we dont have a key
	, m_money(0) // money set to 0
	, m_lives(kStartingNumberLives)
{

}


// member functions
bool Player::hasKey()
{
	return m_pCurrentKey != nullptr; // check to see if current key is set to null, will return true if we have a key
}

bool Player::hasKey(int color) // check to see if we have a key
{
	return hasKey() && m_pCurrentKey->GetColor() == color; // return color of the key
}

void Player::PickUpKey(Key* key)
{
	m_pCurrentKey = key; // will take in a key pointer and set current key to the key pointer
}

void Player::UseKey()
{
	m_pCurrentKey->Remove(); // will remove the key by setting it to inActive
	m_pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (m_pCurrentKey) // check to see if the player has a key
	{
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y); // drop key in position of the player
		m_pCurrentKey = nullptr; // set current key to null, and key is active in the world position
	}
}

void Player::Draw()
{
	cout << "@";
}

