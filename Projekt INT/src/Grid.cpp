#include "Grid.h"

#include "stb_image/stb_image.h"
#include "TerrainType.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Color.h"

TerrainType getTileType(Color color) {
	return TerrainType::DEFAULT;
}

Grid::Grid(const std::string& path)
	:  shader("res/shaders/basic.shader")
{
	int width, height, bpp;
	unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
	size = width * height;
	std::cout << size << std::endl;
	tiles = new Tile[width * height];

	float* data = new float[size * 20];

	indices = new unsigned int[size * 6];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * height + j;
			TerrainType type = getTileType(Color{ (float)buffer[index * bpp], (float)buffer[index * bpp + 1],
												  (float)buffer[index * bpp + 2], (float)buffer[index * bpp + 3], });

			tiles[i * height + j] = { { (float)j * offset, (float)i * offset, (float)offset, (float)offset }, type };

			data[index * 20 + 0] = j * offset;
			data[index * 20 + 1] = i * offset;
			data[index * 20 + 2] = 0;
			data[index * 20 + 3] = 0;
			data[index * 20 + 4] = getTextureIndex(type);

			data[index * 20 + 5] = j * offset + offset;
			data[index * 20 + 6] = i * offset;
			data[index * 20 + 7] = 1;
			data[index * 20 + 8] = 0;
			data[index * 20 + 9] = getTextureIndex(type);

			data[index * 20 + 10] = j * offset + offset;
			data[index * 20 + 11] = i * offset + offset;
			data[index * 20 + 12] = 1;
			data[index * 20 + 13] = 1;
			data[index * 20 + 14] = getTextureIndex(type);

			data[index * 20 + 15] = j * offset;
			data[index * 20 + 16] = i * offset + offset;
			data[index * 20 + 17] = 0;
			data[index * 20 + 18] = 1;
			data[index * 20 + 19] = getTextureIndex(type);

			indices[index * 6 + 0] = 0 + index * 4;
			indices[index * 6 + 1] = 1 + index * 4;
			indices[index * 6 + 2] = 2 + index * 4;
			indices[index * 6 + 3] = 2 + index * 4;
			indices[index * 6 + 4] = 3 + index * 4;
			indices[index * 6 + 5] = 0 + index * 4;
		}
	}

	ib.LoadData(indices, size * 6);

	vb.LoadData(data, size * 20);

	layout.Push<float>(2);
	layout.Push<float>(2);

	va.AddBuffer(vb, layout);

	va.Unbind();

	glm::mat4 proj = glm::ortho(0.0f, 1600.0f, 0.0f, 960.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	glm::mat4 mvp = proj * view;

	int* textureIndexes = new int[TileTexture.NUM_OF_TEXTURES];

	for (int i = 0; i < TileTexture.NUM_OF_TEXTURES; i++)
	{
		textureIndexes[i] = i;
	}

	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	shader.SetUniform1iv("u_Textures", TileTexture.NUM_OF_TEXTURES, textureIndexes);
}

Grid::~Grid()
{
	delete tiles;
}

void Grid::Draw(const Renderer& renderer)
{
	TileTexture.LoadTextures();
	renderer.DrawBatch(va, ib, shader, indices);
}
