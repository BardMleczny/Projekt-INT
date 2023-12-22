#pragma once

#include "Terrain.h"

class Grid 
{
public:
	Grid();
	Terrain* tiles;
private:
	const int offset = 20;
};