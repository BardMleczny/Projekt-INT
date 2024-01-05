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
	case RED:
		return { { 1.0f, 1.0f, 1.0f, 1.0f }, Texture("res/textures/a.png") };
	case GREEN:
		return { { 1.0f, 1.0f, 1.0f, 1.0f }, Texture("res/textures/b.png") };
	case BLUE:
		return { { 1.0f, 1.0f, 1.0f, 1.0f }, Texture("res/textures/c.png") };
	default:
		return { { 0.0f, 0.0f, 0.0f, 0.0f }, Texture("res/textures/a.png") };
		break;
	}

	/*switch (type)
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
	}*/
}

Terrain::Terrain(Rectangle& rectangle, TerrainType type)
	: GameObject::GameObject(rectangle, getTileType(type).color, getTileType(type).texture)
{

}

Terrain::Terrain()
	: GameObject::GameObject()
{

}