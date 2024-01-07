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

	int size;

	Tile* tiles;
private:
	class TileTexture
	{
	public:
		TileTexture();
		~TileTexture();

		int getTextureIndex(TerrainType terrainType);
		void LoadTextures();

		const char NUM_OF_TEXTURES = 24;

	private:
		Texture** textures;
	};

	TileTexture tileTexture;

	const int OFFSET = 16;
	unsigned int* indices;
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
};