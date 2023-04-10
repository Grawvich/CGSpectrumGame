#pragma once
#include <string>
#include <vector>

class PlaceableActor;

class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;

	// creat a list of placeable actors as pointers
	std::vector<PlaceableActor*>m_pActors;

public:
	// constructors and destructors
	Level();
	~Level();

	bool Load(std::string levelName, int* playerX, int* playerY);
	void Draw();
	PlaceableActor* UpdateActors(int x, int y);

	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

	// declare constant public border for our HUD
	static constexpr char WAL = (char)219;

	// private functions
private:
	bool Convert(int* playerX, int* playerY);
	int GetIndexFromCoordinates(int x, int y);
};