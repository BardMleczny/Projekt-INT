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

	float* data = new float[size * 16];

	indices = new unsigned int[size * 6];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * height + j;
			TerrainType type = getTileType(Color{ (float)buffer[index * bpp], (float)buffer[index * bpp + 1],
												  (float)buffer[index * bpp + 2], (float)buffer[index * bpp + 3], });

			tiles[i * height + j] = { { (float)j * offset, (float)i * offset, (float)offset, (float)offset }, type };

			data[index * 16 + 0] = j * offset;
			data[index * 16 + 1] = i * offset;
			data[index * 16 + 2] = 0;
			data[index * 16 + 3] = 0;

			data[index * 16 + 4] = j * offset + offset;
			data[index * 16 + 5] = i * offset;
			data[index * 16 + 6] = 1;
			data[index * 16 + 7] = 0;

			data[index * 16 + 8] = j * offset + offset;
			data[index * 16 + 9] = i * offset + offset;
			data[index * 16 + 10] = 1;
			data[index * 16 + 11] = 1;

			data[index * 16 + 12] = j * offset;
			data[index * 16 + 13] = i * offset + offset;
			data[index * 16 + 14] = 0;
			data[index * 16 + 15] = 1;

			indices[index * 6 + 0] = 0 + index * 4;
			indices[index * 6 + 1] = 1 + index * 4;
			indices[index * 6 + 2] = 2 + index * 4;
			indices[index * 6 + 3] = 2 + index * 4;
			indices[index * 6 + 4] = 3 + index * 4;
			indices[index * 6 + 5] = 0 + index * 4;
		}
	}

	ib.LoadData(indices, size * 6);

	vb.LoadData(data, size * 16);

	layout.Push<float>(2);
	layout.Push<float>(2);

	va.AddBuffer(vb, layout);

	va.Unbind();

	glm::mat4 proj = glm::ortho(0.0f, 1600.0f, 0.0f, 960.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	glm::mat4 mvp = proj * view;

	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	shader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
}

Grid::~Grid()
{
	delete tiles;
}

void Grid::Draw(const Renderer& renderer)
{
	renderer.DrawBatch(va, ib, shader, indices);
}
