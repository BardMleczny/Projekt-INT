#pragma once

#include "Grid.h"
#include "CheckPoint.h"
#include "Coin.h"
#include "Vector2.h"
#include "Camera.h"
#include "Number.h"

class Level
{
public:
	Level(std::string gridPath, Vector2 checkPointPos, Vector2 playerPos, Vector2* coinsPos, int coinCount, Player& player);

	bool Update(const Renderer& renderer, Camera& camera, Player& player, NumberText& points);

	Grid grid;
	CheckPoint checkPoint;
	Vector2 playerPos;
	int coinCount;
	Coin** coins;
	bool* pickedCoins;
};
