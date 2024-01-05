#include "Grid.h"

#include "stb_image/stb_image.h"
#include "TerrainType.h"
#include <iostream>
#include <string>


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
{
	int width, height, bpp;
	unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
	int size = width * height;
	std::cout << size << std::endl;
	tiles = new Terrain*[width * height];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Rectangle tileRec = Rectangle(j * offset, i * offset, offset, offset, "res/shaders/basicRectangle.shader");

			int index = i * height + j;
			TerrainType type = getTileType(Color{ (float)buffer[index * bpp] / 255, (float)buffer[index * bpp + 1] / 255,
										(float)buffer[index * bpp + 2] / 255, (float)buffer[index * bpp + 3] / 255, });
		
			std::cout << sizeof(tiles) << std::endl;
			delete tiles[i * height + j];

			tiles[i * height + j] = new Terrain(tileRec, type);
		}
	}
}

void Grid::Draw(const Renderer& renderer)
{
	for (int i = 0; i < sizeof(tiles) / sizeof(Terrain); i++)
	{
		tiles[i]->Draw(renderer);
	}
}

Grid::TileTexture::TileTexture()
{
	const char NUM_OF_TEXTURES = 23;
	textures = new Texture[NUM_OF_TEXTURES];
	std::string texturesNames[NUM_OF_TEXTURES] = {
		"grass1", "grass2", "grass3", "grass4", "grass4", 
		"dirtGrass1", "dirtGrass2", "dirtGrass3", "dirtGrass4", "dirtGrass5", 
		"dirtLeft1", "dirtLeft2", "dirtRight1", "dirtRight2", 
		"dirtBottom1", "dirtBottom2", "dirtBottom3", "dirtBottom4", "dirtBottom5", 
		"dirtCenter1", "dirtCenter2" , "dirtCenter3" , "dirtCenter4" 
	};

	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		textures[i] = Texture("res/textures/tiles/" + texturesNames[i] + ".png");
	}
}