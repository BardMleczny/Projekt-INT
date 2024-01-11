#include "Level.h"

Level::Level(std::string gridPath, Vector2 checkPointPos, Vector2 playerPos, Vector2* coinsPos, int coinCount)
	: grid(gridPath),
	checkPoint(checkPointPos.x, checkPointPos.y), 
	playerPos(playerPos),
	coinCount(coinCount),
	pickedCoins(new bool[coinCount]),
	coins(new Coin* [coinCount])
{
	for (int i = 0; i < coinCount; i++)
	{
		pickedCoins[i] = 0;
		coins[i] = new Coin(coinsPos[i].x, coinsPos[i].y);
	}
}

bool Level::Update(const Renderer& renderer, Camera& camera, const Player& player, NumberText& points)
{
    for (int i = 0; i < coinCount; i++)
    {
        if (!pickedCoins[i])
        {
            if (coins[i]->canBeDrawn)
            {
                coins[i]->Draw(renderer, camera);
                if (coins[i]->IsPicked(player))
                {
                    delete coins[i];
                    pickedCoins[i] = true;
                    points.number++;
                }
            }
        }
    }

    grid.Draw(renderer, camera.GetMatrix());

    checkPoint.Draw(renderer, camera);
    if (checkPoint.IsComplete(player))
        return true;

    return false;
}