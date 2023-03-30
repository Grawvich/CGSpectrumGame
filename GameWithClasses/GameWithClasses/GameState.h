#pragma once

class GameState // asbtract class with public virtual function to be overridden
{
public:

	// provide destructor
	virtual ~GameState() = default;

	// establish gamestates
	virtual void Enter() {} // virtual function gamestate Enter
	virtual bool Update(bool processInput = true) {} // virtual function gamestate 

	virtual void Exit(){} // virtual function gamestate Exit
};