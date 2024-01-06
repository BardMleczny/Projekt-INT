#pragma once

#include "Renderer.h"
#include "Rectangle.h"
#include "TerrainType.h"
#include "Texture.h"

struct Tile {
	Transform transform;
	TerrainType type;
};

class Grid 
{
public:
	Grid(const std::string& path);
	~Grid();

	void Draw(const Renderer& renderer);

	Tile* tiles;

	class TileTexture
	{
	public:
		const char NUM_OF_TEXTURES = 23;
		Texture* textures;
		TileTexture();
		int NumOfTextureEnum(TerrainType terrainType);
	};
private:
	int size;
	const int offset = 32;
	unsigned int* indices;
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
};
