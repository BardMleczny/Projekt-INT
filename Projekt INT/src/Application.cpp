#include <iostream>

#include "Renderer.h"
#include "Input.h"
#include "Rectangle.h"
#include "Number.h"
#include "Camera.h"
#include "Color.h"

#include "Grid.h"
#include "Player.h"
#include "Coin.h"
#include "CheckPoint.h"
#include "Level.h"

double lastTime = 0.0;
int frameCount = 0;

int main(void)
{
    Renderer::Init();
    
    NumberText points(0, 32, Colors::WHITE);
    Player player(*new Rectangle(200, 2400, 96, 96, "res/shaders/basicRectangle_vertex.shader", "res/shaders/basicRectangle_fragment.shader"), Colors::WHITE, "res/textures/player_right.png", "res/textures/player_left.png");

    Vector2 coins1[] = {
        {800, 2176}, {1024, 2432}, {1250, 2176}, {1946, 2384},
        {1984, 2432}, {2040, 2464}, {2272, 2488}, {2272, 2546},
        {1024, 1334}, {1536, 1334}, {1152, 408}, {1408, 408},
        {1152, 464}, {1408, 464}
    };
    Vector2 coins2[] = {
        {1024, 608}, {1088, 672}, {1152, 736}, {1200, 776},
        {1248, 736}, {1312, 672}, {1376, 608}, {2137, 504}, 
        {2176, 576}, {2216, 648}, {2272, 704}, {2328, 760},
        {2400, 800}, {2720, 728}, {2778, 728}, {2720, 786},
        {2778, 786}
    };
    Vector2 coins3[] = {
        {512, 440}, {680, 440}, {856, 440}, {1024, 440},
        {1764, 730}, {2400, 824}, {2878, 1144}, {2400, 1464},
        {2052, 1784}, {960, 1564}, {312, 1696}, {672, 2010},
        {1280, 2232}, {1708, 2556}, {1764, 2556}, {1820, 2556},
        {1708, 2612}, {1764, 2612}, {1820, 2612}
    };
    Level levels[3] = {
        Level("res/textures/map1.png", {2400, 2528}, {200, 2400}, coins1, 14, player),
        Level("res/textures/map2.png", {3072, 792}, {192, 640}, coins2, 17, player),
        Level("res/textures/map3.png", {1920, 2592}, {192, 640}, coins3, 19, player)
    };

    CheckPoint checkPoint1(1280, 1372);
    CheckPoint checkPoint2(1280, 448);

    int currentLevel = 0;

    while (!Renderer::ShouldWindowClose())
    {
        Renderer::BeginIteration();

        Renderer::Clear();

        if (currentLevel < 3)
        {
            player.Update(levels[currentLevel].grid);
            if (levels[currentLevel].Update(player, points))
                currentLevel++;
        }
        else
        {
            if (points.value == 50)
                NumberText(2137, 100, Colors::WHITE).Draw(900, 400);
            else
                break;
        }

        if (currentLevel == 0)
        {
            checkPoint1.Draw();
            checkPoint2.Draw();
            if (checkPoint1.IsComplete(player) || checkPoint2.IsComplete(player))
                currentLevel = 1;
        }
        
        points.Draw(100, 860);

        Renderer::EndIteration();
    }
    

    Renderer::Terminate();
    exit(0);
    return 0;
}