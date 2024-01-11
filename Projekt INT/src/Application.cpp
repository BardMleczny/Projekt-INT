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
#include "Level.h"

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
        Player player(*new Rectangle(192, 640, 96, 96, "res/shaders/basicRectangle.shader"), { 1.0f, 1.0f, 1.0f, 1.0f }, "res/textures/player_right.png", "res/textures/player_left.png");

        Vector2 coins[] = {
            {200, 1200},
            {400, 1200}
        };
        Level levels[1] = {
            Level("res/textures/map1.png", {}, {}, coins, 2, player)
        };
        int currentLevel = 0;

        while (!glfwWindowShouldClose(window))
        {
            calculateFPS(window);

            renderer.Clear();

            if (currentLevel < 1)
            {
                player.Update(renderer, levels[currentLevel].grid, camera);
                if (levels[currentLevel].Update(renderer, camera, player, points))
                    currentLevel++;
            }
            else
            {
                break;
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