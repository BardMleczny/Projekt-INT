#include "Terrain.h"

struct Tile
{
	Color color;
	Texture texture;
};

Tile getTileType(TerrainType type)
{
	/*
		switch z texturami
	*/

	return { { 1.0f, 1.0f, 1.0f, 1.0f }, Texture("res/textures/image1.png") };
}

Terrain::Terrain(Rectangle& rectangle, TerrainType type)
	: GameObject::GameObject(rectangle, getTileType(type).color, getTileType(type).texture)
{

}
