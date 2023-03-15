#pragma once
#include "PlaceableActor.h"

class Key; // forward class declaration

class Player : public PlaceableActor
{
public:
	Player();
	
	// member functions
	bool hasKey();
	bool hasKey(int color);
	void PickUpKey(Key* key);
	void UseKey();
	void DropKey();

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; } 

	virtual void Draw() override;
	
private:
	Key* m_pCurrentKey; // Aggregation because we can hold the key, AND it still exists
	int m_money;
	int m_lives;


};