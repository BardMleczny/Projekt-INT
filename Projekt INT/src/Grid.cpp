#include "Grid.h"

#include "stb_image/stb_image.h"
#include "TerrainType.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Color.h"

Grid::Grid(const std::string& path)
	:  shader("res/shaders/grid.shader")
{
	int width, height, bpp;
	unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	size = width * height;
	std::cout << width << std::endl;
	std::cout << height << std::endl;
	std::cout << size << std::endl;
	tiles = new Tile[width * height];

	float* data = new float[size * 20];

	indices = new unsigned int[size * 6];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * height + j;
			
			int value = (int)(buffer[index * 4] * 1000000 +
				buffer[index * 4 + 1] * 1000 +
				buffer[index * 4 + 2]);

			TerrainType type = TerrainType(value);

			float x = (float)j * OFFSET;
			float y = (float)i * OFFSET;

			tiles[index] = { { x, y, (float)OFFSET, (float)OFFSET }, type };

			data[index * 20 + 0] = x;
			data[index * 20 + 1] = y;
			data[index * 20 + 2] = 0;
			data[index * 20 + 3] = 0;
			data[index * 20 + 4] = tileTexture.getTextureIndex(type);

			data[index * 20 + 5] = x + OFFSET;
			data[index * 20 + 6] = y;
			data[index * 20 + 7] = 1;
			data[index * 20 + 8] = 0;
			data[index * 20 + 9] = tileTexture.getTextureIndex(type);

			data[index * 20 + 10] = x + OFFSET;
			data[index * 20 + 11] = y + OFFSET;
			data[index * 20 + 12] = 1;
			data[index * 20 + 13] = 1;
			data[index * 20 + 14] = tileTexture.getTextureIndex(type);

			data[index * 20 + 15] = x;
			data[index * 20 + 16] = y + OFFSET;
			data[index * 20 + 17] = 0;
			data[index * 20 + 18] = 1;
			data[index * 20 + 19] = tileTexture.getTextureIndex(type);

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
	layout.Push<float>(1);

	va.AddBuffer(vb, layout);

	va.Unbind();

	glm::mat4 proj = glm::ortho(0.0f, 1600.0f, 0.0f, 960.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	glm::mat4 mvp = proj * view;

	int* textureIndexes = new int[tileTexture.NUM_OF_TEXTURES];

	for (int i = 0; i < tileTexture.NUM_OF_TEXTURES; i++)
	{
		textureIndexes[i] = i;
	}

	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	shader.SetUniform1iv("u_Textures", tileTexture.NUM_OF_TEXTURES, textureIndexes);
}

Grid::~Grid()
{
	delete tiles;
}

void Grid::Draw(const Renderer& renderer)
{
	tileTexture.LoadTextures();
	renderer.DrawBatch(va, ib, shader, indices);
}

Grid::TileTexture::TileTexture()
{
	const char NUM_OF_TEXTURES = 24;
	textures = new Texture * [NUM_OF_TEXTURES];
	std::string texturesNames[NUM_OF_TEXTURES] = {
		"empty",
		"grass1", "grass2", "grass3", "grass4", "grass4",
		"dirtGrass1", "dirtGrass2", "dirtGrass3", "dirtGrass4", "dirtGrass5",
		"dirtLeft1", "dirtLeft2", "dirtRight1", "dirtRight2",
		"dirtCenter1", "dirtCenter2" , "dirtCenter3" , "dirtCenter4",
		"dirtBottom1", "dirtBottom2", "dirtBottom3", "dirtBottom4", "dirtBottom5"
	};

	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		Texture* tempTexture = new Texture("res/textures/tiles/" + texturesNames[i] + ".png");
		textures[i] = tempTexture;
	}
}

Grid::TileTexture::~TileTexture()
{
	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		delete textures[i];
	}
	delete textures;
}

void Grid::TileTexture::LoadTextures()
{
	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		textures[i]->Bind(i);
	}
}

int Grid::TileTexture::getTextureIndex(TerrainType terrainType)
{
	switch (terrainType)
	{
	case GRASS1:
		return 1;
	case GRASS2:
		return 2;
	case GRASS3:
		return 3;
	case GRASS4:
		return 4;
	case GRASS5:
		return 5;
	case DIRTGRASS1:
		return 6;
	case DIRTGRASS2:
		return 7;
	case DIRTGRASS3:
		return 8;
	case DIRTGRASS4:
		return 9;
	case DIRTGRASS5:
		return 10;
	case DIRTLEFT1:
		return 11;
	case DIRTLEFT2:
		return 12;
	case DIRTRIGHT1:
		return 13;
	case DIRTRIGHT2:
		return 14;
	case DIRTCENTER1:
		return 15;
	case DIRTCENTER2:
		return 16;
	case DIRTCENTER3:
		return 17;
	case DIRTCENTER4:
		return 18;
	case DIRTBOTTOM1:
		return 19;
	case DIRTBOTTOM2:
		return 20;
	case DIRTBOTTOM3:
		return 21;
	case DIRTBOTTOM4:
		return 22;
	case DIRTBOTTOM5:
		return 23;
	default:
		return 0;
	}
}