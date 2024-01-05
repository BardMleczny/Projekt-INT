#pragma once

#include "Terrain.h"

class Grid 
{
public:
	Grid(const std::string& path);

	void Draw(const Renderer& renderer);

	Terrain** tiles;

	class TileTexture
	{
	public:
		Texture* textures;
		TileTexture()
	};
private:
	const int offset = 32;
};