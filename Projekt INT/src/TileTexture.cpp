#include "Grid.h"

Grid::TileTexture::TileTexture()
{
	const char NUM_OF_TEXTURES = 24;
	textures = new Texture * [NUM_OF_TEXTURES];
	std::string texturesNames[NUM_OF_TEXTURES] = {
		"empty",
		"grass1", "grass2", "grass3", "grass4", "grass5",
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