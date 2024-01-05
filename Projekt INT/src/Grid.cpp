#include "Grid.h"

#include "stb_image/stb_image.h"
#include "TerrainType.h"
#include <iostream>


TerrainType getTileType(Color color) {
	if (color.r == 1.0f && color.g == 0.0f && color.b == 0.0f)
		return TerrainType::RED;
	if (color.r == 0.0f && color.g == 1.0f && color.b == 0.0f)
		return TerrainType::GREEN;
	if (color.r == 1.0f && color.g == 0.0f && color.b == 0.0f)
		return TerrainType::BLUE;
	return TerrainType::DEFAULT;
}

Grid::Grid(const std::string& path)
	:  basicRectangle(0, 0, offset, offset, "res/shaders/basic.shader")
{
	int width, height, bpp;
	unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
	size = width * height;
	std::cout << size << std::endl;
	tiles = new Tile[width * height];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * height + j;
			TerrainType type = getTileType(Color{ (float)buffer[index * bpp], (float)buffer[index * bpp + 1],
												  (float)buffer[index * bpp + 2], (float)buffer[index * bpp + 3], });

			tiles[i * height + j] = { (float)j * offset, (float)i * offset, (float)offset, type };
		}
	}
}

Grid::~Grid()
{
	delete tiles;
}

void Grid::Draw(const Renderer& renderer)
{
	for (int i = 0; i < size; i++)
	{
		Tile tempTile = tiles[i];
		basicRectangle.m_transform = { tempTile.x, tempTile.y, tempTile.size, tempTile.size };
		// LoadTileTexture(tempTile.tileType);
		renderer.DrawRectangle(basicRectangle, { 1.0f, 0.0f, 1.0f, 1.0f }, basicRectangle.m_shader);
	}
}