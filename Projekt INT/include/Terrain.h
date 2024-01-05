#pragma once

#include "GameObject.h"
#include "TerrainType.h"

class Terrain : public GameObject
{
public:
	Terrain(Rectangle& rectangle, TerrainType type);
	Terrain();
};