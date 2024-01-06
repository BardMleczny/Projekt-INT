#include "Grid.h"

#include "stb_image/stb_image.h"
#include "TerrainType.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Color.h"

Grid::Grid(const std::string& path)
	:  shader("res/shaders/basic.shader")
{
	int width, height, bpp;
	unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	/*for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << (int)buffer[(i * height + j) * 4] << "-" << 
					(int)buffer[(i * height + j) * 4 + 1] << "-" << 
					(int)buffer[(i * height + j) * 4 + 2] << "-" << 
					(int)buffer[(i * height + j) * 4 + 3] << "|";
		}
		std::cout << std::endl;
	}*/

	size = width * height;
	std::cout << width << std::endl;
	std::cout << height << std::endl;
	std::cout << size << std::endl;
	tiles = new Tile[width * height];

	float* data = new float[size * 16];

	indices = new unsigned int[size * 6];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * height + j;
<<<<<<< Updated upstream
			TerrainType type = TerrainType((int)((float)buffer[index * bpp] * 1000000 + (float)buffer[index * bpp + 1] * 1000 + (float)buffer[index * bpp + 2]));
=======
			int value = (int)(buffer[index * 4] * 1000000 +
				buffer[index * 4 + 1] * 1000 +
				buffer[index * 4 + 2]);

			TerrainType type = TerrainType(value);
>>>>>>> Stashed changes

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
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 300.0f, 0));

	glm::mat4 mvp = proj * view/* * model*/;

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

Grid::TileTexture::TileTexture()
{
	const char NUM_OF_TEXTURES = 23;
	textures = new Texture[NUM_OF_TEXTURES];
	std::string texturesNames[NUM_OF_TEXTURES] = {
<<<<<<< Updated upstream
		"grass1", "grass2", "grass3", "grass4", "grass4",
=======
		"empty",
		"grass1", "grass2", "grass3", "grass4", "grass5",
>>>>>>> Stashed changes
		"dirtGrass1", "dirtGrass2", "dirtGrass3", "dirtGrass4", "dirtGrass5",
		"dirtLeft1", "dirtLeft2", "dirtRight1", "dirtRight2",
		"dirtCenter1", "dirtCenter2" , "dirtCenter3" , "dirtCenter4",
		"dirtBottom1", "dirtBottom2", "dirtBottom3", "dirtBottom4", "dirtBottom5"
	};

	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		textures[i] = Texture("res/textures/tiles/" + texturesNames[i] + ".png");
	}
}

int Grid::TileTexture::NumOfTextureEnum(TerrainType terrainType)
{
	switch (terrainType)
	{
	case GRASS1:
		return 0;
	case GRASS2:
		return 1;
	case GRASS3:
		return 2;
	case GRASS4:
		return 3;
	case GRASS5:
		return 4;
	case DIRTGRASS1:
		return 5;
	case DIRTGRASS2:
		return 6;
	case DIRTGRASS3:
		return 7;
	case DIRTGRASS4:
		return 8;
	case DIRTGRASS5:
		return 9;
	case DIRTLEFT1:
		return 10;
	case DIRTLEFT2:
		return 11;
	case DIRTRIGHT1:
		return 12;
	case DIRTRIGHT2:
		return 13;
	case DIRTCENTER1:
		return 14;
	case DIRTCENTER2:
		return 15;
	case DIRTCENTER3:
		return 16;
	case DIRTCENTER4:
		return 17;
	case DIRTBOTTOM1:
		return 18;
	case DIRTBOTTOM2:
		return 19;
	case DIRTBOTTOM3:
		return 20;
	case DIRTBOTTOM4:
		return 21;
	case DIRTBOTTOM5:
		return 22;
	default:
		return -1;
	}
}