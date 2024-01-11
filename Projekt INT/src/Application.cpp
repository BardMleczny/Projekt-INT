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

#include "../tests/TestClearColor.h"

#include "Grid.h"
#include "Number.h"
#include "Camera.h"
#include "Coin.h"

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

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        Grid grid("res/textures/map3.png");

        Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        Player player(*new Rectangle(192, 640, 96, 96, "res/shaders/basicRectangle.shader"), color, "res/textures/player_right.png");
        //Player player(*new Rectangle(200, 2400, 96, 96, "res/shaders/basicRectangle.shader"), color, "res/textures/player_right.png"); 
        //NumberText n(251, 64);

        int coinCount = 17; // Map 3
        bool* pickedCoins = new bool[coinCount];

        for (int i = 0; i < coinCount; i++)
        {
            pickedCoins[i] = 0;
        }

        Coin** coin = new Coin*[coinCount];
        coin[0] = new Coin(512, 440); // Map3
        coin[1] = new Coin(1024, 440);
        coin[2] = new Coin(1764, 730);
        coin[3] = new Coin(2400, 824);
        coin[4] = new Coin(2878, 1144);
        coin[5] = new Coin(2400, 1464);
        coin[6] = new Coin(2052, 1784);
        coin[7] = new Coin(960, 1564);
        coin[8] = new Coin(312, 1696);
        coin[9] = new Coin(672, 2010);
        coin[10] = new Coin(1280, 2232);
        coin[11] = new Coin(1708, 2556);
        coin[12] = new Coin(1764, 2556);
        coin[13] = new Coin(1820, 2556);
        coin[14] = new Coin(1708, 2612);
        coin[15] = new Coin(1764, 2612);
        coin[16] = new Coin(1820, 2612);
        //coin[2] = new Coin(1380, 610); // Map3 OLD
        //coin[3] = new Coin(1420, 680);
        //coin[4] = new Coin(1480, 740);
        //coin[5] = new Coin(1560, 780);


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

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
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