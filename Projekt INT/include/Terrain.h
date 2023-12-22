#pragma once

#include "GameObject.h"
#include "TerrainType.h"

class Terrain : public GameObject
{
	Terrain(Rectangle& rectangle, TerrainType type);
};