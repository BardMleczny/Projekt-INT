#pragma once

#include "Terrain.h"

struct Tile {
	float x, y;
	float size;
	TerrainType type;
};

class Grid 
{
public:
	Grid(const std::string& path);
	~Grid();

	void Draw(const Renderer& renderer);

	Tile* tiles;
private:
	int size;
	const int offset = 32;
	Rectangle basicRectangle;
};