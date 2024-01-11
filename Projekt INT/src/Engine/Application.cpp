#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Engine/Renderer.h"
#include "Engine/Input.h"
#include "Engine/Rectangle.h"
#include "Engine/Number.h"
#include "Engine/Camera.h"

#include "Game/Grid.h"
#include "Game/Player.h"
#include "Game/Coin.h"
#include "Game/CheckPoint.h"
#include "Game/Level.h"

void calculateFPS(GLFWwindow* window);

double lastTime = 0.0;
int frameCount = 0;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1600, 960, "Projekt", NULL, NULL);

    Input::window = window;

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;
        Camera camera;

        NumberText points(0, 32);
        Player player(*new Rectangle(200, 2400, 96, 96, "res/shaders/basicRectangle.shader"), { 1.0f, 1.0f, 1.0f, 1.0f }, "res/textures/player_right.png", "res/textures/player_left.png");

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

        while (!glfwWindowShouldClose(window))
        {
            calculateFPS(window);

            renderer.Clear();

            if (currentLevel < 3)
            {
                player.Update(renderer, levels[currentLevel].grid, camera);
                if (levels[currentLevel].Update(renderer, camera, player, points))
                    currentLevel++;
            }
            else
            {
                if (points.value == 50)
                    NumberText(2137, 100).Draw(900, 400, renderer);
                else
                    break;
            }

            if (currentLevel == 0)
            {
                checkPoint1.Draw(renderer, camera);
                checkPoint2.Draw(renderer, camera);
                if (checkPoint1.IsComplete(player) || checkPoint2.IsComplete(player))
                    currentLevel = 1;
            }
            
            points.Draw(100, 860, renderer);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

void calculateFPS(GLFWwindow* window) {
    double currentTime = glfwGetTime();

    double deltaTime = currentTime - lastTime;

    frameCount++;

    if (deltaTime >= 1.0) {
        double fps = static_cast<double>(frameCount) / deltaTime;
        std::cout << "FPS: " << fps << std::endl;

        frameCount = 0;
        lastTime = currentTime;
    }
}