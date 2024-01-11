#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Input.h"

#include "Rectangle.h"
#include "Player.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Grid.h"
#include "Number.h"
#include "Camera.h"
#include "Coin.h"
#include "CheckPoint.h"

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

        Grid grid("res/textures/niggermap3.png");

        int coinCount = 3;
        bool* pickedCoins = new bool[coinCount];

        for (int i = 0; i < coinCount; i++)
        {
            pickedCoins[i] = 0;
        }

        Coin** coin = new Coin*[coinCount];
        coin[0] = new Coin(192, 640);
        coin[1] = new Coin(320, 640);
        coin[2] = new Coin(480, 640);

        CheckPoint checkPoint(192, 480);

        Player player(*new Rectangle(192, 640, 96, 96, "res/shaders/basicRectangle.shader"), { 1.0f, 1.0f, 1.0f, 1.0f }, "res/textures/player_right.png");
        NumberText points(0, 32);

        while (!glfwWindowShouldClose(window))
        {
            calculateFPS(window);

            renderer.Clear();
            player.Update(renderer, grid, camera);
            grid.Draw(renderer, camera.GetMatrix());

            for (int i = 0; i < coinCount; i++)
            {
                if (!pickedCoins[i])
                {
                    if (coin[i]->canBeDrawn)
                    {
                        coin[i]->Draw(renderer, camera);
                        if (coin[i]->IsPicked(player))
                        {
                            delete coin[i];
                            pickedCoins[i] = true;
                            points.number++;
                        }
                    }
                }
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