#pragma once

#include "Terrain.h"
#include <iostream>

struct Tile {
	float x, y;
	float size;
	TerrainType type;
};

class Grid 
{
public:
	Grid(const std::string& path);
<<<<<<< Updated upstream
	~Grid();

	void Draw(const Renderer& renderer);

	Tile* tiles;
=======
	Terrain* tiles;
>>>>>>> Stashed changes
private:
	int size;
	const int offset = 32;
	Rectangle basicRectangle;
};