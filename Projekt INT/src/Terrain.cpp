#include "Terrain.h"

struct Tile
{
	Color color;
	Texture texture;
};

Tile getTileType(TerrainType type)
{
	switch (type)
	{
	case dirtLeftTop:
		return { { 0.0f, 0.0f, 0.0f, 1.0f }, Texture("res/textures/dirtLeftTop.png") };
	case dirtRightTop:
		return { { 0.0f, 0.0f, 0.0f, 1.0f }, Texture("res/textures/dirtRightTop.png") };
	case dirtCenter:
		return { { 0.0f, 0.0f, 0.0f, 1.0f }, Texture("res/textures/dirtCenter.png") };
	case dirtLeftBottom:
		return { { 0.0f, 0.0f, 0.0f, 1.0f }, Texture("res/textures/dirtLeftBottom.png") };
	case dirtRightBottom:
		return { { 0.0f, 0.0f, 0.0f, 1.0f }, Texture("res/textures/dirtRightBottom.png") };
	default:
		return { { 0.0f, 0.0f, 0.0f, 1.0f }, Texture("res/textures/image2.png") };
	}
}

Terrain::Terrain(Rectangle& rectangle, TerrainType type)
	: GameObject::GameObject(rectangle, getTileType(type).color, getTileType(type).texture)
{

}
